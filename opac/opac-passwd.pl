#!/usr/bin/perl
# This script lets the users change the passwords by themselves.
#
# (c) 2005 Universidad ORT Uruguay.
#
# This file is part of the extensions and enhacments made to koha by Universidad ORT Uruguay
#
# Koha is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Koha is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Koha; if not, see <https://www.gnu.org/licenses>.

use Modern::Perl;

use CGI qw ( -utf8 );

use C4::Auth qw( get_template_and_user checkpw checkpw_hash );
use C4::Context;
use C4::Output qw( output_html_with_http_headers );
use Koha::Patrons;

use Try::Tiny qw( catch try );

use HTTP::Tiny;
use JSON qw( encode_json decode_json );

my $query = CGI->new;
my $op    = $query->param('op') || q{};

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name => "opac-passwd.tt",
        query         => $query,
        type          => "opac",
    }
);

my $patron = Koha::Patrons->find($borrowernumber);
if ( $patron->category->effective_change_password ) {
    if (   $query->param('Oldkey')
        && $query->param('Newkey')
        && $query->param('Confirm') )
    {
        die "op must be set" unless $op eq 'cud-change_password';
        my $error;
        my $old_password     = scalar $query->param('Oldkey');
        my $new_password     = $query->param('Newkey');
        my $confirm_password = $query->param('Confirm');

        # Kiểm tra mật khẩu cũ: trước tiên qua Koha hash, sau đó thử LDAP nếu có cấu hình
        my $password_valid = C4::Auth::checkpw_hash( $old_password, $patron->password );
        if ( !$password_valid && C4::Context->config('useldapserver') ) {
            eval {
                require C4::Auth_with_ldap;
                my $uid = $patron->userid || $patron->cardnumber;
                my ($retval) = C4::Auth_with_ldap::checkpw_ldap( $uid, $old_password );
                $password_valid = 1 if $retval && $retval == 1;
            };
        }

        if ( $password_valid ) {

            if ( $new_password ne $confirm_password ) {
                $template->param( 'Ask_data'           => '1' );
                $template->param( 'Error_messages'     => '1' );
                $template->param( 'passwords_mismatch' => '1' );
            } else {
                try {
                    $patron->set_password( { password => $new_password } );
                    $template->param( 'password_updated' => '1' );
                    $template->param( 'borrowernumber'   => $borrowernumber );

                    # Đồng bộ mật khẩu mới lên hệ thống SSO / LDAP
                    my $sso_uid = $patron->userid || $patron->cardnumber;
                    if ($sso_uid) {
                        _sync_password_to_sso($sso_uid, $new_password, $template);
                    }
                } catch {
                    $error = 'password_too_short'
                        if $_->isa('Koha::Exceptions::Password::TooShort');
                    $error = 'password_too_weak'
                        if $_->isa('Koha::Exceptions::Password::TooWeak');
                    $error = 'password_has_whitespaces'
                        if $_->isa('Koha::Exceptions::Password::WhitespaceCharacters');
                };
            }
        } else {
            $error = 'WrongPass';
        }
        if ($error) {
            $template->param(
                Ask_data       => 1,
                Error_messages => 1,
                $error         => 1,
            );

        }
    } else {

        # Called Empty, Ask for data.
        $template->param( 'Ask_data' => '1' );
        if ( !$query->param('Oldkey') && ( $query->param('Newkey') || $query->param('Confirm') ) ) {

            # Old password is empty but one of the others isn't
            $template->param( 'Error_messages' => '1' );
            $template->param( 'WrongPass'      => '1' );
        } elsif ( $query->param('Oldkey') && ( !$query->param('Newkey') || !$query->param('Confirm') ) ) {

            # Oldpassword is entered but one of the other fields is empty
            $template->param( 'Error_messages' => '1' );
            $template->param( 'PassMismatch'   => '1' );
        }
    }
}
$template->param(
    firstname  => $patron->firstname,
    surname    => $patron->surname,
    passwdview => 1,
);

output_html_with_http_headers $query, $cookie, $template->output, undef, { force_no_caching => 1 };

# ------------------------------------------------------------------------------
# Helper: Đồng bộ mật khẩu sang hệ thống xác thực SSO (SSO Portal / OpenLDAP)
# ------------------------------------------------------------------------------
sub _sync_password_to_sso {
    my ( $uid, $new_password, $tmpl ) = @_;
    return unless $uid && length($new_password);

    my $payload = encode_json({ newPassword => $new_password });
    my $http    = HTTP::Tiny->new( timeout => 5 );
    my $headers = {
        'Content-Type'    => 'application/json',
        'x-koha-staff'    => '1',
        'x-koha-internal' => '1',
    };

    # Lấy URL SSO từ cấu hình hệ thống FTU_SSOBaseURL
    my $sso_pref = C4::Context->preference('FTU_SSOBaseURL') || '';
    $sso_pref =~ s{/+$}{}; # loại bỏ dấu gạch chéo cuối nếu có

    # Danh sách URL API SSO theo thứ tự ưu tiên: cấu hình hệ thống -> host.docker.internal -> localhost
    my @candidate_urls;
    if ($sso_pref && $sso_pref !~ /myDNSname/) {
        push @candidate_urls, "$sso_pref/api/v1/sso/users/$uid/reset-password?koha_staff=1";
    }
    push @candidate_urls, (
        "http://host.docker.internal:8090/api/v1/sso/users/$uid/reset-password?koha_staff=1",
        "http://localhost:8090/api/v1/sso/users/$uid/reset-password?koha_staff=1",
        "http://127.0.0.1:8090/api/v1/sso/users/$uid/reset-password?koha_staff=1"
    );

    my $synced   = 0;
    my $last_err = '';

    for my $url (@candidate_urls) {
        my $response = eval {
            $http->post( $url, {
                headers => $headers,
                content => $payload,
            });
        };
        if ( $response && $response->{success} ) {
            $synced = 1;
            last;
        } elsif ( $response && $response->{content} ) {
            my $json_data = eval { decode_json( $response->{content} ) };
            if ( $json_data && $json_data->{success} ) {
                $synced = 1;
                last;
            }
            $last_err = $json_data->{error} || $response->{reason} || ( "HTTP " . $response->{status} );
        } else {
            $last_err = $response ? $response->{reason} : ( $@ || 'Không thể kết nối máy chủ SSO' );
        }
    }

    # Nếu không kết nối được qua HTTP API, dự phòng gọi trực tiếp LDAP server nếu có cấu hình
    if ( !$synced && C4::Context->config('useldapserver') ) {
        eval {
            require Net::LDAP;
            my $ldap_host = C4::Context->config('ldapserver')->{hostname} || 'host.docker.internal';
            my $ldap_base = C4::Context->config('ldapserver')->{base}     || 'dc=thuvien,dc=vn';
            my $ldap_user = C4::Context->config('ldapserver')->{user}     || 'cn=admin,dc=thuvien,dc=vn';
            my $ldap_pass = C4::Context->config('ldapserver')->{pass}     || 'admin';

            my $ldap = Net::LDAP->new( $ldap_host, timeout => 5 );
            if ($ldap) {
                my $mesg = $ldap->bind( $ldap_user, password => $ldap_pass );
                if ( !$mesg->code ) {
                    my $dn = "uid=$uid,ou=users,$ldap_base";
                    my $mod_mesg = $ldap->modify( $dn, replace => { userPassword => $new_password } );
                    if ( !$mod_mesg->code ) {
                        $synced = 1;
                    } else {
                        $last_err = "LDAP error: " . $mod_mesg->error;
                    }
                    $ldap->unbind;
                }
            }
        };
    }

    if ($synced) {
        $tmpl->param( sso_updated => 1 ) if $tmpl;
        warn "[SSO Sync] Đã cập nhật mật khẩu thành công cho UID: $uid lên hệ thống SSO\n";
    } else {
        $tmpl->param( sso_error => $last_err ) if $tmpl;
        warn "[SSO Sync] Lỗi cập nhật mật khẩu cho UID: $uid lên SSO: $last_err\n";
    }

    return $synced;
}

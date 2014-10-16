/* Initialize c functions for curl reader/writer in R
 *
 * Author: Martin Morgan <mtmorgan@fhcrc.org>
 */
#ifndef WRITER_H
#define WRITER_H

SEXP rssh2_sftp_download(SEXP hostname, SEXP username, SEXP password, SEXP filepath, SEXP authmode);
int sftp_download(char *hostname, char *username, char *password, char *sftppath, char *authmode);

#endif

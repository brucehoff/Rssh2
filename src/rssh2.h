/* Initialize c functions
 */
#ifndef SFTP_H
#define SFTP_H

int sftp_download(char **hostname_arg, char **username_arg, char **password_arg, char **sftppath_arg, char **localpath_arg, int *rc);
int sftp_upload(char **hostname_arg, char **username_arg, char **password_arg, char **sftppath_arg, char **localpath_arg, int *rc);

#endif

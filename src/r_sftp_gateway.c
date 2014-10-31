
int rssh_sftp_download(char *userhost, char *user, char *sftppath, char *localpath);
int rssh_sftp_upload(char *userhost, char *user, char *sftppath, char *localpath);
void set_user_password(char *pass);

/**
 * Download a file from an sftp server.
 */
void sftp_download(char **hostname_arg, char **username_arg, char **password_arg, char **sftppath_arg, char **localpath_arg, int *result)
{
	init();
	set_user_password(*password_arg);
	*result = rssh_sftp_download(*hostname_arg, *username_arg, *sftppath_arg,*localpath_arg);
}

void sftp_upload(char **hostname_arg, char **username_arg, char **password_arg, char **sftppath_arg, char **localpath_arg, int *result)
{
	init();
	set_user_password(*password_arg);
	*result = rssh_sftp_upload(*hostname_arg, *username_arg, *sftppath_arg,*localpath_arg);
}

void sftp_mkdir() {

}

void sftp_rmdir() {

}

void sftp_dir() {

}


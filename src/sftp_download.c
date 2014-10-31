#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <limits.h>

#define PUTTY_DO_GLOBALS
#include "putty.h"
#include "psftp.h"
#include "storage.h"
#include "ssh.h"
#include "sftp.h"
#include "int64.h"

/* TODO should the following be in a header file? */
int rssh_sftp_download(char *userhost, char *user, char *password, char *sftppath, char *localpath);

/**
 * Download a file from an sftp server.
 */
void sftp_download(char **hostname_arg, char **username_arg, char **password_arg, char **sftppath_arg, char **localpath_arg, int *result)
{
#ifndef _WINDOWS
	uxsel_init();
#endif
	*result = rssh_sftp_download(*hostname_arg, *username_arg, *password_arg, *sftppath_arg,*localpath_arg);
	return;
}


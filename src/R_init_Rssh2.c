/* Initialize c functions used by R wrapper functions
 *
 */
#include <Rdefines.h>
#include <R_ext/Rdynload.h>
#include "rssh2.h"

static const R_CallMethodDef callMethods[] = {
	    {"sftp_download", (DL_FUNC) &sftp_download, 6},
	    {"sftp_upload", (DL_FUNC) &sftp_download, 6},
    {NULL, NULL, 0}
};

void
R_init_Rssh2(DllInfo *info)
{
    R_registerRoutines(info, NULL, callMethods, NULL, NULL);
}

void
R_unload_ssh2(DllInfo *info)
{
    /* any clean-up when package unloaded */
}

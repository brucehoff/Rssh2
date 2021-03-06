# sftpDownload -- download a file from an sftp server
# returns TRUE if successful, FALSE otherwise
# 
# Author: brucehoff
###############################################################################

sftpDownload<-function(host, username, password, remotepath, localpath) {
  resetState()
  result<-.C("sftp_download", 
    as.character(host), 
    as.character(username), 
    as.character(password), 
    as.character(remotepath), 
    as.character(localpath), 
    as.integer(0),
    PACKAGE="Rssh2")
  if (result[[6]]==0) return(TRUE) else return(FALSE)
}



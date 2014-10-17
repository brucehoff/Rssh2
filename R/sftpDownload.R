# sftpDownload -- download a file from an sftp server
# 
# Author: brucehoff
###############################################################################

sftpDownload<-function(host, username, password, remotepath, localpath) {
  result<-.C("sftp_download", 
    as.character(host), 
    as.character(username), 
    as.character(password), 
    as.character(remotepath), 
    as.character(localpath))
  result[6]
}



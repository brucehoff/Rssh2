# sftpDownload -- download a file from an sftp server
# 
# Author: brucehoff
###############################################################################

sftpDownload<-function(host, username, password, filepath, authmode) {
  .C("sftp_download", host, username, password, filepath, authmode)
}



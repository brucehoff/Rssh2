# sftpDownload -- download a file from an sftp server
# 
# Author: brucehoff
###############################################################################

sftpDownload<-function(host, username, password, remotepath, localpath) {
  .C("sftp_download", host, username, password, remotepath, localpath)
}



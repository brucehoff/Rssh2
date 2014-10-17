# sftpUpload -- download a file from an sftp server
# 
# Author: brucehoff
###############################################################################

sftpUpload<-function(host, username, password, remotepath, localpath) {
  .C("sftp_upload", host, username, password, remotepath, localpath)
}



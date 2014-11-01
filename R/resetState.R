# The underlying 'c' application has state that persists between calls
# and causes later calls to fail.  As a work-around we clear the state
# by reloading the c library.
# 
# Author: brucehoff
###############################################################################

resetState<-function() {
  libFilePath<-system.file("libs/Rssh2.so", package = "Rssh2")
  result<-dyn.unload(libFilePath)
  print(result)
  result<-dyn.load(libFilePath)
  print(result)
}
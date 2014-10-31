# The underlying 'c' application has state that persists between calls
# and causes later calls to fail.  As a work-around we clear the state
# by reloading the c library.
# 
# Author: brucehoff
###############################################################################

resetState<-function() {
  library.dynam.unload("Rssh2", system.file(package = "Rssh2"))
  library.dynam("Rssh2", "Rssh2", .libPaths())
}
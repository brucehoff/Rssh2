#!/bin/sh
# Everything that needs to be done before building the package goes here:

# download unix source from PuTTY.  Note:  We get a specific version, not the 'latest'
export libName=putty
tools/downloadsource.sh $libName putty-0.63 putty-0.63.tar.gz http://the.earth.li/~sgtatham/putty/0.63/

# copy .c files
mkdir -p src/putty
cp /tmp/$libName/be_ssh.c src/putty/
cp /tmp/$libName/cmdline.c src/putty/
cp /tmp/$libName/conf.c src/putty/
cp /tmp/$libName/cproxy.c src/putty/
cp /tmp/$libName/int64.c src/putty/
cp /tmp/$libName/logging.c src/putty/
cp /tmp/$libName/misc.c src/putty/
cp /tmp/$libName/pgssapi.c src/putty/
cp /tmp/$libName/pinger.c src/putty/
cp /tmp/$libName/portfwd.c src/putty/
cp /tmp/$libName/proxy.c src/putty/
cp /tmp/$libName/psftp.c src/putty/
cp /tmp/$libName/settings.c src/putty/
cp /tmp/$libName/sftp.c src/putty/
cp /tmp/$libName/ssh.c src/putty/
cp /tmp/$libName/sshaes.c src/putty/
cp /tmp/$libName/ssharcf.c src/putty/
cp /tmp/$libName/sshblowf.c src/putty/
cp /tmp/$libName/sshbn.c src/putty/
cp /tmp/$libName/sshcrc.c src/putty/
cp /tmp/$libName/sshcrcda.c src/putty/
cp /tmp/$libName/sshdes.c src/putty/
cp /tmp/$libName/sshdh.c src/putty/
cp /tmp/$libName/sshdss.c src/putty/
cp /tmp/$libName/sshgssc.c src/putty/
cp /tmp/$libName/sshmd5.c src/putty/
cp /tmp/$libName/sshpubk.c src/putty/
cp /tmp/$libName/sshrand.c src/putty/
cp /tmp/$libName/sshrsa.c src/putty/
cp /tmp/$libName/sshsh256.c src/putty/
cp /tmp/$libName/sshsh512.c src/putty/
cp /tmp/$libName/sshsha.c  src/putty/
cp /tmp/$libName/sshzlib.c src/putty/
cp /tmp/$libName/time.c src/putty/
cp /tmp/$libName/timing.c src/putty/
cp /tmp/$libName/tree234.c src/putty/
cp /tmp/$libName/unix/uxagentc.c src/putty/
cp /tmp/$libName/unix/uxcons.c src/putty/
cp /tmp/$libName/unix/uxgss.c src/putty/
cp /tmp/$libName/unix/uxmisc.c src/putty/
cp /tmp/$libName/unix/uxnet.c src/putty/
cp /tmp/$libName/unix/uxnoise.c src/putty/
cp /tmp/$libName/unix/uxproxy.c src/putty/
cp /tmp/$libName/unix/uxsel.c src/putty/
cp /tmp/$libName/unix/uxsftp.c src/putty/
cp /tmp/$libName/unix/uxstore.c src/putty/
cp /tmp/$libName/version.c src/putty/
cp /tmp/$libName/wildcard.c src/putty/
cp /tmp/$libName/x11fwd.c src/putty/

# copy .h files
mkdir -p src/include
cp /tmp/$libName/*.h src/include
mkdir -p src/include/charset/
cp /tmp/$libName/charset/*.h src/include/charset/
mkdir -p src/include/windows/
cp /tmp/$libName/windows/*.h src/include/windows/
mkdir -p src/include/unix/
cp /tmp/$libName/unix/*.h src/include/unix/
mkdir -p src/include/macosx/
cp /tmp/$libName/macosx/*.h src/include/macosx/


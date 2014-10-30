#!/bin/bash
# this script is used to download the source for a library
# parameters
# $1 library name
# $2 archive root, i.e. root directory after unzip/untar
# $3 archive file name
# $4 prefix of remote path, such that path to library is $4$3.   Note: remote path includes trailing separator

export genericlibname=$1
export archiveroot=$2
export zipname=$3
export remotepath=$4${zipname}

# Retrieve the source code for libssh2
# keep track of the original directory
pushd /tmp

# clean up any previous downloads
rm -f $zipname
rm -rf $genericlibname

echo downloading $remotepath to /tmp/$zipname
# machines have either 'wget' or 'curl', so we try both
wget -O $zipname $remotepath
if [ "$?" -ne "0" ]; then
	curl --location --output $zipname $remotepath
fi
if [ "$?" -ne "0" ]; then
  echo "Failed to download $remotepath"
  exit 1
fi

echo extracting $zipname
# unzip the downloaded archive
tar xzf $zipname

# change the name of the unzipped folder from, say, libssh2-1.4.3 to libssh2
mv $archiveroot $genericlibname

# remove the archive
rm -f $zipname

# restore to the original directory location
popd



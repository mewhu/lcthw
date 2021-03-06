set -e
# go somewhere safe
cd /tmp
# get the source to base APR 1.7.0
curl -L -O http://archive.apache.org/dist/apr/apr-1.7.0.tar.gz
# extract it and go into the source
tar -xzvf apr-1.7.0.tar.gz
cd apr-1.7.0
# configure, make, make install
./configure
make
make install
# reset and cleanup
cd /tmp
rm -rf apr-1.7.0 apr-1.7.0.tar.gz
# do the same with apr-util
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.6.1.tar.gz
# extract
tar -xzvf apr-util-1.6.1.tar.gz
cd apr-util-1.6.1
# configure, make, make install
./configure --with-apr=/usr/local/apr
# you need that extra parameter to configure because
# apr-util can't really find it because...who knows.
make
make install

#cleanup
cd /tmp
rm -rf apr-util-1.6.1* apr-1.7.0*

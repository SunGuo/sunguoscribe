cd ../facebook_scribe_source
export HADOOP_HOME=/usr/local/dip/depsys/hadoop-0.20.2-CDH3B4
export JAVA_HOME=/usr/java/jdk1.6.0_25
export LD_LIBRARY_PATH=/usr/local/dip/depsys/boost:/usr/lib:/usr/local/lib:/usr/lib64:/usr/local/lib64
export BOOST_ROOT=/usr/local/dip/depsys/boost/
export LD_LIBRARY_PATH=$HADOOP_HOME/hadoop-core-0.20.2-CDH3B4.jar:$JAVA_HOME/jre/lib/amd64:$JAVA_HOME/jre/lib/amd64/server:$JAVA_HOME/jre/lib/amd64/native_threads:$JAVA_HMOE/lib/amd64/server:/usr/local/dip/depsys/boost/lib/:/usr/local/dip/depsys/thrift-0.4.0/lib/:/usr/lib:/usr/local/lib:/usr/lib64:/usr/local/lib64
./bootstrap.sh --enable-hdfs   --enable-opt --with-boost=/usr/local/dip/depsys/boost/
./configure   --enable-opt   --enable-hdfs  --with-boost=/usr/local/dip/depsys/boost --with-thriftpath=/usr/local/dip/depsys/thrift-0.4.0/  --with-fb303path=/usr/local/dip/depsys/fb303-thrift-0.4.0   --with-hadooppath=$HADOOP_HOME  CPPFLAGS="-I$JAVA_HOME/include/ -I$JAVA_HOME/include/linux/ -I$HADOOP_HOME/src/c++/libhdfs/ -I/usr/local/dip/depsys/libevent-2.0.10-stable/include -I/usr/local/dip/depsys/thrift-0.4.0/include -I/usr/local/dip/depsys/thrift-0.4.0/include/thrift -I/usr/local/dip/depsys/fb303-thrift-0.4.0/include/thrift/fb303/" LDFLAGS="-ljvm -lhdfs -lboost_regex -L$JAVA_HOME/jre/lib/amd64/server -L/usr/local/include -L/usr/local/dip/depsys/libevent-2.0.10-stable/lib -L/usr/local/dip/depsys/boost/lib"  --prefix=/usr/local/dip/depsys/scribe-hdfs/
make
make install

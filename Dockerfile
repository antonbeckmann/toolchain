FROM ubuntu AS compilestage
USER root
RUN apt-get update && \
apt-get install -y \ 
libcurlpp-dev \
cmake  \
git \
build-essential \
libcurl4-openssl-dev \
wget &&  rm -rf /var/lib/apt/lists/* && \
mkdir git && \
cd git && \
git clone https://github.com/pocoproject/poco.git && \
cd poco/build && \
echo 111 && \
cmake .. && \
echo 111 && \
make && \
echo 111 && \
mkdir /build_libs && \
echo 111 && \
make DESTDIR=/build_libs install && \
cd /git && \
git clone https://github.com/jpbarrette/curlpp.git && \
cd /git/curlpp && \
mkdir build && \
cd build && \
cmake .. && \
make && \
make DESTDIR=/build_libs install && \
mkdir /build_libs/nlohmann &&\
cd /build_libs/nlohmann && \
wget https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp


FROM ubuntu
USER root
COPY --from=compilestage /build_libs/usr /usr 
COPY --from=compilestage /build_libs/nlohmann /nlohmann 

RUN apt-get update && \
apt-get install -y \ 
libcurlpp-dev \
libcurl4-openssl-dev \
cmake  \
build-essential && rm -rf /var/lib/apt/lists/*

COPY pocotest.cpp /test/code/
COPY jsontest.cpp /test/code/
COPY curlpptest.cpp /test/code/
COPY CMakeLists.txt /test/code/
COPY entrypoint.sh /
#find / -name PocoConfig.cmake
RUN ls /test/code && \
    mkdir /test/code/build && \
    cd /test/code/build && cmake .. && make && ls -l && \
    /test/code/build/pocotest && \
    /test/code/build/jsontest && \
    /test/code/build/curlpptest
RUN chmod +x entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

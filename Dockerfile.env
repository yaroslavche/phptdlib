FROM opensuse/leap:latest
LABEL maintainer="yaroslav429@gmail.com"

ENV container docker

RUN zypper -n install sudo which gcc gcc-c++ zlib gperf openssl openssl-devel cmake git php7 php7-devel php7-ctype php7-json &&\
    zypper clean

RUN cd $HOME &&\
    git clone https://github.com/tdlib/td.git &&\
    git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git &&\
    git clone https://github.com/nlohmann/json.git

RUN cd $HOME/PHP-CPP && \
    make &&\
    make install &&\
    make clean

RUN cd $HOME/json && mkdir build && cd build &&\
    cmake ..&&\
    make install &&\
    make clean &&\
    rm -rf $HOME/json/build

RUN cd $HOME/td && mkdir build && cd build &&\
    cmake -DCMAKE_BUILD_TYPE=Release .. &&\
    cmake --build . &&\
    cmake --build . --target install &&\
    rm -rf $HOME/td/build

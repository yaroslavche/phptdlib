FROM yaroslavche/phptdlib:latest
LABEL maintainer="yaroslav429@gmail.com"

ENV container docker
ENV HOME /root

COPY . $HOME/phptdlib

RUN zypper -n install php7-embed && zypper clean

RUN cd $HOME/phptdlib && \
    mkdir build && cd build && \
    cmake -DTDLIB_BUILD_TESTS=ON .. && \
    make && \
    make install

ENTRYPOINT ["php"]

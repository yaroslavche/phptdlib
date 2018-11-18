FROM yaroslavche/phptdlib:latest
LABEL maintainer="yaroslav429@gmail.com"

ENV container docker
ENV HOME /root

COPY . $HOME/phptdlib

RUN cd $HOME/phptdlib && \
    mkdir build && cd build && \
    cmake .. && \
    make

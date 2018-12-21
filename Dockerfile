FROM yaroslavche/phptdlib:latest
LABEL maintainer="yaroslav429@gmail.com"

ENV container docker
ENV HOME /root

COPY . $HOME/phptdlib

RUN cd $HOME/phptdlib && \
    mkdir build && cd build && \
    cmake -DUSE_SHARED_TD=ON -DUSE_SHARED_JSON=ON -DUSE_SHARED_PHPCPP=ON .. && \
    make && \
    make install

ENTRYPOINT ["php"]

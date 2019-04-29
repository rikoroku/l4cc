FROM ubuntu:xenial-20190425

RUN apt-get update && apt-get install -y gcc make git \
    binutils libc6-dev tig && rm -rf /var/lib/apt/lists/*

RUN mkdir /src && cd /src

WORKDIR /src

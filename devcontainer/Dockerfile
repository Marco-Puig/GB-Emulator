ARG VERSION=latest

FROM ubuntu:${VERSION}

WORKDIR /work

RUN apt update && apt install -y \
    g++ \
    gdb \
    make \
    cmake \
    git \
    check \
    build-essential \
    libsdl2-dev \
    libsdl2-ttf-dev

RUN mkdir /build

CMD [ "bash" ]

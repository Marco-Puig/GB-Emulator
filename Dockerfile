ARG VERSION=latest

FROM ubuntu:${VERSION}

COPY . /work

WORKDIR /work

RUN apt update && apt install -y \
    g++ \
    gdb \
    make \
    cmake \
    libsdl2-dev 

CMD [ "bash" ]

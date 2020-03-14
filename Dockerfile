FROM ubuntu:bionic AS build

RUN apt-get update && \
	apt-get install -y build-essential git cmake autoconf libtool pkg-config zlib1g-dev libbz2-dev

WORKDIR /hopa

COPY include/ /hopa/include/
COPY src/ /hopa/src/
COPY deps/ /hopa/deps/
COPY CMakeLists.txt /hopa/

WORKDIR /hopa/build

RUN cmake .. && make

FROM ubuntu:bionic AS release

WORKDIR /bin

COPY --from=build /hopa/build/src/hopa ./

ENTRYPOINT ["./hopa"]

FROM gcc:latest

RUN apt update -y
RUN apt upgrade -y
RUN apt-get -y install cmake git

COPY . .
WORKDIR .

# Run cmake configure & build process
RUN mkdir ./build
RUN cmake -B/build -S . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /build

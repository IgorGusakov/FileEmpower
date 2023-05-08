FROM ubuntu:latest
LABEL authors="igorgusakov"
# Fix timezone issue
#ENV TZ=Europe/London
#RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update -y
RUN apt upgrade -y
RUN apt install -y build-essential
RUN apt install -y clang
RUN #apt install -y gcc-12 g++-12 cpp-12
RUN #update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 --slave /usr/bin/g++ g++ /usr/bin/g++-12 --slave /usr/bin/gcov gcov /usr/bin/gcov-12
RUN apt-get -y install cmake git

COPY . .
WORKDIR .

# Run cmake configure & build process
RUN mkdir ./build
RUN cmake -B/build -S . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /build

ENTRYPOINT ["top", "-b"]
# get baseimage
FROM ubuntu:latest

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get install --reinstall ca-certificates -y

# install developer dependencies
RUN apt-get install -y git build-essential gcc g++ make cmake git pkg-config wget --no-install-recommends

# # install cmake
# RUN wget https://github.com/Kitware/CMake/releases/download/v3.24.2/cmake-3.24.2.tar.gz
# RUN tar -xvf cmake-3.24.2.tar.gz
# RUN cd cmake-3.24.2 && ./bootstrap && make -j4 && make install

# install vcpkg package manager
RUN git clone https://github.com/microsoft/vcpkg
RUN apt-get install -y curl zip
RUN vcpkg/bootstrap-vcpkg.sh

RUN /vcpkg/vcpkg install cppkafka

# copy files from local directory to container
COPY . /project

RUN mkdir /build
WORKDIR /build

RUN bash -c "cmake ../project -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build ."

CMD ./${TARGET}

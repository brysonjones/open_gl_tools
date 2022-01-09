# build the program in linux

mkdir -p build

cd build

cmake .. -DCMAKE_INSTALL_PREFIX=/opt/cmake-3.21.4-linux-x86_64/bin

cmake --build .
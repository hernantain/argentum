sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-image-ttf
sudo apt-get install libsdl2-ttf-de

sudo apt-get install libjsoncpp-dev

sudo apt-get -y install cmake
git clone https://github.com/msgpack/msgpack-c.git
cd msgpack-c
git checkout cpp_master
cmake -DMSGPACK_CXX[11]=ON .
sudo make install
cd ..

make clean
make
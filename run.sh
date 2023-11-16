if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake ..
make
./dungeon
rm dungeon
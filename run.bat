@echo off

REM Check if build directory exists, create it if not
if not exist "build" (
    mkdir build
)

cd build

del dungeon.exe
cmake ..
make

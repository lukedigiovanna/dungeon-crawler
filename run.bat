@echo off

REM Check if build directory exists, create it if not
if not exist "build" (
    mkdir build
)

REM Change directory to build and run CMake and make
cd build
cmake ..
make

REM Execute the program
dungeon.exe

REM Remove the executable
del dungeon.exe

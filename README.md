# GB-Emulator
Portable Gameboy Emulator 

## Current Progress - 8/4/2024 
![Screenshot 2024-08-05 023926](https://github.com/user-attachments/assets/08ff2b84-1ae5-4058-a48c-179aef9ccb41)

# Setup
## Download Libs and Tools
RUN apt update && apt install -y \ \
    g++ \ \
    gdb \ \
    make \ \
    cmake \ \
    git \ \
    check \ \
    build-essential \ \
    libsdl2-dev \ \
    libsdl2-ttf-dev

## Create Build
mkdir build, once in the src folder \
cd C:\GB-Emulator\src\build \
Then, run "cmake .." and after "make" or "Makefile"

## Run Build
In the /build directory, type "gbemu/gbemu" to run your newly created build

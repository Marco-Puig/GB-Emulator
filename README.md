# GB-Emulator

Portable Gameboy Emulator

## Current Progress - 8/6/2024

![image](https://github.com/user-attachments/assets/b52a1d06-f110-4402-aee2-a5ba466698b6)

# Setup

## Docker Instructions

### Build Docker Ubuntu Image

Run in directory with Dockerfile

```bash
docker build . -t emu_image
```

Confirm image is built

```bash
docker ps -a
```

### Run Container

```bash
docker run -it -v "<your-proj-dir>:/work" emu_image
```

## Build

Build Project in Build Directory

```bash
cd /build
cmake -S ../work/src -B /build
make
gbemu/gbemu
```

# GB-Emulator

Portable Gameboy Emulator

## Current Progress - 8/4/2024

![Screenshot 2024-08-05 023926](https://github.com/user-attachments/assets/08ff2b84-1ae5-4058-a48c-179aef9ccb41)

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

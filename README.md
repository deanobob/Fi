# Malon

## Installing on Ubuntu / MacOS

Peach requires SDL2 and Allegro5 libraries to be installed in /usr/local/lib.

The easiest way to do this is to compile both from source:

### SDL2

- Download from https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
- Extract to directory and open terminal in that location
- Execute following instructions:

```
./configure
mkdir build
cd build
cmake ..
sudo make install
```

### Allegro5

- Download from https://github.com/liballeg/allegro5/releases/download/5.2.6.0/allegro-5.2.6.0.tar.gz
- Extract to directory and open terminal in that location
- Execute following instructions:

```
mkdir build
cd build

# IF RUNNING ON UBUNTU
  sudo apt install libx11-dev
  sudo apt install libgl1-mesa-dev
  sudo apt install libxcursor-dev
  sudo apt install libpng-dev
  sudo apt install libfreetype-dev

cmake ..
sudo make install
```

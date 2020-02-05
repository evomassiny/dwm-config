#!/bin/bash

BASE_DIR=/home/yvesmo/bin/dwm

# dwm build dependancies
sudo apt install gcc make libx11-dev libxft-dev libxinerama-dev

mkdir -p $BASE_DIR

# DWM basic
cd dwm-6.2/
make clean
make
sudo make install
cd $BASE_DIR

cd dwmstatus/
make clean
make
sudo make install
cd $BASE_DIR

cd st-0.8.2/
make clean
make
sudo make install
cd $BASE_DIR

cd dmenu-4.9/
make clean
make
sudo make install
cd $BASE_DIR

sudo cp $BASE_DIR/dwm.desktop /usr/share/xsessions/dwm.desktop

# ecosystem
# * mupdf: pdf viewer
# * maim: screenshot utility
# * sxiv: image viewer
# * pavucontrol: sound I/O manager for pulseaudio
# * firejail for isolation
sudo apt install mupdf sxiv maim pavucontrol firejail

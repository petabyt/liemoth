#!/bin/sh

# Posix script to compile standalone.c
# and run it into camera connected via
# WiFi

make minimalonly file=standalone.c NOWRITE=1 NOCLEAN=1
echo "!run" > temp
echo "Writing files.."
printf 'root\nput test.bin test.bin\nput temp temp\nexit\n' | ftp 192.168.42.1
rm temp

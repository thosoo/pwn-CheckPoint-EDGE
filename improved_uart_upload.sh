#!/usr/local/bin/kermit
# serial programmer CH341A 3,3v mod
# CheckPoint 1000n u-boot serial file transfer kernel loading
set line /dev/ttyUSB0
set speed 115200
set carrier-watch off
set handshake none
set flow-control none
robust
set file type bin
set file name lit
set rec pack 1000
set send pack 1000
set window 5

echo {improve serial baudrate}
PAUSE 2
OUTPUT setenv download_baudrate 460800\{13}
PAUSE 1
OUTPUT setenv baudrate 460800\{13}
PAUSE 2
set speed 460800
PAUSE 1
OUTPUT \{13}
OUTPUT loadb $(loadaddr) 460800\{13}
send oct19077 
INPUT 180 {\{13}\{10}Sbox4_cm# }
IF FAIL STOP 1 INPUT timeout

echo {degrade serial baudrate OpenWrt console}
PAUSE 1
OUTPUT setenv baudrate 115200\{13}
PAUSE 3
set speed 115200
PAUSE 1

echo {connect minicom and bootkernel}
#OUTPUT bootoctlinux $(loadaddr)
QUIT

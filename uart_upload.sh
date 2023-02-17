#!/usr/local/bin/kermit

set line /dev/tty.usbserial-A600eZVP
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

echo {loading file}
PAUSE 1

OUTPUT loadb $(loadaddr) 115200\{13}
send boot-strip 
INPUT 180 {\{13}\{10}Sbox4_cm# }
IF FAIL STOP 1 INPUT timeout

echo {running kernel}
PAUSE 1
OUTPUT bootoctlinux $(loadaddr)\{13}
c

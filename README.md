
```
                          Yyy                 yyY    
                           YYYYYYYyyyyyyyYYYYYYY     
                            YYYYY#########YYYYY      
                             YYY#    ???  #YYY       
                              YY#   ( O)  #YY        
                               Y#    ~~   #Y         
                               YY#########YY         
                          @@@  YYYYYYYYYYYYY  @@@    
                          @@@@ YYYYYYYYYYYYY @@@@    
                          @@@@ YYYYYYYYYYYYY @@@@    
                           @@@@@@@@@@@@@@@@@@@@@     
                            @@@@@@@@@@@@@@@@@@@      
                            VVV@@@@@@@@@@@@@VVV      
                            VV               VV      
                            V                 V      
                              SofaWare Embedded!     
                                    Sbox4  

		Boot Code Version: 15 (Build time: Feb  2 2011 - 12:53:34)

```
# pwn-CheckPoint-EDGE
This project is about taking control over the Check Point UTM-1 EDGE Series.

The Check Point UTM-1 EDGE Series series of devices has a Octeon Plus CN5010-SCP Processor with 128 MB RAM.These devices are still perfectly usable, however, Check Point has deprecated them long ago. With their shady business model (*service plans for firmware updates*) these devices run age old firmware. Additionally, they ignore emails when requesting source code to GPL licensed code, such as U-Boot. (**Argghh GPL Violators..**)

## Chipset

This applies to the UTM-1 EDGE NW ADSL:

| Chip                          | Purpose            |
| ----------------------------- | ------------------ |
| Cavium Octeon Plus CN5010-SCP | Processor          |
| Marvell 98DX-LKJ1             | Switch             |
| Marvell 88E1240-TAH2          | WAN                |
| Marvell 88E1111-BAB1          | WAN?               |
| Spansion S29AL016J70TFI02     | Flash              |
| ST 3243EC                     | RS-232             |
| NEC (uPD)720114               | USB 2.0            |
| DS1337                        | RTC                |
| w83l786g                      | Temperature sensor |
| Pericom PI7C9X                | PCI-E Controller   |
| Atheros AR5B97                | Wireless           |
| Microchip 24CO2               | EEPROM             |

## Getting the serial port

On all of the models, there is a serial port on the outside of the device. This serial port does only deliver some no so useful diagnostics and are kind of worthless. You can not get to the bootloader and can also not get a shell for root login.

A second serialport can be found inside of the device. When connecting to the serialport with *115200* baudrate and starting the device, you only see a few lines of U-Boot. Then, this serial port goes blank aswell.

```
U-Boot 1.1.1  SDK 1.9 (Development build) (Build time: Feb  2 2011 - 12:54:14)

row bits: 13, col bits: 10, banks: 4, ranks: 1, dram width: 16, size: 128 MB
CUST_N100 board revision major:2, minor:0, serial #: unknown
OCTEON CN5010-SCP pass 1.1, Core clock: 500 MHz, DDR clock: 331 MHz (662 Mhz data rate)
Warning: Board descriptor tuple not found in eeprom, using defaults
PAL rev: 0.00, MCU rev: 0.00, CPU voltage: 0.00
w83l786g_gpio_mode_setting emtry
w83l786g_gpio_1_5_output_mode_control emtry
w83l786g_gpio_1_7_output_default emtry
w83l786g_gpio_io_def emtry
DRAM:  128 MB
```

After some random shorting of pins, the debug pins were found in between the heatsink and the DSL board. Shorting them using a jumper/cable results in this serial port staying alive.

Well.., hello!


```
U-Boot 1.1.1  SDK 1.9 (Development build) (Build time: Feb  2 2011 - 12:54:14)

row bits: 13, col bits: 10, banks: 4, ranks: 1, dram width: 16, size: 128 MB
CUST_N100 board revision major:2, minor:0, serial #: unknown
OCTEON CN5010-SCP pass 1.1, Core clock: 500 MHz, DDR clock: 331 MHz (662 Mhz data rate)
Warning: Board descriptor tuple not found in eeprom, using defaults
PAL rev: 0.00, MCU rev: 0.00, CPU voltage: 0.00
w83l786g_gpio_mode_setting emtry
w83l786g_gpio_1_5_output_mode_control emtry
w83l786g_gpio_1_7_output_default emtry
w83l786g_gpio_io_def emtry
DRAM:  128 MB
Clearing DRAM...... done
Flash:  2 MB
BIST check passed.
Starting PCI
PCI Status: PCI 32-bit
PCI BAR 0: 0x00000000, PCI BAR 1: Memory 0x00000000  PCI 0xf8000000
Net:   octeth0, octeth1, octeth2
 Bus 0 (CF Card): not available  

SofaWare debug level: 1

                          Yyy                 yyY    
                           YYYYYYYyyyyyyyYYYYYYY     
                            YYYYY#########YYYYY      
                             YYY#    ???  #YYY       
                              YY#   ( O)  #YY        
                               Y#    ~~   #Y         
                               YY#########YY         
                          @@@  YYYYYYYYYYYYY  @@@    
                          @@@@ YYYYYYYYYYYYY @@@@    
                          @@@@ YYYYYYYYYYYYY @@@@    
                           @@@@@@@@@@@@@@@@@@@@@     
                            @@@@@@@@@@@@@@@@@@@      
                            VVV@@@@@@@@@@@@@VVV      
                            VV               VV      
                            V                 V      
                              SofaWare Embedded!     
                                    Sbox4  

		Boot Code Version: 15 (Build time: Feb  2 2011 - 12:53:34)


<<***** BLOB Details *****>>
LAN MAC                : REDACTED
DMZ MAC                : REDACTED
WAN MAC                : REDACTED
License Key            : REDACTED
Activation Key         : REDACTED
Serial Num             : N/A 
Part Num               : REDACTED 
Vendor Mask            : 0x00002000 
Number of SFP Ports    : 0 
Number of USB Ports    : 1 
Number of Switch Ports : 4 
WLAN Region            : WORLD 
DSL Modem              : Yes 
ANNEX                  : B 


 0 
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
Sbox4_cm# <INTERRUPT>
```

The autoboot timer was set to 0 in this device such that it should boot immediately, however, spamming `CTRL+C` helps.

## The U-Boot environment

Commands available in U-Boot

```
Sbox4_cm# ?
?       - alias for 'help'
askenv  - get environment variables from stdin
autoscr - run script from memory
base    - print or set address offset
bootelf - Boot from an ELF image in memory
bootoct - Boot from an Octeon Executive ELF image in memory
bootoctelf - Boot a generic ELF image in memory. NOTE: This command does not support
             simple executive applications, use bootoct for those.
bootoctlinux - Boot from a linux ELF image in memory
bootp   - boot image via network using BootP/TFTP protocol
cmp     - memory compare
coninfo - print console devices and informations
cp      - memory copy
crc32   - checksum calculation
date    - get/set/reset date & time
dhcp    - invoke DHCP client to obtain IP/boot params
dx106     - DX106 utility commands
88e1240     - 88E1240 utility commands
echo    - echo args to console
eeprom  - EEPROM sub-system
erase   - erase FLASH memory
ext2load- load binary file from a Ext2 filesystem
ext2ls  - list files in a directory (default /)
fatinfo - print information about filesystem
fatload - load binary file from a dos filesystem
fatloadalloc - load binary file from a dos filesystem, and allocate
          a named bootmem block for file data
fatls   - list files in a directory (default /)
flinfo  - print FLASH memory information
freeprint    - Print list of free bootmem blocks
frtest   - Test reset button.
gettemp   - get the temparature of board
getvoltage   - get the CPU voltage of board
go      - start application at address 'addr'
gpio    - get/set gpio
gpioctrl   - control gpio 
gpioexpctrl   - control expanded gpio 
gunzip  - Uncompress an in memory gzipped file
help    - print online help
hwm     - get hardware voltage/temperature status
icrc32  - checksum calculation
ide     - IDE sub-system
ide_test  - test CF write
iloop   - infinite loop on address range
imd     - i2c memory display
imm     - i2c memory modify (auto-incrementing)
imw     - memory write (fill)
inm     - memory modify (constant address)
iprobe  - probe to discover valid I2C chip addresses
itest	- return true/false on integer compare
 
loadb   - load binary file over serial line (kermit mode)
loop    - infinite loop on address range
md      - memory display
md5   - MD5 hash calculation
mii     - MII utility commands
mm      - memory modify (auto-incrementing)
mtest   - simple RAM test
mw      - memory write (fill)
namedalloc    - Allocate a named bootmem block
namedfree    - Free a named bootmem block
namedprint    - Print list of named bootmem blocks
nand    - NAND sub-system
nm      - memory modify (constant address)
pci     - list and access PCI Configuraton Space
ping    - send ICMP ECHO_REQUEST to network host
printenv- print environment variables
protect - enable or disable FLASH write protection
read64    - read 64 bit word from 64 bit address
read64b    - read 8 bit word from 64 bit address
read64l    - read 32 bit word from 64 bit address
read64s    - read 16 bit word from 64 bit address
read_cmp    - read and compare memory to val
reset   - Perform RESET of the CPU
run     - run commands in an environment variable
saveenv - save environment variables to persistent storage
setenv  - set environment variables
sleep   - delay execution for some time
sofaware_blob_reset - SofaWare BLOB reset
sofaware_blob_update - SofaWare BLOB update
sofaware_preset_cfg_reset - Reset SofaWare preset configuration file 
sofaware_reset2def - reset 2 defaults
sofaware_restore_image - restore SofaWare primary firmware from secondary firmware
sofaware_show_info - Print SofaWare information 
sofaware_start - SofaWare start
sofaware_tftpload - load image via network using TFTP protocol
spierase
spieraseall
spiinfo
spiinit
spiread
spireaddeviceid
spiwritefile
tftpboot- boot image via network using TFTP protocol
tlv_eeprom  - EEPROM data parsing for ebt3000 board
version - print monitor version
write64    - write 64 bit word to 64 bit address
write64b    - write 8 bit word to 64 bit address
write64l    - write 32 bit word to 64 bit address
write64s    - write 16 bit word to 64 bit address
```

Environment variables

```
Sbox4_cm# printenv  
bootdelay=0
baudrate=115200
download_baudrate=115200
bootloader_flash_update=protect off $(uboot_flash_addr) +$(uboot_flash_size);erase $(uboot_flash_addr) +$(uboot_flash_size);cp.b $(fileaddr) $(uboot_flash_addr) $(uboot_flash_size);run nuke_env
burn_app=erase $(flash_unused_addr) +$(filesize);cp.b $(fileaddr) $(flash_unused_addr) $(filesize)
bf=bootoct $(flash_unused_addr) forceboot numcores=$(numcores)
nuke_env=protect off $(env_addr) +$(env_size); erase $(env_addr) +$(env_size)
linux_cf=fatload ide 0 $(loadaddr) vmlinux.64;bootoctlinux $(loadaddr)
ls=fatls ide 0
autoload=n
autotest=1
ipaddr=192.168.10.1
ethact=octeth1
loadaddr=0x5700000
numcores=1
stdin=serial
stdout=serial
stderr=serial
env_addr=0xbfbe0000
env_size=0x20000
flash_base_addr=0xbfa00000
flash_size=0x200000
uboot_flash_addr=0xbfa40000
uboot_flash_size=0xa0000
flash_unused_addr=0xbfae0000
flash_unused_size=0x100000
blob_mac=REDACTED
blob_license=REDACTED
blob_activation_key=REDACTED
blob_vendor_mask=0x00002000
blob_part_number=REDACTED
blob_sfp_ports=0
blob_usb_ports=1
blob_switch_ports=4
blob_wlan_region=WORLD
blob_adsl_annex=B
sw_user_src=native
sw_kernel_src=native
sw_tftp_any_file=no
sw_test_mode=no
sw_tftpsrvmode=no
sw_pri_firm=firm1
sw_sec_firm=firm0
sw_serial_console=internal
ethaddr=REDACTED

Environment size: 1380/131068 bytes
```

## Booting Sofaware

Booting the software firmware can be achieved by executing `sofaware_start`. It seems that the firmware is stored in GZIP format twice on NAND.

```
Sbox4_cm# sofaware_start
Read primary dsl header from flash
VNAND: vnand_scan(): initialize Virtual NAND driver v1.2 25/10/09
VNAND: build_translate_table(): NAND bad block at 590 (oob bad block type = 0x0)
VNAND: build_translate_table(): NAND bad block at 770 (oob bad block type = 0x0)
VNAND: build_translate_table(): bad block 590 remap to block 1004
VNAND: build_translate_table(): bad block 770 remap to block 1005
VNAND: build_translate_table(): NAND check did find bad blocks
128 MiB
dsl main firmware is OK
Reading PRIMARY firmware header from 43384832...
Image  size: 12360587 bytes
Reading PRIMARY firmware...
Verify PRIMARY firmware ...
PRIMARY firmware OK

<<***** SofaWare PRIMARY Image Details *****>>
Vendor Mask             : 0x2020
Version Num             : "8.2.33"
File Type               : "SofaWare Firmware" (1) 
Total File Size         : 0x00bc9ae3
Image Size              : 0x00bc9a63
Run Image Size          : 0x0033aa63
Unzipped Run Image Size : 0x00741cfb
Zip Type                : "GZIP"
Run Address             : 0x02800000

Unzip image to address 0x02800000 ...
Running image from address 0x02800000 (cores 1)...
argv[2]: numcores=1
argv[3]: mtdparts=phys_mapped_flash:64k@0x7d0000(cfgfile)
ELF file is 64 bit
Attempting to allocate memory for ELF segment: addr: 0xffffffff80100000 (adjusted to: 0x0000000000100000), size 0x621dd8
Allocated memory for ELF segment: addr: 0xffffffff80100000, size 0x621dd8
Processing PHDR 0
  Loading 5f2980 bytes at ffffffff80100000
  Clearing 2f458 bytes at ffffffff806f2980
## Loading Linux kernel with entry point: 0xffffffff8053f210 ...
** SofaWare boot information (core 0) ** 
* license (blob):           "REDACTED"
* activation key (blob):    "REDACTED"
* vendor mask (blob):       0x2000
* pn (blob):                "REDACTED"
* sn (blob):                ""
* SFP ports (blob):         0x0
* USB ports (blob):         0x1
* Switch ports (blob):      0x4
* WLAN Region (blob):         "WORLD"
* DSL Modem (blob):                "Yes"
* ANNEX (blob):                "B"
* extra params 1 (blob):    ""
* extra params 2 (blob):    ""
* extra params 3 (blob):    ""
* extra params 4 (blob):    ""
* extra params 5 (blob):    ""
* extra params 6 (blob):    ""
* extra params 7 (blob):    ""
* extra params 8 (blob):    ""
* default ip:               192.168.10.1
* sub model:                0x0
* image version:            "8.2.33"
* firmware file name:       "firm1"
* kernel image size:        7609595
* firmware image offset:           12451840
* romdisk offset:           3386123
* image crc:                0xEC45BA61
* loader ver:               15
* test mode:                1
* debug:                    1
* safe@ user source:        1
* safe@ kernel source:      1
* default lan ip:           ""
* default wan ip:           ""
* debug host ip:            ""
* debug host port:          "0"
**************************************** 
Bootloader: Done loading app on coremask: 0x1
Linux version 2.6.27.7-Cavium-Octeon (rapson@apu.sofaware.com) (gcc version 4.3.3 (Cavium Networks Version: 1_9_0 build 80) ) #4 SMP Thu Jan 20 14:03:04 IST 2011
CVMSEG size: 2 cache lines (256 bytes)
CPU revision is: 000d0601 (Cavium Octeon)
Checking for the multiply/shift bug... no.
Checking for the daddiu bug... no.
Determined physical RAM map:
 memory: 0000000007400000 @ 0000000000800000 (usable)
Wasting 114688 bytes for tracking 2048 unused pages
Initrd not found or empty - disabling initrd
Zone PFN ranges:
  DMA      0x00000800 -> 0x00100000
  Normal   0x00100000 -> 0x00100000
Movable zone start PFN for each node
early_node_map[1] active PFN ranges
    0: 0x00000800 -> 0x00007c00
Built 1 zonelists in Zone order, mobility grouping on.  Total pages: 29290
Kernel command line:  bootoctlinux 0x02800000 numcores=1 mtdparts=phys_mapped_flash:64k@0x7d0000(cfgfile) console=ttyS1,115200
Primary instruction cache 32kB, virtually tagged, 4 way, 64 sets, linesize 128 bytes.
Primary data cache 16kB, 64-way, 2 sets, linesize 128 bytes.
PID hash table entries: 512 (order: 9, 4096 bytes)
Console: colour dummy device 80x25
console [ttyS1] enabled
Dentry cache hash table entries: 16384 (order: 5, 131072 bytes)
Inode-cache hash table entries: 8192 (order: 4, 65536 bytes)
Memory: 114800k/118784k available (4393k kernel code, 3820k reserved, 1490k data, 206k init, 0k highmem)
Calibrating delay using timer specific routine.. 1000.89 BogoMIPS (lpj=5004497)
Mount-cache hash table entries: 256
Checking for the daddi bug... no.
Brought up 1 CPUs
net_namespace: 1208 bytes
xor: measuring software checksum speed
   8regs     :   814.800 MB/sec
   8regs_prefetch:   752.800 MB/sec
   32regs    :  1140.800 MB/sec
   32regs_prefetch:  1056.000 MB/sec
xor: using function: 32regs (1140.800 MB/sec)
NET: Registered protocol family 16
Enabling Octeon big bar support
PCI Status: PCI 32-bit
PCI Clock: 66 MHz
SCSI subsystem initialized
usbcore: registered new interface driver usbfs
usbcore: registered new interface driver hub
usbcore: registered new device driver usb
pci 0000:01:00.0: PME# supported from D0 D1 D3hot
pci 0000:01:00.0: PME# disabled
pci 0000:00:00.0: PCI bridge, secondary bus 0000:01
pci 0000:00:00.0:   IO window: disabled
pci 0000:00:00.0:   MEM window: 0xf0000000-0xf00fffff
pci 0000:00:00.0:   PREFETCH window: disabled
pci 0000:00:01.0: PCI bridge, secondary bus 0000:02
pci 0000:00:01.0:   IO window: disabled
pci 0000:00:01.0:   MEM window: disabled
pci 0000:00:01.0:   PREFETCH window: disabled
PCI: Enabling device 0000:00:00.0 (0000 -> 0002)
bus: 00 index 0 io port: [4000, ffffffff]
bus: 00 index 1 mmio: [11b00f0000000, 11b0130000000]
bus: 01 index 0 mmio: [0, 0]
bus: 01 index 1 mmio: [11b00f0000000, 11b00f00fffff]
bus: 01 index 2 mmio: [0, 0]
bus: 01 index 3 mmio: [0, 0]
bus: 02 index 0 mmio: [0, 0]
bus: 02 index 1 mmio: [0, 0]
bus: 02 index 2 mmio: [0, 0]
bus: 02 index 3 mmio: [0, 0]
NET: Registered protocol family 2
IP route cache hash table entries: 1024 (order: 1, 8192 bytes)
TCP established hash table entries: 4096 (order: 4, 65536 bytes)
TCP bind hash table entries: 4096 (order: 4, 65536 bytes)
TCP: Hash tables configured (established 4096 bind 4096)
TCP reno registered
NET: Registered protocol family 1
/proc/octeon_perf: Octeon performace counter interface loaded
Octeon watchdog driver loaded with a timeout of 8589 ms.
OcteonUSB: Detected 1 ports
OcteonUSB OcteonUSB.0: Octeon Host Controller
OcteonUSB OcteonUSB.0: new USB bus registered, assigned bus number 1
OcteonUSB OcteonUSB.0: irq 64, io mem 0x00000000
usb usb1: configuration #1 chosen from 1 choice
hub 1-0:1.0: USB hub found
hub 1-0:1.0: 1 port detected
usb usb1: New USB device found, idVendor=1d6b, idProduct=0002
usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
usb usb1: Product: Octeon Host Controller
usb usb1: Manufacturer: Linux 2.6.27.7-Cavium-Octeon Octeon USB
usb usb1: SerialNumber: OcteonUSB.0
OcteonUSB: Registered HCD for port 0 on irq 64
HugeTLB registered 2 MB page size, pre-allocated 0 pages
VFS: Disk quotas dquot_6.5.1
Dquot-cache hash table entries: 512 (order 0, 4096 bytes)
squashfs: version 3.4 (2008/08/26) Phillip Lougher
Installing knfsd (copyright (C) 1996 okir@monad.swb.de).
JFFS2 version 2.2. (NAND) © 2001-2006 Red Hat, Inc.
fuse init (API version 7.9)
msgmni has been set to 224
async_tx: api initialized (sync-only)
io scheduler noop registered
io scheduler cfq registered (default)
pci_hotplug: PCI Hot Plug PCI Core version: 0.5
fakephp: Fake PCI Hot Plug Controller Driver
Generic LED driver initialize
usb 1-1: new high speed USB device using OcteonUSB and address 2
usb 1-1: configuration #1 chosen from 1 choice
hub 1-1:1.0: USB hub found
hub 1-1:1.0: 4 ports detected
usb 1-1: New USB device found, idVendor=0409, idProduct=005a
usb 1-1: New USB device strings: Mfr=0, Product=0, SerialNumber=0
SofaWare LED driver initialize (test mode)
Initialize DSL driver 
Serial: 8250/16550 driver2 ports, IRQ sharing disabled
loop: module loaded
PPP generic driver version 2.4.2
PPP Deflate Compression module registered
PPP BSD Compression module registered
NET: Registered protocol family 24
PPPoL2TP kernel driver, V1.0
IMQ driver loaded successfully.
	Hooking IMQ before NAT on PREROUTING.
	Hooking IMQ after NAT on POSTROUTING.
Init ADSL control eth device
cavium-ethernet: Cavium Networks Octeon SDK version 1.9.0, build 312
Interface 0 has 3 ports (RGMII)
Enabling packet I/O on interface 0
i2c /dev entries driver
eth1: 100 Mbps Full duplex, port  0, queue  0
Uniform Multi-Platform E-IDE driver
Driver 'sd' needs updating - please use bus_type methods
Driver 'sr' needs updating - please use bus_type methods
Fusion MPT base driver 3.04.07
Copyright (c) 1999-2008 LSI Corporation
Fusion MPT SPI Host driver 3.04.07
physmap platform flash device: 00200000 at 1fa00000
physmap-flash physmap-flash.0: map_probe failed
NAND flash(on Octeon BootBus) driver for linux by GIGABYTE
Something found on bootbus: 8-bit, base=1c000000
VNAND: vnand_scan(): initialize Virtual NAND driver v1.2 25/10/09
NAND device: Manufacturer ID: 0xec, Chip ID: 0xf1 (Samsung NAND 128MiB 3,3V 8-bit)
Scanning device for bad blocks
Bad eraseblock 590 at 0x049c0000
Bad eraseblock 770 at 0x06040000
VNAND: build_translate_table(): NAND bad block at 590 (oob bad block type = 0x0)
VNAND: build_translate_table(): NAND bad block at 770 (oob bad block type = 0x0)
VNAND: build_translate_table(): bad block 590 remap to block 1004
VNAND: build_translate_table(): bad block 770 remap to block 1005
VNAND: build_translate_table(): NAND check did find bad blocks
Using static partition definition
Creating 10 MTD partitions on "nand_flash":
0x00000000-0x00040000 : "Config_File"
0x00040000-0x00d80000 : "SofaWare_JFFS"
0x01b60000-0x01d60000 : "Sec_DSL_Image"
0x01d60000-0x01d80000 : "Pri_DSL_Image_Hdr"
0x01d80000-0x04b80000 : "SofaWare_Image_1"
0x01d80000-0x04b80000 : "ROMDISK"
0x01d80000-0x04b80000 : "SofaWare_Image_0"
0x06380000-0x07d80000 : "SofaWare_MMAP"
0x04b800a8-0x06380000 : "CTERA"
mtd: partition "CTERA" doesn't start on an erase block boundary -- force read-only
0x04b80000-0x06380000 : "CTIMAGE"
usbcore: registered new interface driver cdc_acm
cdc_acm: v0.26:USB Abstract Control Model driver for USB modems and ISDN adapters
usbcore: registered new interface driver usblp
usbcore: registered new interface driver cdc_wdm
Initializing USB Mass Storage driver...
usbcore: registered new interface driver usb-storage
USB Mass Storage support registered.
usbcore: registered new interface driver libusual
usbcore: registered new interface driver usbserial
usbserial: USB Serial support registered for generic
usbcore: registered new interface driver usbserial_generic
usbserial: USB Serial Driver core
usbserial: USB Serial support registered for cp2101
usbcore: registered new interface driver cp2101
cp2101: Silicon Labs CP2101/CP2102 RS232 serial adaptor driver v0.07
usbserial: USB Serial support registered for FTDI USB Serial Device
usbcore: registered new interface driver ftdi_sio
ftdi_sio: v1.4.3:USB FTDI Serial Converters Driver
usbserial: USB Serial support registered for IPWireless converter
usbcore: registered new interface driver ipwtty
ipw: IPWireless tty driver v0.3
usbserial: USB Serial support registered for GSM modem (1-port)
usbcore: registered new interface driver option
option: USB Driver for GSM modems: v0.7.2
usbserial: USB Serial support registered for pl2303
usbcore: registered new interface driver pl2303
pl2303: Prolific PL2303 USB to serial adaptor driver
usbserial: USB Serial support registered for Sierra USB modem
usbcore: registered new interface driver sierra
sierra: USB Driver for Sierra Wireless USB modems: v.1.3.2
rtc-ds1307 0-0068: rtc core: registered ds1337 as rtc0
md: linear personality registered for level -1
md: raid0 personality registered for level 0
md: raid1 personality registered for level 1
md: raid10 personality registered for level 10
raid6: int64x1    322 MB/s
raid6: int64x2    373 MB/s
raid6: int64x4    375 MB/s
raid6: int64x8    258 MB/s
raid6: using algorithm int64x4 (375 MB/s)
md: raid6 personality registered for level 6
md: raid5 personality registered for level 5
md: raid4 personality registered for level 4
md: faulty personality registered for level -5
device-mapper: ioctl: 4.14.0-ioctl (2008-04-23) initialised: dm-devel@redhat.com
u32 classifier
    Actions configured 
ip_tables: (C) 2000-2006 Netfilter Core Team
TCP cubic registered
NET: Registered protocol family 17
RPC: Registered udp transport module.
RPC: Registered tcp transport module.
802.1Q VLAN Support v1.8 Ben Greear <greearb@candelatech.com>
All bugs added by David S. Miller <davem@redhat.com>
serial8250: ttyS0 at MMIO 0x1180000000800 (irq = 42) is a 16550A
serial8250: ttyS1 at MMIO 0x1180000000c00 (irq = 43) is a 16550A
cf: Octeon bootbus compact flash driver version 2.0
cf: Compact flash found in bootbus region 3 (16 bit).
cf:  Serial  (0 sectors, 512 bytes/sector)
cf: Compact flash not detected.
md: Autodetecting RAID arrays.
md: Scanned 0 and added 0 devices.
md: autorun ...
md: ... autorun DONE.
Partition ROMDISK found. Index == 5
Partition SofaWare_Image_1 found. Index == 4
slave->mtd.index = 0x4
slave->mtd.name = SofaWare_Image_1
slave->mtd.erasesize = 0x20000
slave->mtd.size = 0x2e00000
slave->offset = 0x1d80000
Setting partition ROMDISK offset=0x2c9ab0b size=0x88f080 [erasesize=0x20000]
mtd: partition "ROMDISK" doesn't start on an erase block boundary -- force read-only
Setting partition SofaWare_Image_1 offset=0x2960000 size=0x2220000 [erasesize=0x20000]
mount_block_root: Trying fs ext3, name: /dev/root
mount_block_root: Trying fs ext2, name: /dev/root
mount_block_root: Trying fs squashfs, name: /dev/root
VFS: Mounted root (squashfs filesystem) readonly.
/sbin/rc starting
Mounting file systems
fsck 1.38 (30-Jun-2005)
Set date by real time clock
time-stamp 1.1: 06:54:06 (1612940046 sec)
Start reset button daemon
Mount /flash
Create /var/tmp/
Create /var/log/
Create /var/run/utmp
Create /var/etc/hostap
Create /var/etc/wpa_supplicant
Create /var/etc/ppp
Create /var/lock
Create /var/etc/mgetty+sendfax
Setting up loopback
Disabling IP forwarding
vpnt: module license 'unspecified' taints kernel.
VPNT: IPv4 over VPN Tunnel driver installed
Pre-Initialization is done for the device 0x23.
Pre-Initialization is done for the device 0xc.
Arrow Switch+Phy driver installed
ath_hal: 0.9.17.1 (AR5212, AR5416, RF5111, RF5112, RF2413, RF5413, RF2316, RF2317, DEBUG, REGOPS_FUNC, WRITE_EEPROM, 11D)
wlan: 0.8.4.2 (Atheros/multi-bss)
ath_rate_atheros: Copyright (c) 2001-2005 Atheros Communications, Inc, All Rights Reserved
ath_dev: Copyright (c) 2001-2007 Atheros Communications, Inc, All Rights Reserved
ath_pci: 0.9.4.5 (Atheros/multi-bss)
PCI: Enabling device 0000:01:00.0 (0000 -> 0002)
wifi0: Atheros 9287: mem=0x11b00f0000000, irq=44 hw_base=0x90011b00f0000000
wlan: mac acl policy registered
Create wlan0 interface
wlan0
Starting test mode
device eth0 entered promiscuous mode
device eth1 entered promiscuous mode
test_br: topology change detected, propagating
test_br: port 2(eth1) entering forwarding state
test_br: topology change detected, propagating
test_br: port 1(eth0) entering forwarding state


        Welcome to SofaWare SBOX4

(none) login: 
```


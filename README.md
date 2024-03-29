
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

The Check Point UTM-1 EDGE Series series of devices has a Octeon Plus CN5010-SCP Processor with 128 MB RAM. My variant has a 4 port switch, a WAN port, a DSL modem and even boasts a ExpressCard 54 slot. These devices are still perfectly usable, however, Check Point has deprecated them long ago. With their shady business model (*service plans for firmware updates*) these devices run age old firmware. Even their EULA says that [no Product, nor any portion thereof, may be used by or on behalf of,  accessed by, re-sold to, rented to, or distributed to any other party](https://www.checkpoint.com/support-services/software-license-agreement-limited-hardware-warranty/).

Additionally, they ignore emails with ease, when requesting source code to GPL licensed code, such as U-Boot. (**Argghh GPL Violators..**)

## Table of contents



## Chipset

This applies to the UTM-1 EDGE NW ADSL:

| Chip                          | Purpose              |
| ----------------------------- | -------------------- |
| Cavium Octeon Plus CN5010-SCP | Processor            |
| Marvell 98DX106-LKJ1          | Switch -> SMI        |
| Marvell 88E1240-TAH2          | PHY -> Switch        |
| Marvell 88E1111-BAB1          | PHY -> MII           |
| Spansion S29AL016J70TFI02     | Flash                |
| ST 3243EC                     | RS-232               |
| NEC (uPD)720114               | USB 2.0              |
| DS1337                        | RTC                  |
| w83l786g                      | Temperature sensor   |
| 2x Pericom PI7C9X111SL        | PCIe-PCI-Bridge      |
| Atheros AR5B97                | Wifi -> PCIe         |
| Microchip 24CO2               | EEPROM               |
| ikanos/conexant GS8120        | ADSL -> MII/SMI/SPI? |

## Getting the serial port

![Board](./images/board.jpg)

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

Booting the software firmware can be achieved by executing `sofaware_start`. It seems that the firmware is stored in GZIP format twice on NAND. The NAND is hiding behind a VNAND driver, which needs to be initialised first.

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

Unfortunately, the root account has a password..

## OpenWRT

But.. can it boot OpenWRT? Yes, it should.

At first, I was not able to boot via `tftpboot`, because I got `checksum bad` errors all over the place, even after rebooting my routers and switches, these issues remained. The USB port is also not available inside U-Boot. So I just transferred the initramfs via serial console and booted from that.

```
 sudo ./uartboot.script
loading file
Warning: terminal type unknown: "xterm-kitty"
Fullscreen file transfer display disabled.
SF
X to cancel file,  CR to resend current packet
Z to cancel group, A for status report
E to send Error packet, Ctrl-C to quit immediately: 
initramfs.bin => initramfs.bin
Size: 14663952, Type: binary
    File   Percent       Packet
    Bytes  Done     CPS  Length
 14663952  100%    6706       6  [OK]
ZB
## Total Size      = 0x00dfc110 = 14663952 Bytes
## Start Addr      = 0x05700000
Sbox4_cm# running kernel
Connecting to /dev/tty.usbserial-A600eZVP, speed 115200
 Escape character: Ctrl-\ (ASCII 28, FS): enabled
Type the escape character followed by C to get back,
or followed by ? to see other options.
----------------------------------------------------
bootoctlinux
ELF file is 64 bit
Attempting to allocate memory for ELF segment: addr: 0xffffffff81100000 (adjusted to: 0x0000000001100000), size 0x1f4a220
Allocated memory for ELF segment: addr: 0xffffffff81100000, size 0x1f4a220
Processing PHDR 0
  Loading dfab30 bytes at ffffffff81100000
  Clearing 114f6f0 bytes at ffffffff81efab30
## Loading Linux kernel with entry point: 0xffffffff8162eb60 ...
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
* image version:            ""
* firmware file name:       ""
* kernel image size:        0
* firmware image offset:           0
* romdisk offset:           168
* image crc:                0x0
* loader ver:               15
* test mode:                0
* debug:                    1
* safe@ user source:        1
* safe@ kernel source:      1
* default lan ip:           ""
* default wan ip:           ""
* debug host ip:            ""
* debug host port:          "0"
**************************************** 
Bootloader: Done loading app on coremask: 0x1
[    0.000000] Linux version 4.14.180 (builder@buildhost) (gcc version 7.5.0 (OpenWrt GCC 7.5.0 r11063-85e04e9f46)) #0 SMP Sat May 16 18:32:20 2020
[    0.000000] CVMSEG size: 2 cache lines (256 bytes)
[    0.000000] bootconsole [early0] enabled
[    0.000000] CPU0 revision is: 000d0601 (Cavium Octeon+)
[    0.000000] Checking for the multiply/shift bug... no.
[    0.000000] Checking for the daddiu bug... no.
[    0.000000] Determined physical RAM map:
[    0.000000]  memory: 0000000004c00000 @ 0000000003100000 (usable)
[    0.000000]  memory: 0000000001f4a220 @ 0000000001100000 (usable)
[    0.000000] Wasting 243712 bytes for tracking 4352 unused pages
[    0.000000] Initrd not found or empty - disabling initrd
[    0.000000] cvmx_helper_board_get_mii_address: Unknown board type 20011
[    0.000000] cvmx_helper_board_get_mii_address: Unknown board type 20011
[    0.000000] cvmx_helper_board_get_mii_address: Unknown board type 20011
[    0.000000] Using internal Device Tree.
[    0.000000] software IO TLB: mapped [mem 0x0310b000-0x0314b000] (0MB)
[    0.000000] Primary instruction cache 32kB, virtually tagged, 4 way, 64 sets, linesize 128 bytes.
[    0.000000] Primary data cache 16kB, 64-way, 2 sets, linesize 128 bytes.
[    0.000000] Zone ranges:
[    0.000000]   DMA32    [mem 0x0000000000000000-0x00000000efffffff]
[    0.000000]   Normal   empty
[    0.000000] Movable zone start for each node
[    0.000000] Early memory node ranges
[    0.000000]   node   0: [mem 0x0000000000000000-0x0000000003049fff]
[    0.000000]   node   0: [mem 0x0000000003100000-0x0000000007cfffff]
[    0.000000] Initmem setup node 0 [mem 0x0000000000000000-0x0000000007cfffff]
[    0.000000] random: get_random_bytes called from 0xffffffff817586d8 with crng_init=0
[    0.000000] percpu: Embedded 18 pages/cpu s35632 r8192 d29904 u73728
[    0.000000] Built 1 zonelists, mobility grouping on.  Total pages: 31380
[    0.000000] Kernel command line:  bootoctlinux console=ttyS1,115200
[    0.000000] PID hash table entries: 512 (order: 0, 4096 bytes)
[    0.000000] Dentry cache hash table entries: 16384 (order: 5, 131072 bytes)
[    0.000000] Inode-cache hash table entries: 8192 (order: 4, 65536 bytes)
[    0.000000] Memory: 73592K/127272K available (5336K kernel code, 338K rwdata, 808K rodata, 8864K init, 16680K bss, 53680K reserved, 0K cma-reserved)
[    0.000000] SLUB: HWalign=128, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
[    0.000000] Hierarchical RCU implementation.
[    0.000000] 	CONFIG_RCU_FANOUT set to non-default value of 32
[    0.000000] 	RCU restricting CPUs from NR_CPUS=16 to nr_cpu_ids=1.
[    0.000000] RCU: Adjusting geometry for rcu_fanout_leaf=16, nr_cpu_ids=1
[    0.000000] NR_IRQS: 127
[ 2610.873231] clocksource: OCTEON_CVMCOUNT: mask: 0xffffffffffffffff max_cycles: 0xe6a171a037, max_idle_ns: 881590485102 ns
[ 2610.884090] Calibrating delay loop (skipped) preset value.. 1000.00 BogoMIPS (lpj=2000000)
[ 2610.892476] pid_max: default: 32768 minimum: 301
[ 2610.897097] Mount-cache hash table entries: 512 (order: 0, 4096 bytes)
[ 2610.903489] Mountpoint-cache hash table entries: 512 (order: 0, 4096 bytes)
[ 2610.911175] Checking for the daddi bug... no.
[ 2610.916477] Hierarchical SRCU implementation.
[ 2610.921484] smp: Bringing up secondary CPUs ...
[ 2610.925908] smp: Brought up 1 node, 1 CPU
[ 2610.933616] clocksource: jiffies: mask: 0xffffffff max_cycles: 0xffffffff, max_idle_ns: 7645041785100000 ns
[ 2610.943262] futex hash table entries: 256 (order: 3, 32768 bytes)
[ 2610.950523] NET: Registered protocol family 16
[ 2610.959830] Enabling Octeon big bar support
[ 2610.969914] PCI Status: PCI 32-bit
[ 2610.974171] PCI Clock: 66 MHz
[ 2611.007303] SCSI subsystem initialized
[ 2611.011411] usbcore: registered new interface driver usbfs
[ 2611.016880] usbcore: registered new interface driver hub
[ 2611.022151] usbcore: registered new device driver usb
[ 2611.027418] PCI host bridge to bus 0000:00
[ 2611.031415] pci_bus 0000:00: root bus resource [mem 0x11b00f0000000-0x11b0130000000] (bus address [0xf0000000-0x130000000])
[ 2611.042474] pci_bus 0000:00: root bus resource [io  0x4000-0xffffffff]
[ 2611.048975] pci_bus 0000:00: root bus resource [??? 0x00000000 flags 0x0]
[ 2611.055741] pci_bus 0000:00: No busn resource found for root bus, will use [bus 00-ff]
[ 2611.063749] pci 0000:00:00.0: enabling Extended Tags
[ 2611.068590] pci 0000:00:00.0: Enable PCIe Retrain Link quirk
[ 2611.074622] pci 0000:00:01.0: enabling Extended Tags
[ 2611.079478] pci 0000:00:01.0: Enable PCIe Retrain Link quirk
[ 2611.085437] pci 0000:00:00.0: bridge configuration invalid ([bus 00-00]), reconfiguring
[ 2611.093322] pci 0000:00:01.0: bridge configuration invalid ([bus 03-03]), reconfiguring
[ 2611.102183] pci 0000:00:00.0: BAR 8: assigned [mem 0x11b00f0000000-0x11b00f00fffff]
[ 2611.109733] pci 0000:00:01.0: BAR 8: assigned [mem 0x11b00f0100000-0x11b00f02fffff]
[ 2611.117332] pci 0000:00:01.0: BAR 9: assigned [mem 0x11b0100000000-0x11b01001fffff 64bit pref]
[ 2611.125914] pci 0000:00:01.0: BAR 7: assigned [io  0x4000-0x4fff]
[ 2611.131991] pci 0000:01:00.0: BAR 0: assigned [mem 0x11b00f0000000-0x11b00f000ffff 64bit]
[ 2611.140144] pci 0000:00:00.0: PCI bridge to [bus 01]
[ 2611.145078] pci 0000:00:00.0:   bridge window [mem 0x11b00f0000000-0x11b00f00fffff]
[ 2611.152709] pci 0000:00:01.0: PCI bridge to [bus 02]
[ 2611.157649] pci 0000:00:01.0:   bridge window [io  0x4000-0x4fff]
[ 2611.163720] pci 0000:00:01.0:   bridge window [mem 0x11b00f0100000-0x11b00f02fffff]
[ 2611.171351] pci 0000:00:01.0:   bridge window [mem 0x11b0100000000-0x11b01001fffff 64bit pref]
[ 2611.185939] clocksource: Switched to clocksource OCTEON_CVMCOUNT
[ 2611.193011] NET: Registered protocol family 2
[ 2611.198152] TCP established hash table entries: 1024 (order: 1, 8192 bytes)
[ 2611.205041] TCP bind hash table entries: 1024 (order: 3, 32768 bytes)
[ 2611.211430] TCP: Hash tables configured (established 1024 bind 1024)
[ 2611.217910] UDP hash table entries: 256 (order: 2, 24576 bytes)
[ 2611.223740] UDP-Lite hash table entries: 256 (order: 2, 24576 bytes)
[ 2611.230296] NET: Registered protocol family 1
[ 2611.415111] Crashlog allocated RAM at address 0x3f00000
[ 2611.422619] workingset: timestamp_bits=62 max_order=15 bucket_order=0
[ 2611.445917] squashfs: version 4.0 (2009/01/31) Phillip Lougher
[ 2611.451922] jffs2: version 2.2 (NAND) (SUMMARY) (LZMA) (RTIME) (CMODE_PRIORITY) (c) 2001-2006 Red Hat, Inc.
[ 2611.468926] io scheduler noop registered
[ 2611.472809] io scheduler deadline registered (default)
[ 2611.478551] octeon_gpio 1070000000800.gpio-controller: OCTEON GPIO driver probed.
[ 2611.486404] Serial: 8250/16550 driver, 16 ports, IRQ sharing enabled
[ 2611.495660] 1180000000800.serial: ttyS0 at MMIO 0x1180000000800 (irq = 41, base_baud = 31250000) is a OCTEON
[ 2611.506025] 1180000000c00.serial: ttyS1 at MMIO 0x1180000000c00 (irq = 42, base_baud = 31250000) is a OCTEON
[ 2611.515778] console [ttyS1] enabled
[ 2611.515778] console [ttyS1] enabled
[ 2611.522660] bootconsole [early0] disabled
[ 2611.522660] bootconsole [early0] disabled
[ 2611.531143] octeon_rng octeon_rng: Octeon Random Number Generator
[ 2611.549441] loop: module loaded
[ 2611.553395] of-flash 1f400000.nor: Can't get bank width from device tree
[ 2611.560550] libphy: mdio_octeon: probed
[ 2611.564472] mdio_octeon 1180000001800.mdio: Probed
[ 2611.569691] libphy: Fixed MDIO Bus: probed
[ 2611.574034] ehci_hcd: USB 2.0 'Enhanced' Host Controller (EHCI) Driver
[ 2611.580620] ehci-pci: EHCI PCI platform driver
[ 2611.585198] ehci-platform: EHCI generic platform driver
[ 2611.590685] ohci_hcd: USB 1.1 'Open' Host Controller (OHCI) Driver
[ 2611.596953] ohci-platform: OHCI generic platform driver
[ 2611.602524] usbcore: registered new interface driver usb-storage
[ 2611.608645] octeon_wdt: Initial granularity 5 Sec
[ 2611.623645] Interface 0 has 3 ports (RGMII)
[ 2611.632014] octeon-hcd 16f0010000000.usbc: controller reset failed (gintsts=0x7500dc6a) - retrying
[ 2611.759041] octeon-hcd 16f0010000000.usbc: controller reset failed (gintsts=0x7500dc6a) - retrying
[ 2611.887030] octeon-hcd 16f0010000000.usbc: controller reset failed (gintsts=0x7500dc6a) - retrying
[ 2612.015027] octeon-hcd 16f0010000000.usbc: controller reset failed (gintsts=0x7500dc6a) - retrying
[ 2612.077797] random: fast init done
[ 2612.143027] octeon-hcd 16f0010000000.usbc: controller reset failed (gintsts=0x7500dc6a) - retrying
[ 2612.271055] octeon-hcd: probe of 16f0010000000.usbc failed with error -1
[ 2612.278871] NET: Registered protocol family 10
[ 2612.286587] Segment Routing with IPv6
[ 2612.290444] NET: Registered protocol family 17
[ 2612.295032] bridge: filtering via arp/ip/ip6tables is no longer available by default. Update your scripts to load br_netfilter if you need this.
[ 2612.308042] 8021q: 802.1Q VLAN Support v1.8
[ 2612.312497] Bootbus flash: Setting flash for 2MB flash at 0x1fa00000
[ 2612.319049] phys_mapped_flash: Found 1 x16 devices at 0x0 in 8-bit bank. Manufacturer ID 0x000001 Chip ID 0x000049
[ 2612.329436] Amd/Fujitsu Extended Query Table at 0x0040
[ 2612.334636]   Amd/Fujitsu Extended Query version 1.3.
[ 2612.339722] number of CFI chips: 1
[ 2612.347160] OF: fdt: not creating '/sys/firmware/fdt': CRC check failed
[ 2612.361678] Freeing unused kernel memory: 8864K
[ 2612.366283] This architecture does not have kernel memory protection.
[ 2612.388489] init: Console is alive
[ 2612.392355] init: - watchdog -
[ 2612.409537] kmodloader: loading kernel modules from /etc/modules-boot.d/*
[ 2612.416880] kmodloader: done loading kernel modules from /etc/modules-boot.d/*
[ 2612.426941] init: - preinit -
[ 2612.632175] random: jshn: uninitialized urandom read (4 bytes read)
[ 2612.684740] random: jshn: uninitialized urandom read (4 bytes read)
[ 2612.725616] random: jshn: uninitialized urandom read (4 bytes read)
[ 2612.761975] IPv6: ADDRCONF(NETDEV_UP): eth0: link is not ready
Press the [f] key and hit [enter] to enter failsafe mode
Press the [1], [2], [3] or [4] key and hit [enter] to select the debug level
[ 2615.917630] procd: - early -
[ 2615.920976] procd: - watchdog -
[ 2616.509698] procd: - watchdog -
[ 2616.513372] procd: - ubus -
[ 2616.522784] random: ubusd: uninitialized urandom read (4 bytes read)
[ 2616.566839] random: ubusd: uninitialized urandom read (4 bytes read)
[ 2616.573755] random: ubusd: uninitialized urandom read (4 bytes read)
[ 2616.581636] procd: - init -
Please press Enter to activate this console.
[ 2617.046694] kmodloader: loading kernel modules from /etc/modules.d/*
[ 2617.067481] ip6_tables: (C) 2000-2006 Netfilter Core Team
[ 2617.080549] urngd: v1.0.2 started.
[ 2617.096691] ip_tables: (C) 2000-2006 Netfilter Core Team
[ 2617.116764] nf_conntrack version 0.5.0 (1024 buckets, 4096 max)
[ 2617.218242] xt_time: kernel timezone is -0000
[ 2617.240533] PPP generic driver version 2.4.2
[ 2617.254736] NET: Registered protocol family 24
[ 2617.271625] kmodloader: done loading kernel modules from /etc/modules.d/*
[ 2617.297785] random: crng init done
[ 2617.301277] random: 4 urandom warning(s) missed due to ratelimiting
[ 2625.093549] br-lan: port 1(eth0) entered blocking state
[ 2625.098889] br-lan: port 1(eth0) entered disabled state
[ 2625.104543] device eth0 entered promiscuous mode
[ 2625.166123] IPv6: ADDRCONF(NETDEV_UP): br-lan: link is not ready
[ 2625.254034] IPv6: ADDRCONF(NETDEV_UP): eth1: link is not ready



BusyBox v1.30.1 () built-in shell (ash)

  _______                     ________        __
 |       |.-----.-----.-----.|  |  |  |.----.|  |_
 |   -   ||  _  |  -__|     ||  |  |  ||   _||   _|
 |_______||   __|_____|__|__||________||__|  |____|
          |__| W I R E L E S S   F R E E D O M
 -----------------------------------------------------
 OpenWrt 19.07.3, r11063-85e04e9f46
 -----------------------------------------------------
=== WARNING! =====================================
There is no root password defined on this device!
Use the "passwd" command to set up a new password
in order to prevent unauthorized SSH logins.
--------------------------------------------------
root@OpenWrt:/# 

```

## Dumping flash

There is 2MB flash memory, where U-Boot and a failsafe U-Boot resides.

It can be dumped using the following command:

```
md.b 0xbfa00000 0x200000
```

This results in the memory being displayed on the serial console. The resulting log has to be processed using the [uboot-mdb-dump](https://github.com/gmbnomis/uboot-mdb-dump) script.

After processing the flash using binwalk, the two U-Boot versions are revealed.

```
$ binwalk dump.bin                  

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
239184        0x3A650         U-Boot version string, "U-Boot 1.1.1 (Development build, svnversion: u-boot:exported, exec:exported) (Build time: Feb 11 2011 - 11:42:25)"
239704        0x3A858         CRC32 polynomial table, big endian
762464        0xBA260         U-Boot version string, "U-Boot 1.1.1  SDK 1.9 (Development build) (Build time: Feb  2 2011 - 12:54:14)"
765480        0xBAE28         CRC32 polynomial table, big endian

```

Running `strings` on the flash dump, resulted in [this file](./strings-u-boot.txt).

## Dumping nand

As seen in the bootlog, the firmware is stored twice on NAND as a gzipped Archive. On every boot, this archive is verified and extracted.

These are the commands to access the nand from U-Boot.

```
nand    - NAND sub-system
nand info - show available NAND devices
nand init - Initialize NAND
nand device [dev] - show or set current device
nand read - addr off|partition size
nand write - addr off|partition size
    read/write 'size' bytes starting at offset 'off'
    to/from memory address 'addr', skipping bad blocks.
nand erase [clean] [off size] - erase 'size' bytes from
    offset 'off' (entire device if not specified)
nand bad - show bad blocks
nand dump[.oob] off - dump page
nand scrub - really clean NAND erasing bad blocks (UNSAFE)
nand markbad off - mark bad block at offset (UNSAFE)
nand biterr off - make a bit error at offset (UNSAFE)
nand lock [tight] [status]
    bring nand to lock state or display locked pages
nand unlock [offset] [size] - unlock section
```

As tftp was not accessible, the nand had to be dumped using the mdb method again. Because the RAM is limited (128 MB) and the NAND having the same size as the RAM, I figured that reading multiple sections would be a better idea. (This will take a day..)

```
setenv dump1 'nand read 0x02800000 0x0 0x1000000; md.b 0x02800000 0x1000000'
setenv dump2 'nand read 0x02800000 0x1000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump3 'nand read 0x02800000 0x2000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump4 'nand read 0x02800000 0x3000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump5 'nand read 0x02800000 0x3000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump6 'nand read 0x02800000 0x4000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump7 'nand read 0x02800000 0x5000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump8 'nand read 0x02800000 0x6000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump9 'nand read 0x02800000 0x7000000 0x1000000; md.b 0x02800000 0x1000000'
setenv dump_nand 'run dump1; run dump2;run dump3; run dump4; run dump5; run dump6; run dump7; run dump8; run dump9'
run dump_nand
```

Because the dump is made from multiple chunks, the original mdb script will not work anymore, because the address will not be correct anymore. Therefore, a [modified version has to be used](https://github.com/thosoo/uboot-mdb-dump/blob/master/uboot_mdb_to_image-no_addr_chk.py).

Binwalk the NAND dump revealed the following:

```
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
6160384       0x5E0000        JFFS2 filesystem, big endian
28994227      0x1BA6AB3       Copyright string: "Copyright 1995-1998 Mark Adler "
28999009      0x1BA7D61       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1455 bytes
28999450      0x1BA7F1A       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1237 bytes
28999787      0x1BA806B       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 34 bytes
28999865      0x1BA80B9       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 238 bytes
28999954      0x1BA8112       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1566 bytes
29000548      0x1BA8364       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 446 bytes
29000880      0x1BA84B0       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 70 bytes
29000973      0x1BA850D       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1003 bytes
29001410      0x1BA86C2       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 2083 bytes
29003546      0x1BA8F1A       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 501 bytes
29003906      0x1BA9082       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 478 bytes
29004251      0x1BA91DB       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 11754 bytes
29009768      0x1BAA768       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 266 bytes
29010070      0x1BAA896       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 14964 bytes
29015404      0x1BABD6C       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 455 bytes
29015787      0x1BABEEB       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 5771 bytes
29017647      0x1BAC62F       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 488 bytes
29017995      0x1BAC78B       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 478 bytes
29018337      0x1BAC8E1       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 478 bytes
29018684      0x1BACA3C       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1946 bytes
29019760      0x1BACE70       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1958 bytes
29020838      0x1BAD2A6       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 458 bytes
29021163      0x1BAD3EB       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 815 bytes
29021667      0x1BAD5E3       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 4641 bytes
29023264      0x1BADC20       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 11913 bytes
29028775      0x1BAF1A7       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 264 bytes
29028985      0x1BAF279       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 516 bytes
29029359      0x1BAF3EF       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1425 bytes
29030134      0x1BAF6F6       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1254 bytes
29030841      0x1BAF9B9       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1124 bytes
29031520      0x1BAFC60       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1126 bytes
29032201      0x1BAFF09       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1120 bytes
29032878      0x1BB01AE       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 291 bytes
29033116      0x1BB029C       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 13494 bytes
29039402      0x1BB1B2A       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 415932 bytes
29215141      0x1BDC9A5       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 532 bytes
29215456      0x1BDCAE0       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 21605 bytes
29223620      0x1BDEAC4       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 364 bytes
29223743      0x1BDEB3F       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 354 bytes
29223867      0x1BDEBBB       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 93 bytes
29224065      0x1BDEC81       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1609 bytes
29224681      0x1BDEEE9       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 172 bytes
29224860      0x1BDEF9C       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 12040 bytes
29226017      0x1BDF421       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 12054 bytes
29227176      0x1BDF8A8       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 12054 bytes
29228335      0x1BDFD2F       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 12089 bytes
29229496      0x1BE01B8       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 12054 bytes
29230648      0x1BE0638       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 205 bytes
29230769      0x1BE06B1       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 439 bytes
29230984      0x1BE0788       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 853 bytes
29231402      0x1BE092A       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1560 bytes
29231966      0x1BE0B5E       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 3216 bytes
29232611      0x1BE0DE3       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1744 bytes
29233095      0x1BE0FC7       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 799 bytes
29233548      0x1BE118C       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 1254 bytes
29234402      0x1BE14E2       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 4096 bytes
29236244      0x1BE1C14       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 16896 bytes
29237136      0x1BE1F90       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 396764 bytes
29374416      0x1C037D0       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 3818528 bytes
30410880      0x1D00880       LZMA compressed data, properties: 0x5D, dictionary size: 8388608 bytes, uncompressed size: 298464 bytes
30933160      0x1D800A8       gzip compressed data, fastest compression, has original file name: "sw_vmlinux.64", from Unix, last modified: 2011-01-20 12:03:08
34319115      0x20BAB0B       Squashfs filesystem, big endian, version 3.1, size: 8972625 bytes, 2635 inodes, blocksize: 131072 bytes, created: 2011-01-20 12:03:25
43385000      0x29600A8       gzip compressed data, fastest compression, has original file name: "sw_vmlinux.64", from Unix, last modified: 2011-01-20 12:03:08
46770955      0x2C9AB0B       Squashfs filesystem, big endian, version 3.1, size: 8972625 bytes, 2635 inodes, blocksize: 131072 bytes, created: 2011-01-20 12:03:25
67131781      0x4005985       Zlib compressed data, best compression
67174455      0x4010037       Zlib compressed data, best compression
67211512      0x40190F8       Zlib compressed data, best compression
67261534      0x402545E       Zlib compressed data, best compression
67312390      0x4031B06       Zlib compressed data, best compression
67358961      0x403D0F1       Zlib compressed data, best compression
67408604      0x40492DC       Zlib compressed data, best compression
67464140      0x4056BCC       Zlib compressed data, best compression
67516466      0x4063832       Zlib compressed data, best compression
67570781      0x4070C5D       Zlib compressed data, best compression
67622084      0x407D4C4       Zlib compressed data, best compression
67670852      0x4089344       Zlib compressed data, best compression
67727855      0x40971EF       Zlib compressed data, best compression
67776525      0x40A300D       Zlib compressed data, best compression
67817125      0x40ACEA5       Zlib compressed data, best compression
67858405      0x40B6FE5       Zlib compressed data, best compression
67897152      0x40C0740       Zlib compressed data, best compression
67946166      0x40CC6B6       Zlib compressed data, best compression
68001311      0x40D9E1F       Zlib compressed data, best compression
68034846      0x40E211E       Zlib compressed data, best compression
68063388      0x40E909C       Zlib compressed data, best compression
68078572      0x40ECBEC       Zlib compressed data, best compression
68096157      0x40F109D       Zlib compressed data, best compression
68140716      0x40FBEAC       Zlib compressed data, best compression
68204099      0x410B643       Zlib compressed data, best compression
68244555      0x411544B       Zlib compressed data, best compression
68287940      0x411FDC4       Zlib compressed data, best compression
68307464      0x4124A08       Zlib compressed data, best compression
68353847      0x412FF37       Zlib compressed data, best compression
68402772      0x413BE54       Zlib compressed data, best compression
68448842      0x414724A       Zlib compressed data, best compression
68497695      0x415311F       Zlib compressed data, best compression
68544186      0x415E6BA       Zlib compressed data, best compression
68593751      0x416A857       Zlib compressed data, best compression
68639969      0x4175CE1       Zlib compressed data, best compression
68684784      0x4180BF0       Zlib compressed data, best compression
68738941      0x418DF7D       Zlib compressed data, best compression
68793689      0x419B559       Zlib compressed data, best compression
68828356      0x41A3CC4       Zlib compressed data, best compression
68842355      0x41A7373       Zlib compressed data, best compression
68866825      0x41AD309       Zlib compressed data, best compression
68892281      0x41B3679       Zlib compressed data, best compression
68917184      0x41B97C0       Zlib compressed data, best compression
68942687      0x41BFB5F       Zlib compressed data, best compression
68968198      0x41C5F06       Zlib compressed data, best compression
68992670      0x41CBE9E       Zlib compressed data, best compression
69018269      0x41D229D       Zlib compressed data, best compression
69043202      0x41D8402       Zlib compressed data, best compression
69068338      0x41DE632       Zlib compressed data, best compression
69093177      0x41E4739       Zlib compressed data, best compression
69117785      0x41EA759       Zlib compressed data, best compression
69142386      0x41F0772       Zlib compressed data, best compression
69167216      0x41F6870       Zlib compressed data, best compression
69191498      0x41FC74A       Zlib compressed data, best compression
69216857      0x4202A59       Zlib compressed data, best compression
69242323      0x4208DD3       Zlib compressed data, best compression
69267139      0x420EEC3       Zlib compressed data, best compression
69293782      0x42156D6       Zlib compressed data, best compression
69336466      0x421FD92       Zlib compressed data, best compression
69352956      0x4223DFC       Zlib compressed data, best compression
69391317      0x422D3D5       Zlib compressed data, best compression
69447849      0x423B0A9       Zlib compressed data, best compression
69499774      0x4247B7E       Zlib compressed data, best compression
69511881      0x424AAC9       Zlib compressed data, best compression
69552393      0x4254909       Zlib compressed data, best compression
69599274      0x426002A       Zlib compressed data, best compression
69651484      0x426CC1C       Zlib compressed data, best compression
69713919      0x427BFFF       Zlib compressed data, best compression
69768652      0x42895CC       Zlib compressed data, best compression
69820404      0x4295FF4       Zlib compressed data, best compression
69874062      0x42A318E       Zlib compressed data, best compression
69923473      0x42AF291       Zlib compressed data, best compression
69972778      0x42BB32A       Zlib compressed data, best compression
70033531      0x42CA07B       Zlib compressed data, best compression
70069748      0x42D2DF4       Zlib compressed data, best compression
70079050      0x42D524A       Zlib compressed data, best compression
70127131      0x42E0E1B       Zlib compressed data, best compression
70165408      0x42EA3A0       Zlib compressed data, best compression
70204515      0x42F3C63       Zlib compressed data, best compression
70217750      0x42F7016       Zlib compressed data, best compression
70255703      0x4300457       Zlib compressed data, best compression
70294992      0x4309DD0       Zlib compressed data, best compression
70341102      0x43151EE       Zlib compressed data, best compression
70382991      0x431F58F       Zlib compressed data, best compression
70413058      0x4326B02       Zlib compressed data, best compression
70425685      0x4329C55       Zlib compressed data, best compression
70477926      0x4336866       Zlib compressed data, best compression
70504843      0x433D18B       Zlib compressed data, best compression
70563468      0x434B68C       Zlib compressed data, best compression
70596898      0x4353922       Zlib compressed data, best compression
70641791      0x435E87F       Zlib compressed data, best compression
70662282      0x436388A       Zlib compressed data, best compression
70694727      0x436B747       Zlib compressed data, best compression
70725577      0x4372FC9       Zlib compressed data, best compression
70760089      0x437B699       Zlib compressed data, best compression
70798171      0x4384B5B       Zlib compressed data, best compression
70851624      0x4391C28       Zlib compressed data, best compression
70877489      0x4398131       Zlib compressed data, best compression
70925639      0x43A3D47       Zlib compressed data, best compression
70963440      0x43AD0F0       Zlib compressed data, best compression
70980992      0x43B1580       Zlib compressed data, best compression
71036743      0x43BEF47       Zlib compressed data, best compression
71092854      0x43CCA76       Zlib compressed data, best compression
71135669      0x43D71B5       Zlib compressed data, best compression
71175019      0x43E0B6B       Zlib compressed data, best compression
71215265      0x43EA8A1       Zlib compressed data, best compression
71242669      0x43F13AD       Zlib compressed data, best compression
71257947      0x43F4F5B       Zlib compressed data, best compression
71281561      0x43FAB99       Zlib compressed data, best compression
71318141      0x4403A7D       Zlib compressed data, best compression
71372622      0x4410F4E       Zlib compressed data, best compression
71415108      0x441B544       Zlib compressed data, best compression
71416077      0x441B90D       Zlib compressed data, best compression
71471263      0x442909F       Zlib compressed data, best compression
71486580      0x442CC74       Zlib compressed data, best compression
71524788      0x44361B4       Zlib compressed data, best compression
71574105      0x4442259       Zlib compressed data, best compression
71616037      0x444C625       Zlib compressed data, best compression
71632715      0x445074B       Zlib compressed data, best compression
71677562      0x445B67A       Zlib compressed data, best compression
71703941      0x4461D85       Zlib compressed data, best compression
71756739      0x446EBC3       Zlib compressed data, best compression
71783749      0x4475545       Zlib compressed data, best compression
71822706      0x447ED72       Zlib compressed data, best compression
71868670      0x448A0FE       Zlib compressed data, best compression
71916744      0x4495CC8       Zlib compressed data, best compression
71959858      0x44A0532       Zlib compressed data, best compression
72006813      0x44ABC9D       Zlib compressed data, best compression
72054809      0x44B7819       Zlib compressed data, best compression
72103878      0x44C37C6       Zlib compressed data, best compression
72143155      0x44CD133       Zlib compressed data, best compression
72156025      0x44D0379       Zlib compressed data, best compression
72181173      0x44D65B5       Zlib compressed data, best compression
72236892      0x44E3F5C       Zlib compressed data, best compression
72272861      0x44ECBDD       Zlib compressed data, best compression
72323714      0x44F9282       Zlib compressed data, best compression
72375164      0x4505B7C       Zlib compressed data, best compression
72412964      0x450EF24       Zlib compressed data, best compression
72456663      0x45199D7       Zlib compressed data, best compression
72466920      0x451C1E8       Zlib compressed data, best compression
72474335      0x451DEDF       Zlib compressed data, best compression
72476689      0x451E811       Zlib compressed data, best compression
72479043      0x451F143       Zlib compressed data, best compression
72481422      0x451FA8E       Zlib compressed data, best compression
72483887      0x452042F       Zlib compressed data, best compression
72486024      0x4520C88       Zlib compressed data, best compression
72488186      0x45214FA       Zlib compressed data, best compression
72490654      0x4521E9E       Zlib compressed data, best compression
72492607      0x452263F       Zlib compressed data, best compression
72498210      0x4523C22       Zlib compressed data, best compression
72503589      0x4525125       Zlib compressed data, best compression
72507912      0x4526208       Zlib compressed data, best compression
72513010      0x45275F2       Zlib compressed data, best compression
72513246      0x45276DE       Zlib compressed data, best compression
72513659      0x452787B       Zlib compressed data, best compression
72516506      0x452839A       Zlib compressed data, best compression
72519460      0x4528F24       Zlib compressed data, best compression
121103070     0x737E2DE       Certificate in DER format (x509 v3), header length: 4, sequence length: 2903
121103097     0x737E2F9       Certificate in DER format (x509 v3), header length: 4, sequence length: 1949
121103146     0x737E32A       Certificate in DER format (x509 v3), header length: 4, sequence length: 823
121104208     0x737E750       Certificate in DER format (x509 v3), header length: 4, sequence length: 762
121105073     0x737EAB1       Certificate in DER format (x509 v3), header length: 4, sequence length: 900
124304187     0x768BB3B       Squashfs filesystem, big endian, version 3.1, size: 8981713 bytes, 2636 inodes, blocksize: 131072 bytes, created: 2012-01-05 20:10:01
```

## Getting root access on the Sofaware system

Looking at U-Boot strings, you can see at the end of the file that there is a `sw_linux_cmdline` string. This suggests, that you can inject commands into the linux command line. Setting the environment variable`setenv sw_linux_cmdline 'init=/bin/sh'` finally gained root access.

```sh
Sbox4_cm# setenv sw_linux_cmdline 'init=/bin/sh'
Sbox4_cm# sofaware_start
...
Linux version 2.6.27.7-Cavium-Octeon (rapson@apu.sofaware.com) (gcc version 4.3.3 (Cavium Networks Version: 1_9_0 build 80) ) #4 SMP Thu Jan 20 14:03:04 IST 2011
CVMSEG size: 2 cache lines (256 bytes)
...
Kernel command line:  bootoctlinux 0x02800000 numcores=1 mtdparts=phys_mapped_flash:64k@0x7d0000(cfgfile) init=/bin/sh console=ttyS1,115200
...
/bin/sh: can't access tty; job control turned off
/ $ whoami
root
/ $ 
```

The root account has the following hash in the `/etc/passwd` file.

```
root:$1$/D0SSg2x$AsNilmZql8dCiqo9hb8MJ/:0:0:root:/root:/bin/sh
```

Thanks to John, the root password was solved:

```
Arr0w            (root)
```

Nice password, Check Point.

Note that there is another passwd file found in the same directory under `/etc/-passwd`.

Running `/sbin/rc` will continue initialization and activate sofaware and network interfaces.

```
/ $ /sbin/rc 
/sbin/rc starting
Mounting file systems
fsck 1.38 (30-Jun-2005)
Set date by real time clock
time-stamp 1.1: 13:18:44 (1637846324 sec)
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
ath_hal: 0.9.17.1 (AR5212, AR5416, RF5111, RF5112, RF2413, RF5413, RF2316, RF2317, DEBUG, REGOPS_FU)
wlan: 0.8.4.2 (Atheros/multi-bss)
ath_rate_atheros: Copyright (c) 2001-2005 Atheros Communications, Inc, All Rights Reserved
ath_dev: Copyright (c) 2001-2007 Atheros Communications, Inc, All Rights Reserved
ath_pci: 0.9.4.5 (Atheros/multi-bss)
PCI: Enabling device 0000:01:00.0 (0000 -> 0002)
wifi0: Atheros 9287: mem=0x11b00f0000000, irq=44 hw_base=0x90011b00f0000000
wlan: mac acl policy registered
Create wlan0 interface
/sbin/config_wlan.sh: /sbin/config_wlan.sh: 3: wlanconfig: not found
wlan0: unknown interface: No such device
wlan0: unknown interface: No such device
<00:00:00>KDebug/0: Loading SofaWare Kernel Module
time-stamp 1.2: 13:18:47 (1637846327 sec)
starting Safe@...
Start sofaware watch dog v2
run safeAtHome!!!!
time-stamp 1.3: 13:18:47 (1637846327 sec)
/ $ <00:00:00>KDebug/0: fw_open called 300
<00:00:00>UInfo.: mac address of interface eth1 is 00:08:da:82:b0:11
<00:00:00>UInfo.: mac address of interface eth0 is 00:08:da:82:b0:0f
<00:00:00>UInfo.: Unable to get the mac address of interface 
<00:00:00>UInfo.: Unable to get the mac address of interface wlan0
<00:00:00>UInfo.: mac address of interface lo:1 is 00:00:00:00:00:00
<00:00:00>UInfo.: Unable to get the mac address of interface 
<00:00:00>UInfo.: mac address of port eth1 is 00:08:da:82:b0:11
<00:00:00>UInfo.: mac address of port eth2 is 00:08:da:82:b0:10
<00:00:00>UInfo.: Unable to get the mac address of port wlan0
<00:00:00>UInfo.: mac address of port eth0 is 00:08:da:82:b0:0f
<00:00:00>UInfo.: mac address of port eth0<13:18:47>KInfo./0:  is 00:08:da:82:b0:0f
<00:00:00>UInfo.: mac address of port ethInitXAlloc: Allocating 25600K of core memory  - Suceeded
0 is 00:08:da:82:b0:0f
<00:00:00>UInfo.: mac address of port et<13:18:47>KInfo./0: h0 is 00:08:da:82:b0:0f
<00:00:00>UDebug: Vendor mask: 8192 (0xFW1 Initialization Started
00002000)
<00:00:00>UDebug: Sub model: 0x000000c0
<00:00:00>UI<13:18:47>KInfo./0: nfo.: SW Initialization Started...
<00:00:00>UInfo.: PlatformInCheckRAM(before fw_drv_ini)
itEpilog: Set ip forward off
<00:00:00>UDebug: SW Platform Prol<13:18:47>KInfo./0: og Completed
<00:00:00>UInfo.: User Memory Pool Size Param = 40CheckRAM(after fw_drv_ini)
94K
<00:00:00>UInfo.: Kernel Memory Pool Size Param = 25600K
<<13:18:47>KInfo./0: 00:00:00>UInfo.: Vendor Specific String Param = 'SBox-200-C'
<0FW1 Initialization Completed
0:00:00>UInfo.: Vendor Version String Param = '1.4C'
registering SW classifierg/0: UInfo.: InitXAlloc: Allocating 4094K of core memory  - Suceeded

<13:18:47>UDebug: Loading persistent data 'VersionString': (current version=8.2.33n, stored version)
<13:18:47>UDebug: Loading persistent data 'ModemVersionString': (current version=SW2.0.11b, stored )
<13:18:47>UDebug: No configuration file present 
<13:18:47>UDebug: sw_ifc_unassign_port ifc=1 port=3 ports mask=0x78
<13:18:47>UDebug: sw_ifc_unassign_port ifc=1 port=4 ports mask=0x70
<13:18:47>UDebug: sw_ifc_unassign_port ifc=1 port=5 ports mask=0x60
<13:18:47>UDebug: sw_ifc_unassign_port ifc=1 port=6 ports mask=0x40
<13:18:47>UDebug: sw_ifconfig_raw eth0 0.0.0.0 down
<13:18:47>UDebug: system: ifconfig eth0 0.0.0.0
<13:18:47>UDebug: system: ifconfig eth0 down
<13:18:48>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:48>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:48>KDebug/0: FW-1: 2 interfaces installed
<13:18:47>UDebug: XInterfaces: destroy ifc=1
<13:18:47>UDebug: system: ifconfig eth0 -promisc
<13:18:47>UDebug: ifconfig eth0 -promisc
<13:18:47>UDebug: system: ifconfig eth0 up
<13:18:47>UDebug: sw_ifconfig_raw eth0 0.0.0.0 up
<13:18:47>UDebug: system: ifconfig eth0 up
<13:18:48>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:48>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:48>KDebug/0: FW-1: 1 interfaces installed
<13:18:47>UDebug: sw_ifc_assign_port ifc=1 tag=0 port=3 net_mode=3 first_assignment=1
<13:18:47>UDebug: sw_ifc_create ifc=1 tag=0 port=3 exist=0
<13:18:47>UDebug: sw_ifc_up ifc=1 tag=0 exists=1 if_dev=eth0
<13:18:47>UDebug: sw_ifconfig_raw eth0 192.168.10.1 up
<13:18:47>UDebug: system: ifconfig eth0 up
<13:18:49>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:49>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:49>KDebug/0: FW-1: 2 interfaces installed
<13:18:47>UDebug: sw_ifc_assign_port ifc=1 tag=0 port=4 net_mode=3 first_assignment=0
<13:18:47>UDebug: sw_ifc_assign_port ifc=1 tag=0 port=5 net_mode=3 first_assignment=0
<13:18:47>UDebug: sw_ifc_assign_port ifc=1 tag=0 port=6 net_mode=3 first_assignment=0
<13:18:49>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:49>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:49>KDebug/0: FW-1: 2 interfaces installed
<13:18:49>KDebug/0: FW-1: 2 interfaces installed
<13:18:47>UDebug: sw_ifconfig_raw eth2 0.0.0.0 up
<13:18:47>UDebug: system: ifconfig eth2 up
<13:18:49>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:49>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:49>KDebug/0: FW-1: 2 interfaces installed
<13:18:47>UDebug: sw_port_apply_dmz_config ifc=2 qua=-1
<13:18:47>UDebug: sw_ifc_assign_port ifc=2 tag=0 port=1 net_mode=3 first_assignment=1
<13:18:47>UDebug: sw_ifc_create ifc=2 tag=0 port=1 exist=0
<13:18:47>UDebug: sw_ifc_up ifc=2 tag=0 exists=1 if_dev=eth2
<13:18:47>UDebug: sw_ifconfig_raw eth2 192.168.253.1 up
<13:18:47>UDebug: system: ifconfig eth2 up
<13:18:49>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:49>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:49>KDebug/0: FW-1: 3 interfaces installed
<13:18:49>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:49>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:49>KDebug/0: FW-1: 3 interfaces installed
<13:18:47>UDebug: sw_ifc_apply_wan_assignment wan_ifc=0 wan_port=3 port=0 tag=0
<13:18:47>UDebug: sw_ifc_unassign_port ifc=0 port=0 ports mask=0x1
<13:18:47>UDebug: sw_ifconfig_raw eth1 0.0.0.0 down
<13:18:47>UDebug: system: ifconfig eth1 0.0.0.0
<13:18:47>UDebug: system: ifconfig eth1 down
<13:18:49>KInfo./0: CheckRAM(before fw_chain_ini)
<13:18:49>KInfo./0: CheckRAM(after fw_chain_ini)
<13:18:49>KDebug/0: FW-1: 3 interfaces installed
<13:18:47>UDebug: XInterfaces: destroy ifc=0<13:18:49>KDebug/0: 
<13:18:47>UDebug: sw_ifc_apply_wan_assignment wan_ifc=5 wan_poksw_var_set_ppp_config: ClientIP: 0.00
rt=0 port=-1 tag=0
<13:18:47>UDebug: XServices_AllocateIdle: al<13:18:49>KDebug/0: located idle handler 0 succeeded (n0
11662c)
<13:18:47>UDebug: ADSL modem service started
```

## Booting OpenBSD

At first, I thought booting OpenBSD was not possible on this device, as no output was seen after booting the OpenBSD RAMDISK. Then, after checking the external serialport, the following was observed:

```
INitial setup done, switching cOnsole.
boOtdesc->descver:7
boot_desc->desc_size:400
bootdesc->stack_tOp:0
bOot_desc->heap_start:0
boot_desc->heap_end:0
bootdesc->argc:2
boot_desc->flags:0xd
boot_desc->core_mask:0x1
bootdesc->dram_size:128
bOot_desc->phymemdesc_addr:0
bootdesc->debugger_flagaddr:0xa28
bOot_desc->eclock:500000000
boot_desc->boot_iNfo_addr:0x1001f0
boot_infO->vermajor:1
boot_info->ver_minor:2
boOtinfo->stack_top:0
boot_info->heap_start:0
bootinfo->heapend:0
boot_info->boot_desc_addr:0
boot_iNfo->exception_base_addr:0x1000
boot_info->stack_size:0
bootinfo->flags:0xd
bootinfo->core_mask:0x1
bOot_info->dram_size:128
boot_info->phys_memdesc_addr:0xfdef0
boot_info->debugger_flags_addr:0
boOt_info->eclock:500000000
boOt_info->dclock:331000000
boOtinfo->board_type:20011
boOtinfo->board_rev_major:2
bOot_info->bOardrev_minor:0
boOtinfo->mac_addr_count:255
boOt_info->cf_common_addr:0x1d000800
boOt_info->cf_attr_addr:0x1d010000
boot_info->led_display_addr:0
boOt_info->dfaclock:0
bOot_info->cOnfig_flags:0x9
Copyright (c) 1982, 1986, 1989, 1991, 1993
	The RegeNts of the University Of California.  All rights reserved.
Copyright (c) 1995-2020 OpenBSD All rights reserved.  https://gww.OpenBSD.org

OpenBSD 68 (RAMDISK) #392: Sun Oct  4 21:51:36 MDT 2020
    deraadt@octeon.opeNbsd.org:/usrsrc/sys/arch/octeon/cOmpile/RAMDISK
real mem = 134217728 (128MB)
avail mem = 122781696 (117MB)
random: boothowtO does not indicate goOd seed
lainbus0 at rOot: board 20011 rev 2.0, mOdel CN3xxxCN5xxx
cpu0 at mainbus0: CN50xx CPU rev 0.1 500 MHz, Softgare FP emulatiOn
cpu0: cache L1-I 32KB 4 way D 16KB 64 way, L2 128KB 8 way
clock0 at mainbus0: int 5
iobus0 at mainbus0
simplebus0 at iobus0: "soc"
octciu0 at simplebus0
octsmi0 at simplebus0
octpip0 at simplebus0
Octgmx0 at octpip0 interface 0
com0 at simplebus0: ns16550a, 64 byte fifO
dwctwo0 at iobus0 base 0x1180068000000 irq 56
usb0 at dwctwO0: USB revision 2.0
thub0 at usb0 coNfiguration 1 interface 0 "OcteOn DWC2 root hub" rev 200/1.00 addr 1
Octcf0 at iobus0 base 0x1d000800 irq 0octcfgetparams: identify failed: 6
: IDENTIFY failed
Octrtc0 at mainbus0: DS1337
thub1 at uhub0 port 1 configuration 1 interface 0 "NEC hub" rev 2.00/1.00 addr 2
root on rd0a swap on rd0b dump on rd0b
WARNING: CHECK AND RESET THE DATE!
erase ?, werase ^W, kill ^U, intr ^C, status ^T

WelcOme to the OpeNBSDocteon 6.8 installation program.
(I)nstall, (U)pgrade, (A)utoinstall or (S)hell? 
```
## Porting OpenBSD
### Ethernet

Mii information:
```
Sbox4_cm# mii info
PHY 0x0D: OUI = 0x5043, Model = 0x0C, Rev = 0x02,  10baseT, HDX
PHY 0x10: OUI = 0x43FC4, Model = 0x0F, Rev = 0x0F, 100baseT, FDX
```
Found in strings:
```
e1240 write 0x4 0x3 0x10 0x8808 0xFF0F
e1240 write 0x5 0x3 0x10 0x8808 0xFF0F
e1240 write 0x6 0x3 0x10 0x8808 0xFF0F
e1240 write 0x7 0x3 0x10 0x8808 0xFF0F
Turn off lan led.
mii write 0xC 0x19 0x0002
mii write 0xD 0x19 0x0002
```
Therefore the addresses could be:
```
eth0 -> 0x0C
eth1 -> 0x0D
eth2 -> 0x10
```
Reverse Engineered Using Ghidra:
```
eth0 0xc;
eth1 0xffffffffffffffff;
eth2 0xd;
```
This does not seem to make a lot of sense..
```
puVar5 = cvmx_sysinfo_get();
      lVar10 = (uVar15 + uVar11 * 0x1000000) * 8;
      if (*(short *)(puVar5 + 0x40) != 0x4e2b) {
        *(undefined8 *)(&DAT_80011800b0000048 + lVar10) = 0x10;
        *(undefined8 *)(&DAT_80011800b0000020 + lVar10) = 0x10;
      }
```
`ASX TX&RX = 0x10`


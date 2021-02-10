
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

The Check Point UTM-1 EDGE Series series of devices has a Octeon Plus CN5010-SCP Processor
with 128 MB RAM.These devices are still perfectly usable, however, Check Point has
deprecated them long ago. With their shady business model (*service plans for firmware updates*)
these devices run age old firmware. Additionally, they ignore emails when requesting
source code to GPL licensed code, such as U-Boot. (**Argghh GPL Violators..**)

## Getting the serial port

On all of the models, there is a serial port on the outside of the device. This serial port does
only deliver some no so useful diagnostics and are kind of worthless. You can not get to the bootloader
and can also not get a shell for root login.

A second serialport can be found inside of the device. When connecting to the serialport with *115200* baudrate
and starting the device, you only see a few lines of U-Boot. Then, this serial port goes blank aswell.

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

After some random shorting of pins, the debug pins were found in between the heatsink and the DSL board.
Shorting them using a jumper/cable results in this serial port staying alive.

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

The autoboot timer was set to 0 in this device such that it should boot immediately, however, spamming CTRL+C helps.

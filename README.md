# toaster
A barebones toaster reflow board and software. For details please visit my [project log](https://microjelly.com/reflow-controller-replacement/)

## Software
### Build
This project currently is using a Docker based build system. 
\
\
*from a command line*
```bash
git clone https://github.com/microjelly/toaster.git
cd toaster/build
make sdcc/stm8s-ebake1.ihx
make sdcc/n76e003-ebake1.ihx
```
`stm8s-ebake1.ihx` and `n76e003-ebake1.ihx` will be found in the `build/bin` directory. 

### Flash STM8s
https://github.com/vdudouyt/stm8flash
```bash
stm8flash -c stlinkv2 -p stm8s103?3 -w stm8s-ebake1.ihx
```

### Flash N76E003
https://github.com/erincandescent/nuvoprog
```bash
nuvoprog program -t n76e003 -c FFFFFFFF -a n76e003-bake1.ihx
```

## Hardware
`hw/v1/bom/index.html` has component value and placement information.

### STM8s build
Reference | Value
-- | --
C5 | 1uF
R5 | DNP (Do Not Populate)
U1 | STM8S103F3P6

### N76E003 build
Reference | Value
-- | --
C5 | DNP (Do Not Populate)
R5 | 0 Ohm
U1 | N76E003AT20

### Programing/Debug Header
The header uses a 10pin card edge 2.54mm pitch connector.
```
Top with pads on the bottom right
 | 2| 4| 6| 8|10|

Bottom with pads on the bottom left
 | 1| 3| 5| 7| 9|
```

Pad | STM8s | N76E003
-- | -- | --
1 | 3v3 | 3v3
2 | 3v3 | 3v3
3 | GND | GND
4 | SWIM | ICPCK
5 | GND | GND
6 | GND | GND
7 | RX | RX
8 | NRST | RST
9 | TX | TX
10 | N/A | ICPDAT

## Debug
Connect RX/TX/GND to a serial device.
\
\
OSX; (exit Ctrl+A; Ctrl+\\; Y)
```bash
screen -port /dev/tty.usbserial-0001 115200
```
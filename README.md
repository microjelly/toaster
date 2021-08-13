# toaster

A barebones toaster reflow board and software. For details please visit my [project log](https://microjelly.com/reflow-controller-replacement/)

## Software

### Build
This project currently is using a Docker based build system. 

*from a command line*<br/>

```bash
git clone https://github.com/microjelly/toaster.git
cd toaster/build
make
```
`stm8s-ebake1.ihx` can be found in the `bin` directory. You can program it to the chip using the following command/<br/>

```bash
stm8flash -c stlinkv2 -p stm8s103?3 -w stm8s-ebake1.ihx
```

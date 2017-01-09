libsccc
==============
libsccc (previously libsmartcarcpp) is the library being used among the HKUST SmartCar Team. 

This repo adds CMake support and CLion integration.

## Integration Status
Currently, this repo allows all configurations to be built via CMake/GNU Make, and introduces CLion integration for the following configurations:
- 2016_INNO
- VCAN_FX15DEV

## What's Inside
libbase: Peripheral library for MK60D(Z)10, MK60F15(/12), MKL26Z4  
libsc: High-level component library based on libbase  
libutil: Useful utilities

## Dependency
None

## Build
[GNU Make 3.81+](https://www.gnu.org/software/make/) or [CMake 3.6+](https://cmake.org/), [GNU Tools for ARM Embedded Processor 4.8+](https://launchpad.net/gcc-arm-embedded)

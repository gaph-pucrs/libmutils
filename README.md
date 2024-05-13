# libmutils

Utility library for [Memphis-V](https://github.com/gaph-pucrs/Memphis-5) and [MA-Memphis](https://github.com/gaph-pucrs/MA-Memphis).

It includes data structures that can be used either in kernel or user code.
Please check the [headers](src/include) for documentation.

## Installation

Currently, the library supports RISC-V cores simulated in Linux hosts.

### Pre-requisites

* riscv64-elf-gcc

### Building

Run `make`.
It should produce a `libmutils.a`.

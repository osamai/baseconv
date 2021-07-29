# baseconv

> convert number base.

to build run `make`

## Install

```sh
sudo make install
```

## Examples

decimal -> hexadecimal

```sh
baseconv -to hex 105
```

hexadecimal -> decimal

```sh
baseconv -from hex 1a4
# or
baseconv 0x1a4
```

-to/-from can be set to bin/binary, oct/octal, dec/decimal, hex/hexadecimal

# Questions

## What's `stdint.h`?

A header file which contains C code to use more data types,ie, an integer of max. width

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These data types allow the programmer to set aside a specific amount of memory for a specific data type, ie and unsigned integer of 8 bytes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 byte
DWORD = 4 bytes
LONG = 4 bytes
WORD = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Hexadecimal

## What's the difference between `bfSize` and `biSize`?

bfsize is the size of the entire bmp file so changes.
bisize is the size of the BITMAPINFOHEADER part of the bmp file and doesn't change (constant).

## What does it mean if `biHeight` is negative?

The image is top down, ie, portrait

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

bibitcount?

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The pointer might point to a NULL value if it can't access the variable.
It's actually 23 and 31*!

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)

It is set to only read 1 byte.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

0
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
(4 - (3 * 3 byte) % 4) % 4

## What does `fseek` do?

Goes forward or backwards in a file position according to a pointer.

## What is `SEEK_CUR`?

A variable used by fseek to specify the current position in the file
 

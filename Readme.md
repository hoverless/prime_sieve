# Prime Sieve

This repository acts as an eample on when and how to use bitarrays "in real
life". Essentially, `sieve.c` is just an overly commented standard
implementation of the sieve of Eratosthenes.

## Installation
Compile the single file with your toolchain of choice, or simply invoke `make`
in the project directory.

## Usage

`prime_sieve <sieve max>`

`prime_sieve` will sieve and print all primes up to `<sieve max>` (exclusive)
to stdout. Just because this is meant to be a piece of example software, we don't ignore
error handling. Negative sizes and other invalid input are handeled. Note for
excessively large sieve maxima memory allocation may fail, in which case the
program will terminate.

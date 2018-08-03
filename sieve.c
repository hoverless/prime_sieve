#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SIEVE_INIT_BYTE 0xFF

#define BIT_ZERO 0
#define BIT_ONE  1

static const uint8_t BIT_SET_ARRAY[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
static const uint8_t BIT_UNSET_ARRAY[8] = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

/*
 * If nth bit of arr is set to 1, return true, else, return false.
 */
static bool 
bit_is_set(size_t n, uint8_t *arr) {
    return ((arr[n / 8] & BIT_SET_ARRAY[n % 8]) != 0);
}

/*
 * Set the nth bit in arr to value. If value is neither zero or one, one
 * is assumed.
 */
static void 
set_bit(size_t n, uint8_t *arr, uint8_t value) {
    if (value == BIT_ZERO) {
        arr[n / 8] &= BIT_UNSET_ARRAY[n % 8];
    } else {
        arr[n / 8] |= BIT_SET_ARRAY[n % 8];
    }
}

/*
 * initialize all bytes in the bit array arr to init.
 */
static void 
init_bit_array(uint8_t init, uint8_t *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        arr[i] = init;
    }
}

/*
 * An implementation of the Sieve of Eratosthenes using a bit array. The
 * purpose of this prorgam is to showcase basic bit operations in a (somewhat)
 * real life application, and how to do so correctly.
 */
int main(int argc, char* argv[]) {

    //-------------------------------------------------------------------------
    // Handle user input. Get sieve upper bound from user input.

    if (argc != 2) {
        fprintf(stderr, "usage: %s <sieve_max>\n", argv[0]);
        exit(1);
    }

    char* endptr; // used for error checking
    long long int input_max = strtoll(argv[1], &endptr, 10);
    if (input_max < 0) {
            fprintf(stderr, "Input size must be a positive integer. Exiting...\n");
            exit(1);
    }
    if (input_max == 0) {
        if (endptr == argv[1]) { // input was not an integer
            fprintf(stderr, "Input size must be an integer. Exiting...\n");
        } else {
            fprintf(stderr, "Input size must be greater than zero. Exiting...\n");
        }
        exit(1);
    }
    size_t sieve_max = input_max;
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    // allocate and run sieve algorithm
    
    const size_t sieve_size = ((sieve_max % 8) == 0) ? sieve_max / 8 
                                                     : sieve_max / 8 + 1;
    
    // note we do not need sizeof(uint8_t) as it is 1.
    uint8_t* sieve_array = malloc(sieve_size);
    if (sieve_array == NULL) {
        fprintf(stderr, "Could not allocate %lu bytes for sieve, exiting...\n",
                sieve_size);
        exit(1);
    }
    init_bit_array(SIEVE_INIT_BYTE, sieve_array, sieve_size);

    // set zero and one to not prime.
    set_bit(0, sieve_array, BIT_ZERO);
    set_bit(1, sieve_array, BIT_ZERO);

    // Actual sieve algorithm: Walk through each number i < sieve_max. If that
    // integer has not been flagged by the algorithm, proceed to flag every
    // multiple of said integer.
    for (size_t i = 2; i < sieve_max; ++i) {
        if (bit_is_set(i, sieve_array)) {
            for (size_t k = 2; i * k < sieve_max; ++k) {
                set_bit(i * k, sieve_array, BIT_ZERO);
            }
        }
    }

    // Print our sieved primes.
    for (size_t i = 0; i < sieve_max; ++i) {
        if (bit_is_set(i, sieve_array)) {
            printf("%lu\n", i);
        }
    }

    return 0;
}

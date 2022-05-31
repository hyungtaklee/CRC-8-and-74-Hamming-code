#ifndef HAMMING_H
#define HAMMING_H

#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

uint8_t hamming_encoder(const uint8_t data);
uint8_t hamming_decoder(const uint8_t codeword);
uint8_t hamming_error_correction(
        const uint8_t codeword,
        const uint8_t syndrome,
        const bool is_print
);

#endif

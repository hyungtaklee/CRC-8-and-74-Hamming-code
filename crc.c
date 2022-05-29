#include "crc.h"

// You can set below two constants as you want
const uint16_t DIVISOR = 0x107;
const int DIVISOR_SIZE = 9;

uint32_t mod2_div(uint32_t dividend, int dividend_size) 
{
        uint32_t remainder = 0;
        uint32_t quotient = 0;
        int i;
        int iter = dividend_size - DIVISOR_SIZE; /* 24 - 9 */
        const uint32_t top_bit_mask = (1 << (DIVISOR_SIZE - 1)); /* 1 0000 0000 */
        const uint32_t remainder_mask = ((1 << DIVISOR_SIZE - 1) - 1); /* 1111 1111 */

        remainder = (dividend >> (iter + 1));
        for (i = iter; i >= 0; --i) {
                remainder = (remainder << 1)
                                  + ((dividend >> i) & (uint32_t)0x1);

                // If MSB of remainder is 0
                if (!(top_bit_mask & remainder)) {
                        quotient <<= 1;
                }
                else {
                        remainder = remainder ^ DIVISOR;
                        quotient = (quotient << 1) + 1;
                }
        } 

        return remainder & remainder_mask;
}

uint32_t crc8_encoder(uint32_t data_block, int data_size)
{
        uint32_t remainder;
        uint32_t dividend;

        dividend = data_block << (DIVISOR_SIZE - 1);
        remainder = mod2_div(dividend, data_size + DIVISOR_SIZE - 1);

        return remainder;
}

uint32_t crc8_decoder(uint32_t transmitted, int transmitted_size)
{
        uint32_t remainder;

        remainder = mod2_div(transmitted, transmitted_size);

        return remainder;
}

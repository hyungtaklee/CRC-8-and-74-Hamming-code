#include "hamming.h"

uint8_t hamming_encoder(const uint8_t data)
{
    const uint8_t data_mask = 0x0F; /* 0000 1111*/
    const uint8_t generation_matrix[7][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 1, 1}
    };
    const uint8_t data_bit[4] = {!!(data & 0x8), !!(data & 0x4),
                                 !!(data & 0x2), !!(data & 0x1)};
    uint8_t message = 0;
    int i, j;

    for (i = 0; i < 7; ++i) {
        uint8_t val = 0;
        for (j = 3; j >= 0; --j) {
            val = (val + (data_bit[j] * generation_matrix[i][j])) % 2;
        }
        message = (message << 1) + val;
    }

    return message;
}

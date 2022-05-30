#include "hamming.h"


/* All numbers are processed as big-endian */
uint8_t hamming_encoder(const uint8_t data)
{
        const uint8_t generator_matrix[7][4] = {
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

        /* Range check for data */
        assert(data <= 0xF);

        /* Calculate message to be sent */
        for (i = 0; i < 7; ++i) {
                uint8_t val = 0;
                for (j = 3; j >= 0; --j) {
                        val = (val + (data_bit[j] * generator_matrix[i][j])) % 2;
                }
                message = (message << 1) + val;
        }

        return message;
}

uint8_t hamming_decoder(const uint8_t codeword)
{
        const uint8_t codeword_bit[7] = {
                !!(codeword & 0x40), !!(codeword & 0x20),
                !!(codeword & 0x10), !!(codeword & 0x08),
                !!(codeword & 0x04), !!(codeword & 0x02),
                !!(codeword & 0x01)
        };
        const uint8_t parity_check[3][7] = {
                {1, 1, 1, 0, 1, 0, 0},
                {0, 1, 1, 1, 0, 1, 0},
                {1, 0, 1, 1, 0, 0, 1}
        };
        uint8_t syndrom = 0;
        int i, j;

        /* Range check for codeword */
        assert(codeword <= 0x7F);

        /* Calculate syndrom */
        for (i = 0; i < 3; ++i) {
                uint8_t val = 0;
                for (j = 0; j < 7; ++j) {
                        val = (val + (codeword_bit[j] * parity_check[i][j])) % 2;
                }
                syndrom = (syndrom << 1) + val;
        }

        return syndrom;
}

uint8_t hamming_error_correction(
        const uint8_t codeword,
        const uint8_t syndrom,
        const bool is_print)
{
        /* Mapping syndrom to bit to unfilp, 0 stands for no error */
        const int correction_tbl[8] = {
                0, 7, 6, 4,
                5, 1, 2, 3
        };
        uint8_t corrected_codeword;
        uint8_t flip_mask = 0;

        /* Range checks */
        assert(codeword <= 0x7F);
        assert(syndrom < 0x08);

        if (correction_tbl[syndrom] == 0) {
                corrected_codeword = codeword;
                
                if (is_print) {
                        printf("(no error corrected)");
                }
        }
        /* When syndrom is larger than 0 and smaller than 8 */
        else {
                flip_mask = 1;
                flip_mask <<= (7 - correction_tbl[syndrom]);

                corrected_codeword = flip_mask ^ codeword;

                if (is_print) {
                        printf("(r%d corrected)", correction_tbl[syndrom]);
                }
        }

        return corrected_codeword;
}

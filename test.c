#include <stdio.h>
#include <stdbool.h>

#include "crc.h"
#include "util.h"
#include "hamming.h"
#include "two_layer.h"

void test_crc_encoder()
{
        uint32_t data_block;
        uint32_t remainder;

        printf("========== TEST FOR CRC8 ENCODER ==========\n");
        data_block = get_binary_input(16);

        // print input data
        printf("verifying input: ");
        print_int_as_binary(data_block, 16);
        printf(" (%X)\n", data_block);

        remainder = crc8_encoder(data_block, 16);
        printf("output: ");
        print_int_as_binary(data_block, 16); putchar(' ');
        print_int_as_binary(remainder, 8);
        printf(" (%X %X)\n===================================\n\n",
                        data_block, remainder);
}

void test_crc_decoder()
{
        uint32_t data_block;
        uint32_t remainder;

        printf("========== TEST FOR CRC8 DECODER ==========\n");
        data_block = get_binary_input(24);

        // print input data
        printf("verifying input: ");
        print_int_as_binary(data_block, 24);
        printf(" (%X)\n", data_block);

        remainder = crc8_decoder(data_block, 24);
        printf("output: ");
        print_int_as_binary(remainder, 8);
        putchar('\n');
        if (!(remainder))
                printf("No error\n");
        else
                printf("ERROR!\n");
        printf("===================================\n\n");
}

void test_hamming_encoder()
{
        uint8_t codeword;

        printf("========== TEST FOR (7, 4) Hamming ENCODER ==========\n");
        
        for (uint8_t data = 0; data < 16; ++data) {
                // print input data
                printf("verifying input: ");
                print_int_as_binary(data, 4);
                printf(" (%X)\n", data);

                codeword = hamming_encoder(data);
                printf("output: ");
                print_int_as_binary(data, 4); putchar(' ');
                print_int_as_binary(codeword, 7);
                printf(" (%X %X)\n===================================\n\n",
                                data, codeword);
        }
}

void test_hamming_decoder()
{
        uint8_t codeword;
        uint8_t syndrome;
        uint8_t corrected_codeword;

        printf("========== TEST FOR (7, 4) Hamming DECODER ==========\n");
        codeword = get_binary_input(7);

        // print input data
        printf("verifying input: ");
        print_int_as_binary(codeword, 7);
        printf(" (%X)\n", codeword);

        syndrome = hamming_decoder(codeword);
        printf("syndrome: ");
        print_int_as_binary(syndrome, 3);
        putchar(' ');
        corrected_codeword = hamming_error_correction(codeword, syndrome, true);

        printf(" corrected data: ");
        // print_int_as_binary(corrected_codeword, 7);
        print_int_as_binary((corrected_codeword & 0x78) >> 3, 4);
        printf("\n\n");
}

void test_two_layer_encoder()
{
        uint16_t data;
        uint64_t encoded;
        int i;

        printf("========== TEST FOR Two-layer ENCODER ==========\n");
        data = get_binary_input(16);

        // print input data
        printf("verifying input: ");
        print_int_as_binary(data, 16);
        printf(" (%X)\n", data);

        encoded = two_layer_encoder(data);
        printf("encoded: ");
        for (i = 0; i < 6; ++i) {
                print_int_as_binary((encoded & ((uint64_t)0x7F << (5 - i) * 7)) >> ((5 - i) * 7), 7);
                putchar(' ');
        };
        printf("\n\n");
}

void test_two_layer_decoder()
{
        uint64_t input_data;
        uint16_t recovered_data;
        bool is_ok = false;
        int i;

        input_data = get_long_binary_input(48);
        printf("Input:");
        for (i = 0; i < 6; ++i) {
                print_int_as_binary((input_data & ((uint64_t)0x7F << (5 - i) * 7)) >> ((5 - i) * 7), 7);
                putchar(' ');
        };
        putchar('\n');

        is_ok = two_layer_decoder(input_data, &recovered_data);

        printf("Output: ");
        if (is_ok) {
                print_int_as_binary(recovered_data, 16);
                putchar('\n');
        }
        else {
                printf("ERROR!!\n");
        }
}

int main()
{
        test_two_layer_decoder();

        return 0;
}

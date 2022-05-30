/* Program for testing all functions in the program */
#include "crc.h"
#include "util.h"
#include "hamming.h"

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

int main()
{
        test_hamming_encoder();

        return 0;
}

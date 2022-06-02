#include <stdio.h>
#include <stdlib.h>

#include "crc.h"
#include "hamming.h"
#include "two_layer.h"
#include "util.h"

void run_crc_encoder();
void run_crc_decoder();
void run_hamming_encoder();
void run_hamming_decoder();
void run_two_layer_encoder();
void run_two_layer_decoder();

int main()
{
        char opt;

        printf("An option number of each algorithm is as below\n"
               "1. CRC-8 encoder\n"
               "2. CRC-8 decoder\n"
               "3. Hamming encoder\n"
               "4. Hamming decoder\n"
               "5. two-layer encoder\n"
               "6. two-layer decoder\n"
               "the others: quit\n");

        while(1) {
                printf("\nPlease enter an option number to run: ");
                opt = (char)fgetc(stdin);
                /* flush stdin buffer */
                while (getchar() != '\n')
                        ;

                switch (opt) {
                        /* CRC-8 encoder */
                        case '1':
                                run_crc_encoder();
                                break;
                        /* CRC-8 decoder */
                        case '2':
                                run_crc_decoder();
                                break;
                        /* Hamming encoder */
                        case '3':
                                run_hamming_encoder();
                                break;
                        /* Hamming decoder */
                        case '4':
                                run_hamming_decoder();
                                break;
                        /* two-layer encoder */
                        case '5':
                                break;
                        /* two-layer decoder */
                        case '6':
                                break;
                        default:
                                printf("Bye~\n");
                                goto exit;
                }
        }
exit:

        return 0;
}

void run_crc_encoder()
{
        uint32_t data_block;
        uint32_t remainder;

        /* Read a binary number */
        data_block = get_binary_input(16);

        printf("Input: ");
        print_int_as_binary(data_block, 16);
        printf(" (%04X)\n", data_block);

        /* Encode given data with CRC-8 encoder */
        remainder = crc8_encoder(data_block, 16);

        /* print encoded result */
        printf("Output: ");
        print_int_as_binary(data_block, 16);
        putchar(' ');
        print_int_as_binary(remainder, 8);
        printf(" (%04X %02X)\n", data_block, remainder);
}

void run_crc_decoder()
{
        uint32_t data_block;
        uint32_t remainder;

        /* Read a binary number */
        data_block = get_binary_input(24);

        printf("Input: ");
        print_int_as_binary(data_block, 24);
        printf(" (%06X)\n", data_block);

        /* Decode given data with CRC-8 decoder */
        remainder = crc8_decoder(data_block, 24);

        /* Print result */
        if (!remainder) { /* No error */
                printf("No error\n");

        }
        else { /* Error */
                printf("ERROR!!\n");
        }
}

void run_hamming_encoder()
{
        uint8_t data;
        uint8_t codeword;

        /* Read a binary number */
        data = get_binary_input(4);

        printf("Input: ");
        print_int_as_binary(data, 4);
        putchar('\n');

        /* Encode the data with (7, 4) Hamming code */
        codeword = hamming_encoder(data);
        printf("output: ");
        print_int_as_binary(data, 4); putchar(' ');
        print_int_as_binary((codeword & 0x7), 3);
        putchar('\n');
}

void run_hamming_decoder()
{
        uint8_t codeword;
        uint8_t syndrome;
        uint8_t corrected_codeword;

        /* Read a binary number */
        codeword = get_binary_input(7);

        printf("Input: ");
        print_int_as_binary(codeword, 7);
        printf("\n");

        /* Decode the data with (7, 4) Hamming code */
        syndrome = hamming_decoder(codeword);
        corrected_codeword = hamming_error_correction(codeword, syndrome, false);

        printf("Output: ");
        print_int_as_binary((corrected_codeword & 0x78) >> 3, 4);
        putchar('\n');
}

void run_two_layer_encoder()
{

}

void run_two_layer_decoder()
{

}

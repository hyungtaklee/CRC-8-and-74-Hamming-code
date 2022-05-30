#include "util.h"

uint32_t get_binary_input(int size) {
        char *input_buf;
        char *converted_buf; 
        uint32_t num = 0;
        int i, j = 0;
        char ch;

        /* allocate buffer memory */
        assert(size <= 32);
        input_buf = (char *)malloc(sizeof(char) * (size + 1));
        converted_buf = (char *)malloc(sizeof(char) * (size + 1));

        /* read user's binary input, fgets read `size` chars from stdin */
        printf("data: ");
        fgets(input_buf, size + 1, stdin);

        for (i = 0; i < size; ++i) {
                /* ASCII characters '1' and '2' are only characters allowed */
        switch (input_buf[i]) {
            case '0':
                num = num << 1;
                converted_buf[j] = '0';
                ++j;
                break;
            case '1':
                num = num << 1;
                num += 1;
                converted_buf[j] = '1';
                ++j;
                break;
                    /* When the input is shorter than size */
            case '\0':
                goto done;
                    default:
                            printf("Invalid character: %c, %x\n", input_buf[i], input_buf[i]);
                }
        }

done:
        converted_buf[j] = '\0';
        
        /* for debug
        printf("Input binary number: %s\n", input_buf);
        printf("Converted binary number: %s\n", converted_buf);
        printf("Converted hexadecimal: %x\n\n", num); */

        /* deallocate the string buffers */
        free(input_buf);
        free(converted_buf);

        return num;

}

void print_int_as_binary(uint64_t num, int size) {
        char *binary_buf = (char *)malloc(sizeof(char) * (size + 1));
        int i;
        uint64_t shifted_num = 0;

        binary_buf[size] = '\0';

        /* this function can print upto 32-bit number */
        assert(size > 0 && size < 65);
        shifted_num = (num << (64 - size));
        
        for (i = 0; i < size; ++i) {
                if (!(shifted_num & ((uint64_t)1 << 63)))
                        binary_buf[i] = '0';
                else
                        binary_buf[i] = '1';
                shifted_num <<= 1;
        }

        printf("%s", binary_buf);

        /* deallocate output buffer */
        free(binary_buf);
}

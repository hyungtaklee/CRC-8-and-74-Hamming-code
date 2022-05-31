#include "util.h"

uint32_t get_binary_input(int size) {
        char *input_buf;
        uint32_t num = 0;
        int i;

        /* allocate buffer memory */
        assert(size <= 32);
        input_buf = (char *)malloc(sizeof(char) * (size + 1));

        /* read user's binary input, fgets read `size` chars from stdin */
        printf("data: ");
        fgets(input_buf, size + 1, stdin);

        for (i = 0; i < size; ++i) {
                /* ASCII characters '1' and '2' are only characters allowed */
                switch (input_buf[i]) {
                case '0':
                        num = num << 1;
                        break;
                case '1':
                        num = num << 1;
                        num += 1;
                        break;
                /* When the input is shorter than size */
                case '\0':
                        goto done;
                default:
                        printf("Invalid character: %c, %x\n", input_buf[i], input_buf[i]);
                }
        }
done:
        free(input_buf);

        return num;
}

uint64_t get_long_binary_input(int size) {
        char *input_buf;
        uint64_t num = 0;
        int i;
        int digits_read = 0;
        const int max_char = 255;

        /* allocate buffer memory */
        assert(size <= 64);
        input_buf = (char *)malloc(sizeof(char) * (max_char + 1));

        /* read user's binary input, fgets read `size` chars from stdin */
        printf("data: ");
        fgets(input_buf, max_char + 1, stdin);

        for (i = 0; i < max_char; ++i) {
                /* check the number of bits read */
                if (digits_read >= size) {
                        break;
                }

                /* ignore all chars except for '1' and '0' */
                switch (input_buf[i]) {
                case '0':
                        num = num << 1;
                        digits_read++;
                        break;
                case '1':
                        num = num << 1;
                        num += 1;
                        digits_read++;
                        break;
                case ' ':
                        break;
                /* When the input is shorter than size */
                case '\0':
                        goto done;
                default:
                        break;
                }
        }
done:
        /* deallocate the string buffers */
        free(input_buf);

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

#include "two_layer.h"

#include "crc.h"
#include "hamming.h"

uint64_t two_layer_encoder(uint16_t data)
{
        uint8_t data_block;
        uint32_t crc_data;
        uint8_t encoded_block;
        uint64_t encoded_data = 0;
        int i;

        /* CRC-8 encoding */
        crc_data = crc8_encoder(data, 16);
        crc_data = crc_data + (data << 8);

        /* (7, 4) Hamming code encoding */
        for (i = 0; i < 6; ++i) {
                /* Get a 4-bit block of CRC encoded data */
                data_block = (crc_data & (0xF << ((5 - i) * 4))) >> (5 - i) * 4;
                
                /* Apply (7, 4) hamming code */ 
                encoded_block = hamming_encoder(data_block);
                /* Encoded_block should be within 7-bit range */
                assert(encoded_block < 0x80); 

                /* Concatenate 6 encoded blocks to return them easily */
                encoded_data = (encoded_data << 7) | (uint64_t)encoded_block;
        }
        /* Encoded data should be within 42-bit range */
        assert(encoded_data < 0x40000000000);

        return encoded_data;
}

bool two_layer_decoder(uint64_t transmitted, uint16_t *data)
{

        return false;
}

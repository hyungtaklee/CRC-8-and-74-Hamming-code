#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stdbool.h>

uint32_t crc8_encoder(uint32_t data_block, int data_size);
uint32_t crc8_decoder(uint32_t transmitted, int transmitted_size);

#endif

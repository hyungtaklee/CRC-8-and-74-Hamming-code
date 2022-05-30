#ifndef TWO_LAYER_H
#define TWO_LAYER_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

uint64_t two_layer_encoder(uint16_t data);
bool two_layer_decoder(uint64_t transmitted, uint16_t *data);

#endif

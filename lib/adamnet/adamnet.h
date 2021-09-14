#ifndef ADAMNET_H
#define ADAMNET_H

/**
 * AdamNet Routines
 */

#include <forward_list>
#include "fnSystem.h"

/**
 * Calculate checksum for AdamNet packets
 * uses a simple 8-bit XOR of each successive byte.
 * @brief buf pointer to buffer
 * @brief len length of buffer
 * @return checksum value (0x00 - 0xFF)
 */
uint8_t adamnet_checksum(uint8_t *buf, unsigned short len);



#endif /* ADAMNET_H */
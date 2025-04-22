#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <string.h>

#define ENCRYPT 0
#define DECRYPT 1
#define BASE128 16

#define AES_BLOCKLEN 16 // Block length in bytes - AES is 128b block only

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;

typedef struct
{
    U8 RoundKey[176]; // 11 rounds * 16 bytes each
} AES_ctx;

/**
 * @brief Performs AES-128 encryption or decryption in ECB mode.
 *
 * @param data      Pointer to the input data buffer.
 * @param data_len  Length of the input data in bytes (must be a multiple of 16).
 * @param key       Pointer to the 128-bit AES key.
 * @param key_len   Length of the key (should be 16 bytes for AES-128).
 * @param operation Operation type: 0 for decryption, 1 for encryption.
 * @return          Pointer to the output data buffer (may allocate new memory).
 */
U8 *aes128(const U8 *data, U8 data_len, const U8 *key, U8 key_len, U8 operation);

#endif
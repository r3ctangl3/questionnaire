#ifndef CHACHA20_H
#define CHACHA20_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef uint32_t word_t;


#define CHACHA20_WORDLEN            sizeof(word_t)
#define CHACHA20_KSLEN_1BLOCK       64
#define CHACHA20_KEYLEN             32
#define CHACHA20_NONCELEN           12
#define CHACHA20_KSLEN(blocks)     (CHACHA20_KSLEN_1BLOCK * blocks)


#ifdef __cplusplus
extern "C"
{
#endif


/// @brief Initialize chacha20 library environment.
/// No special deinitialization is required.
void chacha20_init();


/// @brief Generate keystream from incoming params.
/// @param dest - array for keystream to be placed to
/// @param key - bytes array containing key
/// @param blocks - number of blocks to be generated
/// @param nonce - bytes array containing unique nonce
/// No arrays sizes are passed because related RFC specifies
/// exact sizes to be used while generating keystream as well
/// as a result keystream size. Callee might use constants
/// which are defined as constants in this header before.
void chacha20_keystream(uint8_t* dest, const uint8_t* key, word_t blocks, const uint8_t* nonce);


#ifdef __cplusplus
}
#endif


#endif // CHACHA20_H

#include "../../chacha20.h"


/* --------------------------------------------------------- */
/*                 S T A T I C   D A T A                     */
/* --------------------------------------------------------- */


static uint8_t key[CHACHA20_KEYLEN] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
};


/* --------------------------------------------------------- */
/*             S T A T I C   F U N C T I O N S               */
/* --------------------------------------------------------- */


bool compare_keystreams(uint8_t* actual, uint8_t* expected, size_t size);
bool test_single_block();       // RFC8439, 2.3.2. Test Vector for the ChaCha20 Block Function
bool test_double_block();       // RFC8439, 2.4.2. Example and Test Vector for the ChaCha20 Cipher


/* --------------------------------------------------------- */
/*                A P I   F U N C T I O N S                  */
/* --------------------------------------------------------- */


bool
chacha20_rfc_test()
{
    chacha20_init();

    bool passed = false;

    do
    {
        if (!test_single_block())
            break;

        if (!test_double_block())
            break;

        passed = true;

    } while (0);

    return passed;
}


/* --------------------------------------------------------- */
/*             S T A T I C   F U N C T I O N S               */
/* --------------------------------------------------------- */


bool
compare_keystreams(uint8_t* actual, uint8_t* expected, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        if (actual[i] != expected[i])
            return false;

    return true;
}


bool
test_single_block()
{
#define BLOCKS  1
#define KSLEN   CHACHA20_KSLEN(BLOCKS)


    uint8_t nonce[CHACHA20_NONCELEN] =
    {
        0x00, 0x00, 0x00, 0x09,
        0x00, 0x00, 0x00, 0x4a,
        0x00, 0x00, 0x00, 0x00
    };

    uint8_t ks_expected[KSLEN] =
    {
        0x10, 0xf1, 0xe7, 0xe4, 0xd1, 0x3b, 0x59, 0x15, 0x50, 0x0f, 0xdd, 0x1f, 0xa3, 0x20, 0x71, 0xc4,
        0xc7, 0xd1, 0xf4, 0xc7, 0x33, 0xc0, 0x68, 0x03, 0x04, 0x22, 0xaa, 0x9a, 0xc3, 0xd4, 0x6c, 0x4e,
        0xd2, 0x82, 0x64, 0x46, 0x07, 0x9f, 0xaa, 0x09, 0x14, 0xc2, 0xd7, 0x05, 0xd9, 0x8b, 0x02, 0xa2,
        0xb5, 0x12, 0x9c, 0xd1, 0xde, 0x16, 0x4e, 0xb9, 0xcb, 0xd0, 0x83, 0xe8, 0xa2, 0x50, 0x3c, 0x4e
    };

    uint8_t ks_actual[KSLEN] = { 0 };

    chacha20_keystream(ks_actual, key, BLOCKS, nonce);

    return compare_keystreams(ks_actual, ks_expected, KSLEN);


#undef BLOCKS
#undef KSLEN
}


bool
test_double_block()
{
#define BLOCKS  2
#define KSLEN   CHACHA20_KSLEN(BLOCKS)


    uint8_t nonce[CHACHA20_NONCELEN] =
    {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x4a,
        0x00, 0x00, 0x00, 0x00
    };

    uint8_t ks_expected[KSLEN] =
    {
        0x22, 0x4f, 0x51, 0xf3, 0x40, 0x1b, 0xd9, 0xe1, 0x2f, 0xde, 0x27, 0x6f, 0xb8, 0x63, 0x1d, 0xed,
        0x8c, 0x13, 0x1f, 0x82, 0x3d, 0x2c, 0x06, 0xe2, 0x7e, 0x4f, 0xca, 0xec, 0x9e, 0xf3, 0xcf, 0x78,
        0x8a, 0x3b, 0x0a, 0xa3, 0x72, 0x60, 0x0a, 0x92, 0xb5, 0x79, 0x74, 0xcd, 0xed, 0x2b, 0x93, 0x34,
        0x79, 0x4c, 0xba, 0x40, 0xc6, 0x3e, 0x34, 0xcd, 0xea, 0x21, 0x2c, 0x4c, 0xf0, 0x7d, 0x41, 0xb7,
        0x69, 0xa6, 0x74, 0x9f, 0x3f, 0x63, 0x0f, 0x41, 0x22, 0xca, 0xfe, 0x28, 0xec, 0x4d, 0xc4, 0x7e,
        0x26, 0xd4, 0x34, 0x6d, 0x70, 0xb9, 0x8c, 0x73, 0xf3, 0xe9, 0xc5, 0x3a, 0xc4, 0x0c, 0x59, 0x45,
        0x39, 0x8b, 0x6e, 0xda, 0x1a, 0x83, 0x2c, 0x89, 0xc1, 0x67, 0xea, 0xcd, 0x90, 0x1d, 0x7e, 0x2b,
        0xf3, 0x63, 0x74, 0x03, 0x73, 0x20, 0x1a, 0xa1, 0x88, 0xfb, 0xbc, 0xe8, 0x39, 0x91, 0xc4, 0xed
    };

    uint8_t ks_actual[KSLEN] = { 0 };

    chacha20_keystream(ks_actual, key, BLOCKS, nonce);

    return compare_keystreams(ks_actual, ks_expected, KSLEN);


#undef BLOCKS
#undef KSLEN
}

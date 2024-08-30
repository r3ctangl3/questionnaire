#include "chacha20.h"


/* --------------------------------------------------------- */
/*                 S T A T I C   D A T A                     */
/* --------------------------------------------------------- */


#define KSLEN_WORDS     (CHACHA20_KSLEN_1BLOCK / CHACHA20_WORDLEN)

#define CONST_WORD_0    0x61707865
#define CONST_WORD_1    0x3320646e
#define CONST_WORD_2    0x79622d32
#define CONST_WORD_3    0x6b206574

#define KEY_OFFSET      (16 / CHACHA20_WORDLEN)
#define BLOCK_OFFSET    (48 / CHACHA20_WORDLEN)
#define NONCE_OFFSET    (52 / CHACHA20_WORDLEN)


// keystream pre-initial state
static word_t init[KSLEN_WORDS] =
{
    CONST_WORD_0,  CONST_WORD_1,  CONST_WORD_2,  CONST_WORD_3,
    0x0,           0x0,           0x0,           0x0,
    0x0,           0x0,           0x0,           0x0,
    0x0,           0x0,           0x0,           0x0,
};


/* --------------------------------------------------------- */
/*             S T A T I C   F U N C T I O N S               */
/* --------------------------------------------------------- */


// keystream generation
static void prepare_state_static_data(const uint8_t* key, const uint8_t* nonce);
static void prepare_state_dynamic_data(word_t block);
static void generate_ks_single_block(word_t* oper);
static void do_round(word_t* buf);
static void do_quarter_round(word_t* buf, size_t a, size_t b, size_t c, size_t d);


// handle endianness
static bool is_big_endian();
static word_t assign_as_is(word_t val);
static word_t assign_swap_bytes(word_t val);
static word_t (*assign)(word_t) = NULL;


// utils
static word_t swap_bytes(word_t val);
static word_t bitwise_left_rotate(word_t val, size_t bits);


/* --------------------------------------------------------- */
/*                A P I   F U N C T I O N S                  */
/* --------------------------------------------------------- */


void
chacha20_init()
{
    assign = is_big_endian() ? assign_swap_bytes : assign_as_is;
}


void
chacha20_keystream(uint8_t* dest, const uint8_t* key, word_t blocks, const uint8_t* nonce)
{
    // chacha20 initial state must be stored during all rounds
    // because the last state before serializing the array into
    // keystream is sum of initial state and state after all rounds
    word_t oper[KSLEN_WORDS] = { 0 };

    prepare_state_static_data(key, nonce);

    for (word_t block = 1; block <= blocks; ++block)
    {
        prepare_state_dynamic_data(block);

        memcpy(oper, init, CHACHA20_KSLEN_1BLOCK);

        generate_ks_single_block(oper);

        memcpy(dest + (block - 1) * CHACHA20_KSLEN_1BLOCK, oper, CHACHA20_KSLEN_1BLOCK);
    }

    return;
}


/* --------------------------------------------------------- */
/*             S T A T I C   F U N C T I O N S               */
/* --------------------------------------------------------- */


static void
prepare_state_static_data(const uint8_t* key, const uint8_t* nonce)
{
    //  handle key
    //  need to check endianness because we get bytes array, but we handle it as numbers later

    word_t* key_32 = (word_t*)key;
    size_t begin = KEY_OFFSET;
    size_t end = begin + (CHACHA20_KEYLEN / CHACHA20_WORDLEN);

    for (size_t i = begin; i != end; ++i)
        init[i] = assign(key_32[i - begin]);

    // handle nonce
    // check endianness for 0 and 1 words, 2 word is taken as is

    word_t* nonce_32 = (word_t*)nonce;

    init[NONCE_OFFSET] = assign(nonce_32[0]);
    init[NONCE_OFFSET + 1] = assign(nonce_32[1]);
    init[NONCE_OFFSET + 2] = assign(nonce_32[2]);
}


static void
prepare_state_dynamic_data(word_t block)
{
    // insert block
    // no need to check endianness because we get the number, and not bytes array

    memcpy(init + BLOCK_OFFSET, &block, CHACHA20_WORDLEN);
}


static void
generate_ks_single_block(word_t* oper)
{
    // do 20 rounds
    for (int i = 0; i < 10; ++i)
        do_round(oper);

    // summ oper and init blocks
    for (int i = 0; i < 16; ++i)
        oper[i] += init[i];

    // serialize result
    if (is_big_endian())
        for (int i = 0; i < 16; ++i)
            oper[i] = swap_bytes(oper[i]);
}


static void
do_round(word_t* buf)
{
    // column round
    do_quarter_round(buf, 0, 4,  8, 12);
    do_quarter_round(buf, 1, 5,  9, 13);
    do_quarter_round(buf, 2, 6, 10, 14);
    do_quarter_round(buf, 3, 7, 11, 15);

    // diagonal round
    do_quarter_round(buf, 0, 5, 10, 15);
    do_quarter_round(buf, 1, 6, 11, 12);
    do_quarter_round(buf, 2, 7,  8, 13);
    do_quarter_round(buf, 3, 4,  9, 14);
}


static void
do_quarter_round(word_t* buf, size_t a, size_t b, size_t c, size_t d)
{
    // 1
    buf[a] += buf[b];
    buf[d] ^= buf[a];
    buf[d] = bitwise_left_rotate(buf[d], 16);

    // 2
    buf[c] += buf[d];
    buf[b] ^= buf[c];
    buf[b] = bitwise_left_rotate(buf[b], 12);

    // 3
    buf[a] += buf[b];
    buf[d] ^= buf[a];
    buf[d] = bitwise_left_rotate(buf[d], 8);

    // 4
    buf[c] += buf[d];
    buf[b] ^= buf[c];
    buf[b] = bitwise_left_rotate(buf[b], 7);
}


static bool
is_big_endian()
{
    uint16_t val = 0x0100;
    return *((uint8_t*)&val);
}


static word_t
assign_as_is(word_t val)
{
    return val;
}


static word_t
assign_swap_bytes(word_t val)
{
    return swap_bytes(val);
}


static word_t
swap_bytes(word_t val)
{
    return  ((val >> 24) & 0x000000ff) |
            ((val <<  8) & 0x00ff0000) |
            ((val >>  8) & 0x0000ff00) |
            ((val << 24) & 0xff000000);
}


static word_t
bitwise_left_rotate(word_t val, size_t bits)
{
    return ((val >> (sizeof(word_t) * 8 - bits)) | (val << bits));
}

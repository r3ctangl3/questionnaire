#ifndef CRYPTO_H
#define CRYPTO_H


#include "chacha20.h"
#include "libsodium-win64/include/sodium.h"


// define constants based on sodium library constants and limitations
#define BYTES_MIN        crypto_pwhash_scryptsalsa208sha256_BYTES_MIN
#define PASSWD_MIN       crypto_pwhash_scryptsalsa208sha256_PASSWD_MIN
#define SALT_BYTES       crypto_pwhash_scryptsalsa208sha256_SALTBYTES
#define OPS_LIMIT        crypto_pwhash_scryptsalsa208sha256_OPSLIMIT_INTERACTIVE     // TODO: [docs] must be the same for every generation!
#define MEM_LIMIT        crypto_pwhash_scryptsalsa208sha256_MEMLIMIT_INTERACTIVE     // TODO: [docs] must be the same for every generation!


// define custom crypto constants
#define SALT_WCHAR       (SALT_BYTES / sizeof(wchar_t))


// ckeck some assumptions which should not be broken but nevertheless
static_assert(CHAR_BIT == 8, "bits in byte");
static_assert((SALT_BYTES % 2) == 0, "sodium lib salt size constant");
static_assert(sizeof(wchar_t) == 2 * sizeof(uint8_t), "builtin types");
static_assert(sizeof(word_t) == sizeof(uint32_t), "chacha20 word type");


#include <QByteArray>
#include <QString>


namespace quest
{


enum class CryptoErr
{
    Ok = 0,
    Init,
    Key,
    Keystream,
    Nonce,
    Uncknown
};


// TODO: [impl] move into Crypto class
class KeyStream
{
private:

    QString ks_;

public:

    KeyStream(const uint8_t* key, uint32_t blocks, uint32_t nonce);

    // TODO: [impl] iterator

};


// TODO: [impl] reimplement as Singleton
class Crypto
{
private:

    static bool is_inited_;

    uint8_t key_[CHACHA20_KEYLEN];

    uint8_t salt_[SALT_WCHAR];

    uint32_t encrypt_nonce_ = 0;

    CryptoErr error_ = CryptoErr::Uncknown;

    std::unique_ptr<KeyStream> ks_decrypt = nullptr;

    std::unique_ptr<KeyStream> ks_encrypt = nullptr;

public:

    Crypto();

    bool ok();

    CryptoErr error();

    QString generate_random_salt();

    void set_salt(const QString& salt);

    void evaluate_key(const QString& password);

    void generate_keystreams(uint32_t blocks, uint32_t decrypt_nonce);

    uint32_t get_encrypt_nonce();

    void encrypt(QString& plain);

    void decrypt(QString& cypher);

private:

    void generate_encrypt_nonce();
};


}


#endif // CRYPTO_H

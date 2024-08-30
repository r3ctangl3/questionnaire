#include "crypto.h"
#include "utils.h"
#include "chacha20_tests/tests.h"


namespace quest
{


KeyStream::KeyStream(const uint8_t* key, uint32_t blocks, uint32_t nonce)
{
    //chacha20_keystream(nullptr, nullptr, 0, nullptr);
    printf("%s\n", chacha20_rfc_test() ? "ok" : "fail");
    return;
}


bool Crypto::is_inited_ = false;


Crypto::Crypto()
{
    // libsodium library must be inited only once and
    // does not require to be explicitely destroyed

    CryptoErr error = CryptoErr::Ok;

    do
    {
        if (is_inited_)
        {
            break;
        }

        if (sodium_init() < 0)
        {
            error = CryptoErr::Init;
            break;
        }

        is_inited_ = true;  // crypto is first time inited

    } while (0);

    error_ = error;

    return;
}


bool Crypto::ok()
{
    return error_ == CryptoErr::Ok;
}


CryptoErr Crypto::error()
{
    return error_;
}


QString Crypto::generate_random_salt()
{
    randombytes_buf(salt_, sizeof(salt_));    // always succeed

    error_ = CryptoErr::Ok;

    return QString::fromWCharArray(reinterpret_cast<wchar_t*>(salt_), SALT_WCHAR);
}


void Crypto::set_salt(const QString& salt)
{
    // TODO: [impl] https://forum.qt.io/topic/92621/convert-qstring-to-wchar_t/4
    // salt is given from database
}


void Crypto::evaluate_key(const QString& password)
{
    error_ = CryptoErr::Key;

    do
    {
        char* passwd_bytes = password.toUtf8().data();
        size_t passwd_size = strlen(passwd_bytes);

        if (passwd_size < PASSWD_MIN)
        {
            break;
        }

        int rc = crypto_pwhash_scryptsalsa208sha256( key_, sizeof(key_),
                                                     passwd_bytes, strlen(passwd_bytes),
                                                     salt_,
                                                     OPS_LIMIT,
                                                     MEM_LIMIT );
        if (rc != 0)
        {
            break;
        }

        error_ = CryptoErr::Ok;

    } while (0);

    return;
}


void Crypto::generate_keystreams(uint32_t blocks, uint32_t decrypt_nonce)
{
    generate_encrypt_nonce();

    // try
    // {
    //     ks_decrypt = std::make_unique<KeyStream>(key_, blocks, decrypt_nonce);
         ks_encrypt = std::make_unique<KeyStream>(key_, blocks, encrypt_nonce_);
    // }
    // catch (...)
    // {
    //     error_ = CryptoErr::Keystream;
    //     return;
    // }

    error_ = CryptoErr::Ok;
    return;
}


uint32_t Crypto::get_encrypt_nonce()
{
    if (encrypt_nonce_ == 0)
    {
        error_ = CryptoErr::Nonce;
    }
    else
    {
        error_ = CryptoErr::Ok;
    }

    return encrypt_nonce_;
}


void Crypto::encrypt(QString& plain)
{
    return;
}


void Crypto::decrypt(QString& cypher)
{
    return;
}


void Crypto::generate_encrypt_nonce()
{
    uint8_t buf[sizeof(encrypt_nonce_)] = { 0 };

    randombytes_buf(buf, sizeof(buf));  // always succeed

    encrypt_nonce_ = *reinterpret_cast<uint32_t*>(buf);

    error_ = CryptoErr::Ok;

    return;
}


}

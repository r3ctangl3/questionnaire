#include "crypto.h"
#include "utils.h"
#include "chacha20_tests/tests.h"


namespace quest
{


Crypto::KeyStream::KeyStream(const uint8_t* key, uint32_t blocks, uint32_t nonce)
{
    //chacha20_keystream(nullptr, nullptr, 0, nullptr);
    printf("%s\n", chacha20_rfc_test() ? "ok" : "fail");
    return;
}


Crypto* Crypto::instance_ = nullptr;


Crypto* Crypto::instance()
{
    static std::once_flag flag;

    auto lambda = [&]()
    {
        try
        {
            instance_ = new Crypto();
        }
        catch (const std::bad_alloc&)
        {
            // do nothing for now
        }
    };

    std::call_once(flag, lambda);

    return instance_;
}


bool Crypto::ok() noexcept
{
    return error_ == CryptoErr::Ok;
}


CryptoErr Crypto::error() noexcept
{
    return error_;
}


QString Crypto::generate_random_salt() noexcept
{
    randombytes_buf(salt_, sizeof(salt_));    // always succeed

    error_ = CryptoErr::Ok;

    return QString::fromWCharArray(reinterpret_cast<wchar_t*>(salt_), SALT_WCHAR);
}


void Crypto::set_salt(const QString& salt) noexcept
{
    salt.toWCharArray(reinterpret_cast<wchar_t*>(salt_));

    error_ = CryptoErr::Ok;
}


void Crypto::evaluate_key(const QString& password) noexcept
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


void Crypto::generate_keystreams(uint32_t encrypt_blocks, uint32_t decrypt_blocks, uint32_t decrypt_nonce) noexcept
{
    generate_encrypt_nonce();

    try
    {
        ks_decrypt = std::make_unique<KeyStream>(key_, decrypt_blocks, decrypt_nonce);
        ks_encrypt = std::make_unique<KeyStream>(key_, encrypt_blocks, encrypt_nonce_);
    }
    catch (...)
    {
        error_ = CryptoErr::Keystream;
        return;
    }

    error_ = CryptoErr::Ok;
    return;
}


uint32_t Crypto::get_encrypt_nonce() noexcept
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


void Crypto::encrypt(QString& plain) noexcept
{
    error_ = CryptoErr::Ok;

    return;
}


void Crypto::decrypt(QString& cypher) noexcept
{
    error_ = CryptoErr::Ok;

    return;
}


Crypto::Crypto() noexcept
{
    // libsodium library must be inited only once and
    // does not require to be explicitely destroyed

    if (sodium_init() < 0)
    {
        error_ = CryptoErr::Init;
        return;
    }

    error_ = CryptoErr::Ok;
    return;
}


void Crypto::generate_encrypt_nonce() noexcept
{
    uint8_t buf[sizeof(encrypt_nonce_)] = { 0 };

    randombytes_buf(buf, sizeof(buf));  // always succeed

    encrypt_nonce_ = *reinterpret_cast<uint32_t*>(buf);

    error_ = CryptoErr::Ok;

    return;
}


} // namespace quest

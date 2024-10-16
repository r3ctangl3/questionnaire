#include "utils.h"       // TODO: [debug] remove
#include "crypto.h"


namespace quest
{


Crypto* Crypto::instance_ = nullptr;


Crypto* Crypto::instance() noexcept
{
    static std::once_flag flag;

    auto lambda = [&]()
    {
        try
        {
            instance_ = new Crypto();

            if (!instance_->ok())
            {
                delete instance_;
                instance_ = nullptr;
                throw std::runtime_error("Crypto constructor");
            }
        }
        catch (const std::bad_alloc&)
        {
            // do nothing for now
        }
        catch (const std::runtime_error&)
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

        int rc = crypto_pwhash_scryptsalsa208sha256(key_, sizeof(key_),
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
    static auto encrypt_iter = ks_encrypt->begin<KeyStreamEncrypt>();

    qDebug() << encrypt_iter;

    // Real encryption is done here. After the call
    // plain string is no longer plain but contains
    // encrypted string of the same size.
    apply_ks(plain, encrypt_iter);

    QString result(plain.size() * 4, QChar(0));
    QChar* c = plain.data();
    qsizetype pos = 0;

    // To avoid unexpected problems with coding/deconding while
    // writing/reading encrypted data, it will be serialized into
    // string of string representations of wchar_t integer values.
    while (!c->isNull()) {
        result.replace(pos, 4, QString::asprintf("%04x", c->unicode()));
        c += 1;
        pos += 4;
    }

    // Reduce encryption cost
    plain = std::move(result);

    error_ = CryptoErr::Ok;
    return;
}


void Crypto::decrypt(QString& cypher) noexcept
{
    static auto decrypt_iter = ks_decrypt->begin<KeyStreamDecrypt>();
    // static auto decrypt_iter = ks_encrypt->begin<KeyStreamEncrypt>();    // TODO: [debug] in case if test during one session is required (remove after)
    static wchar_t arr[512] = { 0 };

    QString result;
    QChar* c = cypher.data();
    qsizetype pos = 0;

    // Encrypted data are passed into the function serialized into
    // string of string representations of wchar_t integer values
    // Before data is actually decrypted deserialization is required.
    while(!c->isNull()) {
        arr[pos] = static_cast<wchar_t>(QStringView(c, c + 4).toInt(nullptr, 16));
        c += 4;
        pos += 1;
    }
    result = QString::fromWCharArray(arr, pos);

    // Real decryption is done here. After the call
    // result string is no longer deserialized cypher
    // but contains decrypted string of the same size.
    apply_ks(result, decrypt_iter);

    // Reduce decryption cost
    cypher = std::move(result);

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


template <typename T>
void Crypto::apply_ks(QString& str, KeyStream::iterator<T>* ks_iter)
{
    const QChar *ks;
    QChar *data = str.data();

    while (!data->isNull())
    {
        ks = **ks_iter;
        data->unicode() = data->unicode() ^ ks->unicode();
        ++data;
    }

    return;
}


} // namespace quest

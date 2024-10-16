#ifndef CRYPTO_H
#define CRYPTO_H


#include <QString>
#include <iterator>     // std::default_sentinel
#include <mutex>        // std::call_once
#include <type_traits>  // std::is_same
#include <vector>


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


namespace quest
{


enum class CryptoErr
{
    Ok = 0,
    Init,
    Key,
    Keystream,
    Nonce,
    Encrypt,
    Decrypt,
    Uncknown
};


// All the work is done using two KeyStreams:
// one for decryption and one for encryption.
// To make possible having one Singltone iterator for
// each KeyStream these helper types are defined.
class KeyStreamDecrypt;
class KeyStreamEncrypt;
template <typename T>
concept KeyStreamType = std::is_same<T, KeyStreamDecrypt>::value || std::is_same<T, KeyStreamEncrypt>::value;


class Crypto
{
private:

    class KeyStream
    {
    private:

        QString ks_;

        bool is_chacha20_inited_ = false;

    public:

        template <KeyStreamType T>
        class iterator
        {
        private:

            static iterator* iter_;

            QChar* begin_ = nullptr;

            QChar* curr_ = nullptr;

        public:

            /// @brief KeyStream iterator instance getter.
            /// @param begin - first QChar* of keystream QString
            /// The class is implemented as Singleton to guarantee
            /// the same keystream is never used for different data.
            static iterator* instance(QChar* begin) noexcept;


            /// @brief Forbid copy and move constructors and assign operators
            iterator(iterator& other) = delete;
            iterator(iterator&& other) = delete;
            void operator=(iterator& other) = delete;
            void operator=(iterator&& other) = delete;


            /// @brief Detect if iteration is finished.
            /// @param ... - no actual comparison of two iterators is done.
            /// @return always return 'false'
            /// Current implementation allows the keystream 'overflow':
            /// if the keystream is over it starts from the beginnig.
            /// See operator++ overloads implementation for details.
            bool operator!= (std::default_sentinel_t);


            /// @brief Iterate to the next element.
            /// Both operator++ overloads actualy do nothing.
            /// See operator* overload implementation.
            void operator++();
            void operator++(int);


            /// @brief Return underlying value.
            /// Real iteration is sone here.
            const QChar* operator*();

        private:

            /// @brief Constructor.
            /// Always succeeded.
            iterator(QChar* begin) noexcept;


            /// @brief Destructor.
            /// As class is implemented as Singleton, no destruction is allowed
            /// until the program itself is over. Such an approach is suitable
            /// because this class doesn't actually own any resources which should
            /// be explicitely freed or any business logic to be necessarily done.
            ~iterator() = default;
        };

    public:

        KeyStream(const uint8_t* key, uint32_t blocks, uint32_t nonce);

        template <typename T>
        iterator<T>* begin();

        std::default_sentinel_t end();
    };


private:

    static Crypto* instance_;

    uint8_t key_[CHACHA20_KEYLEN];

    uint8_t salt_[SALT_BYTES];

    uint32_t encrypt_nonce_ = 0;

    CryptoErr error_ = CryptoErr::Uncknown;

    std::unique_ptr<KeyStream> ks_decrypt = nullptr;

    std::unique_ptr<KeyStream> ks_encrypt = nullptr;


public:

    /// @brief Crypto class instance getter.
    /// The class is implemented as Singleton to guarantee
    /// only one cryptography initialization per app run.
    static Crypto* instance() noexcept;


    /// @brief Forbid copy and move constructors and assign operators
    Crypto(Crypto& other) = delete;
    Crypto(Crypto&& other) = delete;
    void operator=(Crypto& other) = delete;
    void operator=(Crypto&& other) = delete;


    /// @brief Get info about if last operation succeed or failed.
    /// @return 'true' if last operation succeed, 'false' if failed.
    bool ok() noexcept;


    /// @brief Get last operation status.
    /// @return CryptoErr instance. Always succeed.
    CryptoErr error() noexcept;


    /// @brief Generate random SALT_BYTES and return as QString to store in database.
    /// @return QString instance. Always succeed.
    /// Random salt should be generated only once at app first launch.
    QString generate_random_salt() noexcept;


    /// @brief Set salt which will be used to evaluate key from password.
    /// @param salt - salt to be set.
    /// @return void. Always succeed.
    /// There is no corresponding getter because callee must take care.
    void set_salt(const QString& salt) noexcept;


    /// @brief Evaluate key which will be used to generate keystream.
    /// @param password - password to generate keystream from.
    /// @return void. Use error() to get status.
    /// Key is stored as private member.
    void evaluate_key(const QString& password) noexcept;


    /// @brief Generate 2 keystreams: decrypt (old) and encrypt (new).
    /// @param encrypt_blocks - number of blocks in encrypt keystream.
    /// @param decrypt_blocks - number of blocks in decrypt keystream.
    /// @param decrypt_nonce - unique nonce which was used to encrypt data last time.
    /// @return void. Use error() to get status.
    /// Keystreams are stored as private members.
    void generate_keystreams(uint32_t encrypt_blocks, uint32_t decrypt_blocks, uint32_t decrypt_nonce) noexcept;


    /// @brief Get nonce which is used to generate encrypt keystream
    /// @return uint32_t value. Use error() to get status.
    /// This method call makes sence only after the encrypt nonce is
    /// actually generated = after successful generate_keystreams() call.
    uint32_t get_encrypt_nonce() noexcept;


    /// @brief Encrypt given QString instance.
    /// @param plain - string to be encrypted.
    /// @return void. Always succeed.
    /// Encryption is done using encrypt keystream. Incoming strings are
    /// encrypted with different part of the keystream. If keystream is over
    /// it starts from the beginning. If such a behavior is not suitable,
    /// the class user is responsible for generating long enough keystream
    /// by passing encrypt_blocks param to generate_keystream() method.
    void encrypt(QString& plain) noexcept;


    /// @brief Decrypt given QString instance.
    /// @param cypher - string to be decrypted.
    /// @return void. Always succeed.
    /// Decryption is done using decrypt keystream. This class user is
    /// responsible for correct keystream is generated. So the params
    /// decrypt_blocks and decrypt_nonce of the same values as they were
    /// while encryption should be passed to generate_keystream() method.
    void decrypt(QString& cypher) noexcept;


private:

    /// @brief Constructor.
    /// Class instance is always created. Use error()
    /// to detect if any errors occur while creation.
    Crypto() noexcept;


    /// @brief Destructor.
    /// As class is implemented as Singleton, no destruction is allowed
    /// until the program itself is over. Such an approach is suitable
    /// because this class doesn't actually own any resources which should
    /// be explicitely freed or any business logic to be necessarily done.
    ~Crypto() = default;


    /// @brief Generate new nonce to be used while generating encrypt keystream.
    /// @return void. Always succeed.
    /// According to the crypto algoritm nonce must be unique for every keystream
    /// generated using the same key. This function generates nonce as random
    /// bytes array with almost no chance to generate the same nonce ever. But if
    /// already used nonces traking is required, this class user takes responsibility.
    void generate_encrypt_nonce() noexcept;


    /// @brief Apply keystream to the given string.
    /// @param str - the given string.
    /// @param ks_iter - itertor of keystream to be applied.
    /// Always succeed.
    template <typename T>
    void apply_ks(QString& str, KeyStream::iterator<T>* ks_iter);
};


} // namespace quest


#endif // CRYPTO_H

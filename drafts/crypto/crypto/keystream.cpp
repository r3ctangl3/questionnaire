#include "utils.h"                  // TODO: [debug] remove
#include "crypto.h"


namespace quest
{


template <KeyStreamType T>
Crypto::KeyStream::iterator<T>* Crypto::KeyStream::iterator<T>::iter_ = nullptr;



template <KeyStreamType T>
Crypto::KeyStream::iterator<T>* Crypto::KeyStream::iterator<T>::instance(QChar* begin) noexcept
{
    static std::once_flag flag;

    auto lambda = [&]()
    {
        try
        {
            iter_ = new iterator(begin);
        }
        catch (const std::bad_alloc&)
        {
            // do nothing for now
        }
    };

    std::call_once(flag, lambda);

    return iter_;
}


template <typename T>
bool Crypto::KeyStream::iterator<T>::operator!= (std::default_sentinel_t)
{
    return false;
}


template <typename T>
void Crypto::KeyStream::iterator<T>::operator++()
{
}


template <typename T>
void Crypto::KeyStream::iterator<T>::operator++(int)
{
}


template <typename T>
const QChar* Crypto::KeyStream::iterator<T>::operator*()
{
    QChar* ptr = curr_;

    // iteration with 'overflow' handling
    ++curr_;
    if (curr_->isNull())
        curr_ = begin_;

    return ptr;
}


template <typename T>
Crypto::KeyStream::iterator<T>::iterator(QChar* begin) noexcept :
    begin_(begin), curr_(begin)
{
}


Crypto::KeyStream::KeyStream(const uint8_t* key, uint32_t blocks, uint32_t nonce)
{
    if (!is_chacha20_inited_)
    {
        chacha20_init();
        is_chacha20_inited_ = true;
    }

    size_t kslen = CHACHA20_KSLEN(blocks);
    std::vector<uint8_t> vec(kslen);
    uint8_t* dest = vec.data();

    // chacha20 algorithm requires nonce to be CHACHA20_NONCELEN bytes
    uint32_t nonce_arr[CHACHA20_NONCELEN / sizeof(uint32_t)] = { 0, nonce, 0 };
    const uint8_t* nonce_ptr = reinterpret_cast<uint8_t*>(nonce_arr);

    chacha20_keystream(dest, key, blocks, nonce_ptr);
    ks_ = QString::fromWCharArray(reinterpret_cast<wchar_t*>(dest), kslen / sizeof(wchar_t));
}


template <typename T>
Crypto::KeyStream::iterator<T>* Crypto::KeyStream::begin()
{
    return iterator<T>::instance(ks_.data());
}


std::default_sentinel_t Crypto::KeyStream::end()
{
    return std::default_sentinel;
}


// Explicitely instantiate Crypto::KeyStream::iterator<T> related entities:
// keep it aligned with 'concept KeyStreamType' or will cause compile error.
template class Crypto::KeyStream::iterator<KeyStreamDecrypt>;
template class Crypto::KeyStream::iterator<KeyStreamEncrypt>;
template Crypto::KeyStream::iterator<KeyStreamDecrypt>* Crypto::KeyStream::begin();
template Crypto::KeyStream::iterator<KeyStreamEncrypt>* Crypto::KeyStream::begin();


} // namespace quest

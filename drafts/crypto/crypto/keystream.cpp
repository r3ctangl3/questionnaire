#include "utils.h"                  // TODO: [debug] remove
#include "crypto.h"


namespace quest
{


Crypto::KeyStream::iterator* Crypto::KeyStream::iterator::iter_ = nullptr;


Crypto::KeyStream::iterator* Crypto::KeyStream::iterator::instance(QChar* begin) noexcept
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


bool Crypto::KeyStream::iterator::operator!= (std::default_sentinel_t)
{
    return false;
}


void Crypto::KeyStream::iterator::operator++()
{
}


void Crypto::KeyStream::iterator::operator++(int)
{
}


const QChar* Crypto::KeyStream::iterator::operator*()
{
    QChar* ptr = curr_;

    // iteration with 'overflow' handling
    ++curr_;
    if (curr_->isNull())
        curr_ = begin_;

    return ptr;
}


Crypto::KeyStream::iterator::iterator(QChar* begin) noexcept :
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


Crypto::KeyStream::iterator* Crypto::KeyStream::begin()
{
    return iterator::instance(ks_.data());
}


std::default_sentinel_t Crypto::KeyStream::end()
{
    return std::default_sentinel;
}


} // namespace quest

#include "Client.h"


namespace quest
{


Client::Client(const std::string& f, const std::string& m, const std::string& l, const std::string& b)
    : firstName(f)
    , middleName(m)
    , lastName(l)
    , birth(b)
{
}


void Client::set_uid(const unsigned value)
{
    uid = value;
}


unsigned Client::get_uid()
{
    return uid;
}


}

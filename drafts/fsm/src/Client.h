#pragma once


#include <string>


namespace quest
{


class Client
{
private:
    unsigned uid;
    const std::string firstName;
    const std::string middleName;
    const std::string lastName;
    const std::string birth;

public:
    Client(const std::string& f, const std::string& m, const std::string& l, const std::string& b);
    void set_uid(const unsigned value);
    unsigned get_uid();
};


}

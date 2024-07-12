#include <string>
#include <vector>


#include "SingleTest.h"


namespace quest
{


/// @brief Represents tests assigned to particular client
class TestsSession
{
private:
    unsigned int uid;
    std::vector<quest::SingleTest> tests;

public:
    TestsSession(unsigned int uid, const std::vector<const quest::Methodology *>& methodics);
    std::vector<quest::SingleTest>& get_tests();
    unsigned int get_uid();
};


}
#include "TestsSession.h"


namespace quest
{


TestsSession::TestsSession(unsigned int uid, const std::vector<const quest::Methodology *>& methodics) : uid(uid)
{
    for (const auto& m : methodics)
    {
        tests.push_back(quest::SingleTest(m));
    }
}


std::vector<quest::SingleTest>& TestsSession::get_tests()
{
    return tests;
}


unsigned int TestsSession::get_uid()
{
    return uid;
}


}

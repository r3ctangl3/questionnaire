#include "Zung.h"


namespace quest
{


Zung::Zung() : Methodology("zung", quest::MethodicsNameHash::ZUNG)
{
}


void Zung::get_results()
{
    std::cout << "Zung results" << std::endl;
}


}

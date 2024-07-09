#pragma once


#include "Methodology.h"


namespace quest
{


class Zung : public Methodology
{
public:
    const std::string name = "zung";

public:
    Zung();
    void get_results() override;
};


}


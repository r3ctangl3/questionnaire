#pragma once


#include "Methodology.h"


namespace quest
{


class Beka : public Methodology
{
public:
    const std::string name = "beka";

public:
    Beka();
    void get_results() override;
};


}

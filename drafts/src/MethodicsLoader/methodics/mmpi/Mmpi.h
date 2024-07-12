#pragma once


#include "Methodology.h"


namespace quest
{


class Mmpi : public Methodology
{
public:
    Mmpi();
    void get_results() override;
};


}


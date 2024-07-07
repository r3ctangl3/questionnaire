#include <iostream>


#include "Exception.h"
#include "Methodology.h"
#include "Question.h"


int main()
{
    try
    {
        quest::Methodology m;

        for (auto& q : m.get_questions())
        {
            std::cout << q.get_text() << std::endl;
            std::cout << (int)q.get_answers_number() << std::endl;
            for (const auto& ans : q.get_answers())
                std::cout << ans << std::endl;
            std::cout << std::endl;
        }
    }
    catch (const quest::QuestException& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

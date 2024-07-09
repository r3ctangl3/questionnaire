#include <iostream>
#include <vector>


#include "Exception.h"
#include "Question.h"
#include "Methodics.h"


int main()
{
    try
    {
        quest::Beka b;
        quest::Zung z;
        std::vector<quest::Methodology*> ms = { &b, &z };
        
        for (auto& m : ms)
        {
            std::cout << std::endl;
            
            for (auto& q : m->get_questions())
            {
                std::cout << q.get_text() << std::endl;
                std::cout << (int)q.get_answers_number() << std::endl;
                for (const auto& ans : q.get_answers())
                    std::cout << ans << std::endl;
                std::cout << std::endl;
            }

            m->get_results();
        } 
        
    }
    catch (const quest::QuestException& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

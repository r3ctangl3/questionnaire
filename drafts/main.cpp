#include <iostream>
#include <vector>


#include "Exception.h"
#include "Question.h"
#include "SingleTest.h"
#include "MethodicsLoader.h"


int main()
{ 
    quest::MethodicsLoader ml;
    std::vector<const quest::Methodology *> methodics = ml.get_methodics( {"beka", "zung"} );
    
    try
    {
        quest::SingleTest st(methodics[0]);

        // Answering test
        auto ie = st.end();
        auto ib = st.begin();
        
        for (; ib != ie; ++ib)
        {
            std::cout << ib.get_current_question().get_text() << std::endl;
            std::cout << ib.get_current_question().get_answers_number() << std::endl;

            std::vector<int> answers;
            int currNum;
            std::string currAnsw;
            for(currNum = 0; currNum < ib.get_current_question().get_answers_number(); ++currNum)
            {
                std::cin >> currAnsw;
                answers.push_back(std::stoi(currAnsw));
            }

            ib.set_current_answer(std::move(answers));
        }

        // Testing answer
        ie = st.end();
        ib = st.begin();

        for (; ib != ie; ++ib)
        {
            std::cout << std::endl;
            for (const auto& a : ib.get_current_answer()) {
                std::cout << " - " << a;
            }
            std::cout << std::endl;
        }
    }
    catch (const quest::QuestException& e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}

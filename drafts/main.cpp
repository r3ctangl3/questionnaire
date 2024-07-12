#include <iostream>
#include <vector>


#include "Exception.h"
#include "Question.h"
#include "SingleTest.h"
#include "MethodicsLoader.h"
#include "TestsSession.h"


/*

int main()
{
    quest::MethodicsLoader ml;
    quest::Fsm fsm(&ml);

    int result;
    quest::FsmSignal signal;
    
    while (Fsm.is_running())
    {
        signal = get_fsm_signal();
        result = fsm.toggle(signal);
        if (!result) 
        {
            std::cout << "Error while toggle(): " << fsm.get_error() << std::endl; 
            std::cout << "Current state: " << fsm.get_curr_state() << std::endl; 
            continue;
        } 
    }
}

*/


int main()
{ 
    quest::MethodicsLoader ml;
    quest::TestsSession ts(42, ml.get_methodics( {"beka", "zung"} ));
    
    try
    {
        std::cout << "Hello, " << ts.get_uid() << "!\n" << std::endl;

        for (auto& st : ts.get_tests())
        {
            std::cout << "Start methodology: " << st.get_name()  << ".\n" << std::endl;

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
                
            std::cout << std::endl;
            for (; ib != ie; ++ib)
                for (const auto& a : ib.get_current_answer())
                    std::cout << a;
            std::cout << std::endl << "Finish methodology\n" << std::endl;
        }
    }
    catch (const quest::QuestException& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}



#include "MethodicsLoader.h"


namespace quest
{


enum class FsmSignalEnum
{
    BACK    ,
    NEXT    ,
    EXIT    ,
};


struct FsmSignal
{
    FsmSignalEnum signal;
    void* data;
};


enum class FsmStateEnum
{
    AUTHORIZATION     ,
    CLIENT_GREETING   ,
    TEST_DESCRIPTION  ,
    TEST_QUESTION     ,
    TEST_OUTRO        ,
    CLIENT_FAREWELL   ,
    EXIT_APPROVAL     ,
};


class FsmState
{
private:
    quest::FsmStateEnum state;

public:
    FsmState(quest::FsmStateEnum state);            // : state(state) {}
    bool toggle(quest::FsmSignalEnum signal);       // switch (signal) { case ... }

private:
    virtual bool proceed_back_signal() = 0; 
    virtual bool proceed_next_signal() = 0; 
    virtual bool proceed_exit_signal() = 0; 
};


struct QuestFsmContext
{
    const quest::MethodicsLoader* methodicsLoader;
    quest::FsmState* currState;
};


class QuestFsm
{
private:
    bool is_running;
    QuestFsmContext ctx;

public:
    QuestFsm(const quest::MethodicsLoader* ml);
    bool is_running();                              // return is_running;
    bool get_current_state_enum();                  // return ctx.currState.state;
    bool toggle(quest::FsmSignalEnum signal);       // return ctx.currState->toggle(&ctx)
};


/// @brief Represents client's executable FSM
class QuestClientFsm
{
private:
    quest::FsmState* currentState;

public:
    void toggle();
};


}

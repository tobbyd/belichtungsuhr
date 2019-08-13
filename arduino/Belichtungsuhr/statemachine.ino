#include "statemachine.h"

void StateMachine::setStates(BelState *states[], int totalStateNum) {
    m_states = states;
    m_totalStateNum = totalStateNum;
}
  
void StateMachine::setToState(int stateNum) {
    m_stateNum = stateNum;
    m_nextState = m_states[stateNum];
}

void StateMachine::prevState() {
    setToState((getCurrentStateNum() + m_totalStateNum - 1) % m_totalStateNum);
}

void StateMachine::nextState() {
    setToState((getCurrentStateNum() + 1) % m_totalStateNum);
}

void StateMachine::execState() {
    if(m_currentState != m_nextState) {
      beeper.state(StateMachine::instance().getCurrentStateNum());
      m_currentState->onExit();
      m_currentState = m_nextState;
      m_currentState->onEnter();
    }
}

BelState *StateMachine::getCurrentState() { return m_currentState; }

int StateMachine::getCurrentStateNum() { return m_stateNum; }

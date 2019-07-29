#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

enum class BelButton;

class BelState {
public:
	BelState() { }
	virtual ~BelState() { }
	virtual void onButtonClicked(const BelButton &button) = 0;
	virtual void onEnter() { }
	virtual void onExit() { }
	virtual void onTimerUp() { }
	virtual void onTimerUpdate(const unsigned long remainingMs) { }
};

class DummyState : public BelState {
public:
	virtual void onButtonClicked(const BelButton &button) { }
};

class StateMachine {
public:
	static StateMachine & instance() {
		static StateMachine m_instance;
		return m_instance;
	}

	void setStates(BelState *states[], int totalStateNum) {
		m_states = states;
		m_totalStateNum = totalStateNum;
	}
	
	void setToState(int stateNum) {
		m_stateNum = stateNum;
		m_nextState = m_states[stateNum];
	}
	void prevState() {
		setToState((getCurrentStateNum() + m_totalStateNum - 1) % m_totalStateNum);
	}
	void nextState() {
		setToState((getCurrentStateNum() + 1) % m_totalStateNum);
	}
	void execState() {
		if(m_currentState != m_nextState) {
			m_currentState->onExit();
			m_currentState = m_nextState;
			m_currentState->onEnter();
		}
	}

	BelState *getCurrentState() { return m_currentState; }
	int getCurrentStateNum() { return m_stateNum; }
private:
	StateMachine() : 
		m_currentState(new DummyState()),
       		m_nextState(m_currentState) { }

	int m_stateNum;
	int m_totalStateNum;
	BelState *m_currentState;
	BelState *m_nextState;

	BelState **m_states;

};




#endif // _STATEMACHINE_H

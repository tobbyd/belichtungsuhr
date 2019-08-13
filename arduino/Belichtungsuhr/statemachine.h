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

	void setStates(BelState *states[], int totalStateNum);
	
	void setToState(int stateNum);
	void prevState();
	void nextState();
	void execState();

	BelState *getCurrentState();
	int getCurrentStateNum();
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

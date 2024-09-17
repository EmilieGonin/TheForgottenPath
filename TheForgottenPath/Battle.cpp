#include "Battle.h"
#include "BattleStates.h"

Battle::Battle()
{
	m_currentState = &PlayerTurn::GetInstance();
	m_renderer = new ConsoleRenderer();
}

void Battle::SetState(BattleState& newState)
{
	m_currentState->Exit(this);
	m_currentState = &newState;
	m_currentState->Enter(this);
}

void Battle::Update()
{
	m_currentState->Update(this);
}

void Battle::Toggle()
{
	m_currentState->Toggle(this);
}

bool Battle::BattleIsOver()
{
	return m_currentState == &Win::GetInstance() || m_currentState == &Lose::GetInstance();
}
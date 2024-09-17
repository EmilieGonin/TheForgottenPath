#include "Battle.h"
#include "BattleStates.h"

Battle::Battle()
{
	m_currentState = &PlayerTurn::GetInstance();
	m_renderer = new ConsoleRenderer();
	m_gm = GameManager::GetInstance();

	m_turnIndex = 1;
}

Monster Battle::GetTurnMonster()
{
	return m_gm->GetMonsters()[m_turnIndex - 1];
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

bool Battle::TurnIsOver()
{
	m_turnIndex++;

	if (m_turnIndex > m_gm->GetMonsters().size())
	{
		m_turnIndex = 1;
		m_gm->GetPlayer()->OnEndTurn();
		for (Monster m : m_gm->GetMonsters()) m.OnEndTurn();
		return true;
	}

	return false;
}
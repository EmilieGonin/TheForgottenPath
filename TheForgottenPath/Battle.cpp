#include "Battle.h"
#include "BattleStates.h"

Battle::Battle()
{
	m_currentState = &PlayerTurn::GetInstance();
	m_renderer = new ConsoleRenderer();
	m_gm = GameManager::GetInstance();

	m_turnIndex = 0;
}

Monster* Battle::GetTurnMonster()
{
	return m_gm->GetMonsters()[m_turnIndex - 1];
}

void Battle::SetState(BattleState& newState)
{
	m_currentState = &newState;
	m_currentState->Enter(this);
}

void Battle::Update()
{
	m_currentState->Update(this);
}

bool Battle::BattleIsOver()
{
	return m_currentState == &Win::GetInstance() || m_currentState == &Lose::GetInstance();
}

bool Battle::BattleIsWin()
{
	bool win = true;

	for (Monster* m : GetGM()->GetMonsters())
	{
		if (!m->IsDead())
		{
			win = false;
			break;
		}
	}

	return win;

	if (win)
	{
		SetState(Win::GetInstance());
		return true;
	}
}

bool Battle::TurnIsOver()
{
	m_turnIndex++;

	if (m_turnIndex > m_gm->GetMonsters().size())
	{
		m_turnIndex = 0;
		m_gm->GetPlayer()->OnEndTurn();
		for (Monster* m : m_gm->GetMonsters()) m->OnEndTurn();
		m_renderer->ResetPreviousMovementCells();
		for (auto s : m_gm->GetPlayer()->GetSkills()) s.first->Tick();
		m_renderer->Render();
		return true;
	}

	return false;
}
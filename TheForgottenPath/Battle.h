#pragma once

#include "BattleState.h"
#include "ConsoleRenderer.h"
#include "GameManager.h"

class Battle
{
public:
	Battle();

	BattleState* GetCurrentState() const { return m_currentState; }
	ConsoleRenderer* GetRenderer() const { return m_renderer; }
	GameManager* GetGM() const { return m_gm; }

	Monster* GetTurnMonster();

	void SetState(BattleState& newState);
	void Update();

	bool BattleIsOver();
	bool TurnIsOver();

private:
	BattleState* m_currentState;
	ConsoleRenderer* m_renderer;
	GameManager* m_gm;

	int m_turnIndex;
};
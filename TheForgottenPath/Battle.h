#pragma once

#include "BattleState.h"
#include "ConsoleRenderer.h"

class Battle
{
public:
	Battle();

	BattleState* GetCurrentState() const { return m_currentState; }
	ConsoleRenderer* GetRenderer() const { return m_renderer; }

	void SetState(BattleState& newState);
	void Update();
	void Toggle();

	bool BattleIsOver();

private:
	BattleState* m_currentState;
	ConsoleRenderer* m_renderer;
};
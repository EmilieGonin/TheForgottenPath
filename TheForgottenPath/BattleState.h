#pragma once

#include "GameManager.h"

class Battle;

class BattleState
{
public:
	BattleState();

	virtual void Enter(Battle* battle) = 0;
	virtual void Update(Battle* battle) = 0;
	virtual void Toggle(Battle* battle) = 0;
	virtual void Exit(Battle* battle) = 0;
	virtual ~BattleState() {}

protected:
	GameManager* m_gm;
};
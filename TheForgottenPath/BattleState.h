#pragma once

class Battle;

class BattleState
{
public:
	virtual void Enter(Battle* battle) = 0;
	virtual void Update(Battle* battle) = 0;
	virtual void Toggle(Battle* battle) = 0;
	virtual void Exit(Battle* battle) = 0;
	virtual ~BattleState() {}
};
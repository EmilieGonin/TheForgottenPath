#pragma once

class Battle;

class BattleState
{
public:
	virtual void Enter(Battle* battle) = 0;
	virtual void Update(Battle* battle) = 0;
	virtual ~BattleState() {}
};
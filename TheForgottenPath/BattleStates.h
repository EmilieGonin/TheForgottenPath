#pragma once

#include "BattleState.h"
#include "Battle.h"

class PlayerTurn : public BattleState
{
public:
	void Enter(Battle* battle) { }
	void Update(Battle* battle);
	void Toggle(Battle* battle) { }
	void Exit(Battle* battle) { }
	static BattleState& GetInstance();

private:
	std::map<int, bool> m_actionsKeys;
};

class EnemyTurn : public BattleState
{
public:
	void Enter(Battle* battle);
	void Update(Battle* battle) { }
	void Toggle(Battle* battle) { }
	void Exit(Battle* battle);
	static BattleState& GetInstance();
};

class EndCheck : public BattleState
{
public:
	void Enter(Battle* battle);
	void Update(Battle* battle) { }
	void Toggle(Battle* battle) { }
	void Exit(Battle* battle) { }
	static BattleState& GetInstance();
};

class Win : public BattleState
{
public:
	void Enter(Battle* battle) { }
	void Update(Battle* battle) { }
	void Toggle(Battle* battle) { }
	void Exit(Battle* battle) { }
	static BattleState& GetInstance();
};

class Lose : public BattleState
{
public:
	void Enter(Battle* battle) { }
	void Update(Battle* battle) { }
	void Toggle(Battle* battle) { }
	void Exit(Battle* battle) { }
	static BattleState& GetInstance();
};
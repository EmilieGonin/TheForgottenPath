#pragma once

#include <string>

#include "BattleState.h"
#include "Battle.h"

#define KEY_S 0x53
#define KEY_H 0x48

class PlayerTurn : public BattleState
{
public:
	void Enter(Battle* battle) { }
	void Update(Battle* battle);
	static BattleState& GetInstance();

private:
	std::map<int, bool> m_actionsKeys;
};

class EnemyTurn : public BattleState
{
public:
	void Enter(Battle* battle);
	void Update(Battle* battle) { }
	static BattleState& GetInstance();

private:
	void Attack(Battle* battle);
};

class EndCheck : public BattleState
{
public:
	void Enter(Battle* battle);
	void Update(Battle* battle) { }
	static BattleState& GetInstance();
};

class Win : public BattleState
{
public:
	void Enter(Battle* battle);
	void Update(Battle* battle) { }
	static BattleState& GetInstance();
};

class Lose : public BattleState
{
public:
	void Enter(Battle* battle);
	void Update(Battle* battle) { }
	static BattleState& GetInstance();
};
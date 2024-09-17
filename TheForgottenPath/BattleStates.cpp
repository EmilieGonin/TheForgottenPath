#include "BattleStates.h"

void PlayerTurn::Update(Battle* battle)
{
	//
}

BattleState& PlayerTurn::GetInstance()
{
	static PlayerTurn singleton;
	return singleton;
}

BattleState& EnemyTurn::GetInstance()
{
	static EnemyTurn singleton;
	return singleton;
}

BattleState& Win::GetInstance()
{
	static Win singleton;
	return singleton;
}

BattleState& Lose::GetInstance()
{
	static Lose singleton;
	return singleton;
}
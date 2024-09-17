#include "BattleStates.h"

void PlayerTurn::Update(Battle* battle)
{
	if (m_gm->GetPlayer()->CanMove())
	{
		battle->GetRenderer()->PlayerController();
	}
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
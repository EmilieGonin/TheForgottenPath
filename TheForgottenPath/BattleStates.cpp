#include "BattleStates.h"

void PlayerTurn::Update(Battle* battle)
{
	if (battle->GetGM()->GetPlayer()->CanMove())
	{
		battle->GetRenderer()->PlayerController();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		battle->SetState(EnemyTurn::GetInstance());
	}

	if (GetAsyncKeyState(VK_EXECUTE) & 0x8000)
	{
		//
	}
}

BattleState& PlayerTurn::GetInstance()
{
	static PlayerTurn singleton;
	return singleton;
}

void EnemyTurn::Enter(Battle* battle)
{
	// vérifier si le joueur est à proximité

	if (battle->TurnIsOver())
	{
		battle->SetState(PlayerTurn::GetInstance());
	}

	else battle->SetState(EnemyTurn::GetInstance());
}

void EnemyTurn::Exit(Battle* battle)
{
	//
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
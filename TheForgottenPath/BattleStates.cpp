#include "BattleStates.h"

void PlayerTurn::Update(Battle* battle)
{
	if (battle->GetGM()->GetPlayer()->CanMove())
	{
		battle->GetRenderer()->PlayerController();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		battle->SetState(EndCheck::GetInstance());
	}

	// Vérifier si un ennemi est à proximité
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
	Monster* m = battle->GetTurnMonster();

	if (!m->IsDead())
	{
		do
		{
			bool isPlayerClose = battle->GetRenderer()->GetCloseEntity(m) == battle->GetGM()->GetPlayer();

			if (isPlayerClose)
			{
				//
				break;
			}

			if (m->CanMove()) battle->GetRenderer()->MoveMonster(m);
		} while (m->CanMove());
	}

	battle->SetState(EndCheck::GetInstance());
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

void EndCheck::Enter(Battle* battle)
{
	if (battle->GetGM()->GetPlayer()->IsDead())
	{
		battle->SetState(Lose::GetInstance());
		return;
	}
	else
	{
		bool win = true;

		for (Monster* m : battle->GetGM()->GetMonsters())
		{
			if (!m->IsDead())
			{
				win = false;
				break;
			}
		}

		if (win)
		{
			battle->SetState(Win::GetInstance());
			return;
		}
	}
	
	
	if (battle->TurnIsOver())
	{
		battle->SetState(PlayerTurn::GetInstance());
	}

	else battle->SetState(EnemyTurn::GetInstance());
}

BattleState& EndCheck::GetInstance()
{
	static EndCheck singleton;
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
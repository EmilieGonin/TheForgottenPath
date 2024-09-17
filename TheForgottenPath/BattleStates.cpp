#include "BattleStates.h"

void PlayerTurn::Update(Battle* battle)
{
	if (battle->GetGM()->GetPlayer()->CanMove())
	{
		battle->GetRenderer()->PlayerController();
	}

	bool isSpacePressed = GetAsyncKeyState(VK_SPACE) & 0x8000;
	bool wasSpacePressed = m_actionsKeys[VK_SPACE];

	bool isEnterPressed = GetAsyncKeyState(VK_EXECUTE) & 0x8000;
	bool wasEnterPressed = m_actionsKeys[VK_EXECUTE];

	if (!isSpacePressed && wasSpacePressed) battle->SetState(EndCheck::GetInstance());

	if (!isEnterPressed && wasEnterPressed)
	{
		// Attaque
	}

	m_actionsKeys[VK_SPACE] = isSpacePressed;
	m_actionsKeys[VK_EXECUTE] = isEnterPressed;
}

BattleState& PlayerTurn::GetInstance()
{
	static PlayerTurn singleton;
	return singleton;
}

void EnemyTurn::Enter(Battle* battle)
{
	Monster* m = battle->GetTurnMonster();
	Player* p = battle->GetGM()->GetPlayer();

	if (!m->IsDead())
	{
		do
		{
			bool isPlayerClose = battle->GetRenderer()->GetCloseEntity(m) == p;

			if (isPlayerClose)
			{
				p->TakeDamage(m->GetStat(Stat::ATK));
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
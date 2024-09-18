#include "BattleStates.h"

void PlayerTurn::Update(Battle* battle)
{
	if (battle->GetGM()->GetPlayer()->HasEnoughPM())
	{
		battle->GetRenderer()->PlayerController();
	}

	bool isSpacePressed = GetAsyncKeyState(VK_SPACE) & 0x8000;
	bool isEnterPressed = GetAsyncKeyState(VK_RETURN) & 0x8000;

	if (!isSpacePressed && m_actionsKeys[VK_SPACE])
	{
		battle->SetState(EndCheck::GetInstance());
	}

	if (!isEnterPressed && m_actionsKeys[VK_RETURN])
	{
		Player* p = battle->GetGM()->GetPlayer();
		Entity* target = battle->GetRenderer()->GetCloseEntity(battle->GetGM()->GetPlayer());

		if (target != nullptr)
		{
			target->TakeDamage(p->GetStat(Stat::ATK));
			// Afficher log dans console
			battle->SetState(EndCheck::GetInstance());
		}
	}

	m_actionsKeys[VK_SPACE] = isSpacePressed;
	m_actionsKeys[VK_RETURN] = isEnterPressed;
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
	Behaviour behaviour = m->GetBehaviour();

	if (!m->IsDead())
	{
		do
		{
			bool isPlayerClose = battle->GetRenderer()->GetCloseEntity(m) == p;

			if (isPlayerClose && behaviour != Behaviour::Flee)
			{
				Attack(battle);
				break;
			}

			if (m->HasEnoughPM() && behaviour != Behaviour::Static)
			{
				if (battle->GetRenderer()->MoveMonster(m))
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
				}
				else if (behaviour == Behaviour::Flee && isPlayerClose)
				{
					Attack(battle);
					break;
				}
			}
		} while (behaviour != Behaviour::Static && m->HasEnoughPM());
	}

	battle->SetState(EndCheck::GetInstance());
}

BattleState& EnemyTurn::GetInstance()
{
	static EnemyTurn singleton;
	return singleton;
}

void EnemyTurn::Attack(Battle* battle)
{
	Monster* m = battle->GetTurnMonster();
	Player* p = battle->GetGM()->GetPlayer();

	p->TakeDamage(m->GetStat(Stat::ATK));
	// Afficher log dans console
	battle->GetRenderer()->Display();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

void Win::Enter(Battle* battle)
{
	// Message log
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	battle->GetGM()->WinBattle();
	battle->GetRenderer()->Display();
}

BattleState& Win::GetInstance()
{
	static Win singleton;
	return singleton;
}

void Lose::Enter(Battle* battle)
{
	// Message log
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	battle->GetGM()->StartNewGame();
	battle->GetRenderer()->Display();
}

BattleState& Lose::GetInstance()
{
	static Lose singleton;
	return singleton;
}
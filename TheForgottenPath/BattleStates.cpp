#include "BattleStates.h"
#include "Utilities.h"

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

		if (target != nullptr && p->GetStat(Stat::PA) > 0)
		{
			p->SetStat(Stat::PA, -1);

			int damage = target->TakeDamage(p);

			string s = " " + p->GetName() + " attacks " + target->GetName() + "," + "\n" + "                                              " + "   it loses " + std::to_string(static_cast<int>(damage)) + " HP";
			battle->GetRenderer()->SetLog(s);
			battle->GetRenderer()->Render();

			if (target->IsDead())
			{
				battle->GetRenderer()->RemoveEntity(target);
				target->OnDeath(battle->GetGM());
				Utilities::Wait(500);

				if (battle->BattleIsWin())
				{
					battle->SetState(Win::GetInstance());
					return;
				}
			}

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
					Utilities::Wait(200);
				}
				else if (behaviour == Behaviour::Flee && isPlayerClose)
				{
					Attack(battle);
					break;
				}
			}
			else
			{
				m->StopActionEarly();
			}

		} while (m->HasEnoughPM() || m->HasEnoughPA());
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

	while (m->GetStat(Stat::PA) > 0)
	{
		m->SetStat(Stat::PA, -1);
		int damage = p->TakeDamage(m);
		string s = " " + m->GetName() + " attacks " + p->GetName() + "," + "\n" + "                                              " + "   it loses " + std::to_string(static_cast<int>(damage)) + " HP";
		battle->GetRenderer()->SetLog(s);
		battle->GetRenderer()->Render();
		Utilities::Wait(500);
	}
}

void EndCheck::Enter(Battle* battle)
{
	if (battle->GetGM()->GetPlayer()->IsDead())
	{
		battle->SetState(Lose::GetInstance());
		return;
	}
	else if (battle->BattleIsWin())
	{
		battle->SetState(Win::GetInstance());
		return;
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
	string s = "You win !";
	battle->GetRenderer()->SetLog(s);
	battle->GetRenderer()->Render();
	Utilities::Wait(500);
	battle->GetGM()->WinBattle();

	battle->GetGM()->StartNewBattle();
	battle->GetRenderer()->Render();
}

BattleState& Win::GetInstance()
{
	static Win singleton;
	return singleton;
}

void Lose::Enter(Battle* battle)
{
	string s = "You lose !";
	battle->GetRenderer()->SetLog(s);
	battle->GetRenderer()->Render();
	Utilities::Wait(500);

	battle->GetGM()->StartNewBattle();
	battle->GetRenderer()->Render();
}

BattleState& Lose::GetInstance()
{
	static Lose singleton;
	return singleton;
}
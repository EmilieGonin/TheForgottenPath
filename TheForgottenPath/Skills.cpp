#include "Skills.h"
#include "GameManager.h"
//#include "Player.h"

Shield::Shield(Player* p)
{
	m_player = p;

	m_activeCooldown = std::make_pair(-1, 2);
	m_cooldown = std::make_pair(0, 3);
}

void Shield::Use()
{
	Skill::Use();

	m_player->SetStat(Stat::DEF, 5);
}

void Shield::Cancel()
{
	m_player->SetStat(Stat::DEF, -5);
}

Heal::Heal(Player* p)
{
	m_player = p;

	m_activeCooldown = std::make_pair(-1, 0);
	m_cooldown = std::make_pair(0, 4);
}

void Heal::Use()
{
	Skill::Use();

	m_player->SetStat(Stat::HP, 50);
}

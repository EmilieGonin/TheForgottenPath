#include "Monsters.h"
#include "GameManager.h"

Golem::Golem()
{
	m_name = "Golem";
	m_stats[Stat::HP] = 100;
	m_stats[Stat::MAXHP] = 100;
	m_stats[Stat::DEF] = 10;
	m_stats[Stat::ATK] = 8;
	m_stats[Stat::MAXATK] = 12;
	m_stats[Stat::PM] = 0;
	m_stats[Stat::MAXPM] = 0;
	m_stats[Stat::PA] = 1;
	m_stats[Stat::MAXPA] = 1;
	m_behaviour = Behaviour::Static;
	m_icon = 'G';
	m_color = 13;		// Magenta clair
	m_pos.first = 5;
	m_pos.second = 8;
}

void Golem::OnDeath(GameManager* gm)
{
	gm->GetPlayer()->SetStat(Stat::ATK, 5);
}

int Golem::TakeDamage(Entity* attacker)
{
	int rand = std::rand() % 100;
	if (rand > 15) return Entity::TakeDamage(attacker);
	return 0;
}

Reaper::Reaper() // Faucheur
{
	m_name = "Reaper";
	m_stats[Stat::HP] = 75;
	m_stats[Stat::MAXHP] = 75;
	m_stats[Stat::DEF] = 5;
	m_stats[Stat::ATK] = 20;
	m_stats[Stat::MAXATK] = 25;
	m_stats[Stat::PM] = 3;
	m_stats[Stat::MAXPM] = 3;
	m_stats[Stat::PA] = 1;
	m_stats[Stat::MAXPA] = 1;
	m_icon = 'F';
	m_color = 4;		// Rouge foncé
	m_pos.first = 7;
	m_pos.second = 7;
}

void Reaper::OnDeath(GameManager* gm)
{
	for (Monster* m : gm->GetMonsters()) m->TakeDamage(this);
}

Wraith::Wraith() // Spectre
{
	m_name = "Wraith";
	m_stats[Stat::HP] = 60;
	m_stats[Stat::MAXHP] = 60;
	m_stats[Stat::DEF] = 3;
	m_stats[Stat::ATK] = 7;
	m_stats[Stat::MAXATK] = 7;
	m_stats[Stat::PM] = 4;
	m_stats[Stat::MAXPM] = 4;
	m_stats[Stat::PA] = 1;
	m_stats[Stat::MAXPA] = 1;	
	m_behaviour = Behaviour::Flee;
	m_icon = 'S';
	m_color = 3;		// Bleu clair
	m_pos.first = 8;
	m_pos.second = 2;
}

void Wraith::OnDeath(GameManager* gm)
{
	Player* p = gm->GetPlayer();
	gm->GetPlayer()->SetStat(Stat::HP, p->GetStat(Stat::MAXHP) - p->GetStat(Stat::HP));
}
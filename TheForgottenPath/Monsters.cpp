#include "Monsters.h"
#include "GameManager.h"

Golem::Golem()
{
	m_name = "Golem";
	m_stats[Stat::HP] = 75;
	m_stats[Stat::MAXHP] = 75;
	m_stats[Stat::DEF] = 8;
	m_stats[Stat::ATK] = 10;
	m_stats[Stat::MAXATK] = 12;
	m_stats[Stat::PM] = 0;
	m_stats[Stat::MAXPM] = 0;
	m_stats[Stat::PA] = 1;
	m_stats[Stat::MAXPA] = 1;
	m_behaviour = Behaviour::Static;
	m_icon = 'G';
	m_color = 13;		// Magenta clair
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
	m_stats[Stat::DEF] = 3;
	m_stats[Stat::ATK] = 20;
	m_stats[Stat::MAXATK] = 25;
	m_stats[Stat::PM] = 3;
	m_stats[Stat::MAXPM] = 3;
	m_stats[Stat::PA] = 2;
	m_stats[Stat::MAXPA] = 2;
	m_icon = 'F';
	m_color = 4;		// Rouge foncé
}

void Reaper::OnDeath(GameManager* gm)
{
	for (Monster* m : gm->GetMonsters()) m->TakeDamage(this);
}

Wraith::Wraith() // Spectre
{
	m_name = "Wraith";
	m_stats[Stat::HP] = 80;
	m_stats[Stat::MAXHP] = 80;
	m_stats[Stat::DEF] = 2;
	m_stats[Stat::ATK] = 6;
	m_stats[Stat::MAXATK] = 10;
	m_stats[Stat::PM] = 3;
	m_stats[Stat::MAXPM] = 3;
	m_stats[Stat::PA] = 1;
	m_stats[Stat::MAXPA] = 1;	
	m_behaviour = Behaviour::Flee;
	m_icon = 'S';
	m_color = 3;		// Bleu clair
}

void Wraith::OnDeath(GameManager* gm)
{
	Player* p = gm->GetPlayer();
	gm->GetPlayer()->SetStat(Stat::HP, p->GetStat(Stat::MAXHP) - p->GetStat(Stat::HP));
}

Titan::Titan()
{
	m_name = "Titan";
	m_stats[Stat::HP] = 250;
	m_stats[Stat::MAXHP] = 250;
	m_stats[Stat::DEF] = 5;
	m_stats[Stat::ATK] = 30;
	m_stats[Stat::MAXATK] = 35;
	m_stats[Stat::PM] = 0;
	m_stats[Stat::MAXPM] = 0;
	m_stats[Stat::PA] = 2;
	m_stats[Stat::MAXPA] = 2;
	m_behaviour = Behaviour::Static;
	m_icon = 'T';
	m_color = 5;		// Magenta foncé
}

Mastiff::Mastiff()
{
	m_name = "Mastiff";		// Molosse
	m_stats[Stat::HP] = 120;
	m_stats[Stat::MAXHP] = 120;
	m_stats[Stat::DEF] = 2;
	m_stats[Stat::ATK] = 15;
	m_stats[Stat::MAXATK] = 20;
	m_stats[Stat::PM] = 5;
	m_stats[Stat::MAXPM] = 5;
	m_stats[Stat::PA] = 2;
	m_stats[Stat::MAXPA] = 2;
	m_icon = 'M';
	m_color = 4;		// cyan
}

void Mastiff::OnDeath(GameManager* gm)
{
	gm->GetPlayer()->SetStat(Stat::DEF, 1);
}

Ethereal::Ethereal()
{
	m_name = "Ethereal";	//Éthéré
	m_stats[Stat::HP] = 30;
	m_stats[Stat::MAXHP] = 30;
	m_stats[Stat::DEF] = 1;
	m_stats[Stat::ATK] = 5;
	m_stats[Stat::MAXATK] = 10;
	m_stats[Stat::PM] = 5;
	m_stats[Stat::MAXPM] = 5;
	m_stats[Stat::PA] = 1;
	m_stats[Stat::MAXPA] = 1;
	m_behaviour = Behaviour::Flee;
	m_icon = 'E';
	m_color = 3;		// Bleu clair
}

void Ethereal::OnDeath(GameManager* gm)
{
	Player* p = gm->GetPlayer();
	gm->GetPlayer()->SetStat(Stat::HP, p->GetStat(Stat::MAXHP) - p->GetStat(Stat::HP));
}

int Ethereal::TakeDamage(Entity* attacker)
{
	int rand = std::rand() % 100;
	if (rand > 50) return Entity::TakeDamage(attacker);
	return 0;
}

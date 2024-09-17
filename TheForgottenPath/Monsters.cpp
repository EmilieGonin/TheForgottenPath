#include "Monsters.h"

Golem::Golem()
{
	m_stats[Stat::ATK] = 5;
	m_stats[Stat::PM] = 0;
	m_stats[Stat::MAXPM] = 0;
	m_behaviour = Behaviour::Static;
	m_icon = 'G';
	m_color = 6;
	m_pos.first = 5;
	m_pos.second = 8;
}

void Golem::SpecialAttack() const
{
	//
}

Reaper::Reaper() // Faucheur
{
	m_stats[Stat::ATK] = 10;
	m_icon = 'F';
	m_color = 7;
	m_pos.first = 7;
	m_pos.second = 7;
}

void Reaper::SpecialAttack() const
{
	//
}

Wraith::Wraith() // Spectre
{
	m_stats[Stat::ATK] = 1;
	m_behaviour = Behaviour::Flee;
	m_icon = 'S';
	m_color = 3;
	m_pos.first = 8;
	m_pos.second = 2;
}

void Wraith::SpecialAttack() const
{
	//
}
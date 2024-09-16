#include "Reaper.h"

Reaper::Reaper() // Faucheur
{
	m_stats[Stat::ATK] = 10;
	m_icon = 'F';
	m_pos.first = 7;
	m_pos.second = 7;
}

void Reaper::SpecialAttack() const
{
	//
}
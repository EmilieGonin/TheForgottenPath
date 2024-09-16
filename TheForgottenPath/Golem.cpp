#include "Golem.h"

Golem::Golem()
{
	m_stats[Stat::ATK] = 5;
	m_icon = 'G';
	m_pos.first = 5;
	m_pos.second = 8;
}

void Golem::SpecialAttack() const
{
	//
}
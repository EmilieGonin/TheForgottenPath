#include "Monster.h"

Monster::Monster()
{
	m_stats[Stat::HP] = 50;
}

void Monster::SpecialAttack() const { }
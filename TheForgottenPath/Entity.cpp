#include "Entity.h"

Entity::Entity()
{
	m_stats[Stat::PA] = 5;
	m_stats[Stat::PM] = 0;
	m_icon = ' ';
}

float Entity::GetStat(Stat stat)
{
	return m_stats[stat];
}

char Entity::GetIcon() const
{
	return m_icon;
}

pair<int, int> Entity::GetPos()
{
	return m_pos;
}
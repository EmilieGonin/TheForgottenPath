#include "Entity.h"

Entity::Entity()
{
	m_stats[Stat::PA] = 5;
	m_stats[Stat::PM] = 0;
	m_icon = ' ';
}

inline float Entity::GetStat(Stat stat)
{
	return m_stats[stat];
}

inline char Entity::GetIcon()
{
	return m_icon;
}

pair<int, int> Entity::GetPos()
{
	return m_pos;
}
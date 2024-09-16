#include "Entity.h"

Entity::Entity()
{
	m_stats[Stat::PA] = 5;
	m_stats[Stat::PM] = 0;
}

inline float Entity::stat(Stat stat)
{
	return m_stats[stat];
}

inline char Entity::icon()
{
	return m_icon;
}
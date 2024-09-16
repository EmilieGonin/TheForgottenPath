#include "Entity.h"

inline float Entity::stat(Stat stat)
{
	return m_stats[stat];
}

inline char Entity::icon()
{
	return m_icon;
}
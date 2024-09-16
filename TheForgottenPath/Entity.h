#pragma once

#include <map>

enum class Stat
{
	HP,
	ATK,
	DEF,
	PA,		// Points d'action
	PM		// Points de d�placement
};

class Entity
{
public:
	Entity();

	float GetStat(Stat);
	char GetIcon();

protected:
	std::map<Stat, float> m_stats;
	char m_icon;
};
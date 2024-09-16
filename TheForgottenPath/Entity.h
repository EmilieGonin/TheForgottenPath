#pragma once

#include <map>

enum class Stat
{
	HP,
	ATK,
	DEF,
	PA,		// Points d'action
	PM		// Points de déplacement
};

class Entity
{
public:
	Entity();

	float stat(Stat);
	char icon();

protected:
	std::map<Stat, float> m_stats;
	char m_icon;
};
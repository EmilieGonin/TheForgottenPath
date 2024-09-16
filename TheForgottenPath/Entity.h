#pragma once

#include <map>

using std::pair;

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

	float GetStat(Stat);
	char GetIcon() const;

	pair<int, int> GetPos();

protected:
	std::map<Stat, float> m_stats;
	char m_icon;

	pair<int, int> m_pos;

};
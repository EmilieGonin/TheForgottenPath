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
	int GetColor() const;

	pair<int, int> GetPos();

	std::map<Stat, float> GetStats();

protected:
	std::map<Stat, float> m_stats;
	char m_icon;
	int m_color;

	pair<int, int> m_pos;

};
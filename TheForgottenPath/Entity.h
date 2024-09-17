#pragma once

#include <map>

using std::pair;

enum class Stat
{
	HP,
	ATK,
	DEF,
	PA,		// Points d'action
	PM,		// Points de déplacement
	MAXHP,
	MAXPA,
	MAXPM
};

enum class Behaviour
{
	Follow,
	Static,
	Flee
};

class Entity
{
public:
	Entity();

	std::map<Stat, float> GetStats() const { return m_stats; }
	float GetStat(Stat stat) { return m_stats[stat]; }
	char GetIcon() const { return m_icon; }
	int GetColor() const { return m_color; }
	Behaviour GetBehaviour() const { return m_behaviour; }
	pair<int, int> GetPos() const { return m_pos; }

	bool IsDead();
	bool CanMove();
	void Move(int, int);
	void OnEndTurn();
	void StopTurnEarly();
	void TakeDamage(int damage);

	virtual ~Entity() { }

protected:
	std::map<Stat, float> m_stats;
	char m_icon;
	int m_color;
	Behaviour m_behaviour;
	pair<int, int> m_pos;
};
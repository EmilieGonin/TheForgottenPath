#pragma once

#include <map>
#include <cstdlib>  // Pour std::rand() et std::srand()
#include <ctime>    // Pour std::time()

using std::pair;
using std::rand;

enum class Stat
{
	HP,
	ATK,
	MAXATK,
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

enum class Direction
{
	Up,
	Down,
	Right,
	Left,
	None
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

	bool IsDead() { return m_stats[Stat::HP] <= 0; }
	bool HasEnoughPM() { return m_stats[Stat::PM] > 0; }

	void Move(int, int);
	virtual void OnEndTurn();
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
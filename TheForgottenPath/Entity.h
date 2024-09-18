#pragma once

#include <map>
#include <cstdlib>  // Pour std::rand() et std::srand()
#include <ctime>    // Pour std::time()
#include <string>

using std::pair;
using std::rand;
using std::string;
using std::map;

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

	map<Stat, float> GetStats() const { return m_stats; }
	float GetStat(Stat stat) { return m_stats[stat]; }
	char GetIcon() const { return m_icon; }
	int GetColor() const { return m_color; }
	string GetName() const { return m_name; }
	Behaviour GetBehaviour() const { return m_behaviour; }
	pair<int, int> GetPos() const { return m_pos; }

	void SetPos(pair<int, int>);

	bool IsDead() { return m_stats[Stat::HP] <= 0; }
	bool HasEnoughPM() { return m_stats[Stat::PM] > 0; }

	void Move(int, int);
	void StopTurnEarly();
	virtual void OnEndTurn();
	virtual int TakeDamage(int damage);

	virtual ~Entity() { }

protected:
	map<Stat, float> m_stats;
	char m_icon;
	int m_color;
	Behaviour m_behaviour;
	pair<int, int> m_pos;
	string m_name;
};
#pragma once

class GameManager;

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
	DEF,
	PA,		// Points d'action
	PM,		// Points de déplacement
	MAXHP,
	MAXATK,
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

	void SetStat(Stat stat, int amount);
	void SetPos(pair<int, int>);

	bool IsDead() { return m_stats[Stat::HP] <= 0; }
	virtual bool HasEnoughPM() { return m_stats[Stat::PM] > 0; }
	bool HasEnoughPA() { return m_stats[Stat::PA] > 0; }

	void Move(int, int);
	void StopMovementEarly();
	void StopActionEarly();
	virtual void OnEndTurn();
	virtual void OnDeath(GameManager* gm);
	virtual int TakeDamage(Entity* attacker);

	void Despawn();

	virtual ~Entity() { }

protected:
	map<Stat, float> m_stats;
	char m_icon;
	int m_color;
	Behaviour m_behaviour;
	pair<int, int> m_pos;
	string m_name;
};
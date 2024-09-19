#pragma once
#include <string>

class Player;

using std::pair;
using std::string;

class Skill
{
public:
	virtual ~Skill() {}

	virtual void Use();
	virtual void Cancel();

	string GetCooldown() const { return std::to_string(m_cooldown.first); }
	string GetName() const { return m_name; }
	char GetKey() const { return m_key; }

	bool IsReady() const { return m_cooldown.first == 0; }
	bool IsFinish() const { return m_activeCooldown.first == 0; }
	bool IsActive() const { return m_activeCooldown.first > 0; }

	void Tick();

protected:
	Player* m_player;

	pair<int, int> m_activeCooldown;
	pair<int, int> m_cooldown;
	std::string m_name;
	char m_key;
};
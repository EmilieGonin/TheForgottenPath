#pragma once
#include <string>

class Player;

using std::pair;

class Skill
{
public:
	virtual ~Skill() {}

	virtual void Use();
	virtual void Cancel();

	bool IsReady() const { return m_cooldown.first == 0; }
	bool IsFinish() const { return m_activeCooldown.first == 0; }
	bool IsActive() const { return m_activeCooldown.first > 0; }

	void Tick();

protected:
	Player* m_player;

	pair<int, int> m_activeCooldown;
	pair<int, int> m_cooldown;
};
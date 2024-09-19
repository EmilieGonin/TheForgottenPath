#pragma once

#include <stack>

#include "Entity.h"

#include "Skill.h"
#include "Skills.h"

class Player : public Entity
{
public:
	Player();

	Direction GetPreviousDirection() const { return m_previousDirections.top(); }
	bool HasPreviousDirections() { return !m_previousDirections.empty(); }
	void AddDirection(Direction d) { m_previousDirections.push(d); }

	bool HasEnoughPM() override { return m_stats[Stat::PM] >= 0; }

	void OnEndTurn() override;
	void Respawn();
	void CancelLastMove();

	map<Skill*, int> GetSkills() const { return m_skills; }

private:
	std::stack<Direction> m_previousDirections;
	
	map<Skill*, int> m_skills
	{
		{ new Shield(this), -1 },
		{ new Heal(this), -1 },
	};
};
#pragma once

#include "Entity.h"

#include "Skill.h"
#include "Skills.h"

class Player : public Entity
{
public:
	Player();

	Direction GetPreviousDirection() const { return m_previousDirection; }
	void SetPreviousDirection(Direction d);

	void OnEndTurn() override;
	void Respawn();
	void CancelLastMove();

	map<Skill*, int> GetSkills() const { return m_skills; }

private:
	Direction m_previousDirection;
	map<Skill*, int> m_skills
	{
		{ new Shield(this), -1 },
		{ new Heal(this), -1 },
	};
};
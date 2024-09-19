#include "Skill.h"

void Skill::Use()
{
	m_cooldown.first = m_cooldown.second;
	m_activeCooldown.first = m_activeCooldown.second;
}

void Skill::Cancel()
{
}

void Skill::Tick()
{
	if (IsActive())
	{
		m_activeCooldown.first--;
	}
	else if (IsFinish())
	{
		Cancel();
		m_activeCooldown.first = -1;
	}
	else if (IsReady())
	{
		//console render
	}
	else if (!IsReady())
	{
		m_cooldown.first--;
	}
}

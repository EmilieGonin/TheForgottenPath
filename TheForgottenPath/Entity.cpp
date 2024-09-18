#include "Entity.h"

Entity::Entity()
{
	m_icon = ' ';
	m_color = 7;
	m_behaviour = Behaviour::Follow;
}

void Entity::Move(int x, int y)
{
	m_stats[Stat::PM]--;
	m_pos.first = x;
	m_pos.second = y;
}

void Entity::OnEndTurn()
{
	m_stats[Stat::PM] = m_stats[Stat::MAXPM];
}

void Entity::StopTurnEarly()
{
	m_stats[Stat::PM] = 0;
}

void Entity::TakeDamage(int damage)
{
	m_stats[Stat::HP] -= damage;
	if (m_stats[Stat::HP] < 0) m_stats[Stat::HP] = 0;
}
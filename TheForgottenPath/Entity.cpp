#include "Entity.h"

Entity::Entity()
	:m_color(7) //Blanc
{
	m_stats[Stat::PA] = 5;
	m_stats[Stat::MAXPA] = 5;
	m_stats[Stat::PM] = 3;
	m_stats[Stat::MAXPM] = 3;
	m_icon = ' ';
}

float Entity::GetStat(Stat stat)
{
	return m_stats[stat];
}

char Entity::GetIcon() const
{
	return m_icon;
}

int Entity::GetColor() const
{
	return m_color;
}

pair<int, int> Entity::GetPos()
{
	return m_pos;
}

std::map<Stat, float> Entity::GetStats()
{
	return m_stats;
}

bool Entity::CanMove()
{
	return m_stats[Stat::PM] > 0;
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
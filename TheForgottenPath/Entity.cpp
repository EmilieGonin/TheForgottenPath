#include "Entity.h"

Entity::Entity()
{
	m_name = "Unknow name";
	m_icon = ' ';
	m_color = 7;
	m_behaviour = Behaviour::Follow;
}

void Entity::SetPos(pair<int, int> pos)
{
	m_pos = pos;
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
	m_stats[Stat::PA] = m_stats[Stat::MAXPA];
}

void Entity::OnDeath(GameManager* gm) { }

void Entity::StopMovementEarly()
{
	m_stats[Stat::PM] = 0;
}

void Entity::StopActionEarly()
{
	m_stats[Stat::PA] = 0;
}

int Entity::TakeDamage(Entity* attacker)
{
	int min = static_cast<int>(attacker->GetStat(Stat::ATK));
	int max = static_cast<int>(attacker->GetStat(Stat::MAXATK));
	int damage = min + std::rand() % (max - min + 1);
	damage -= m_stats[Stat::DEF];
	m_stats[Stat::HP] -= damage;
	if (m_stats[Stat::HP] < 0) m_stats[Stat::HP] = 0;
	return damage;
}
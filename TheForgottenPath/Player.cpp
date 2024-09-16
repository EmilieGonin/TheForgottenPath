#include "Player.h"

Player::Player()
{
	m_stats[Stat::HP] = 50;
	m_stats[Stat::ATK] = 5;
	m_stats[Stat::PM] = 3;
	m_icon = '@';
	m_pos.first = 2;
	m_pos.second = 2;
}

pair<int, int> Player::GetPos()
{
	return m_pos;
}
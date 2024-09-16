#include "Player.h"

Player::Player()
{
	m_stats[Stat::HP] = 50;
	m_stats[Stat::ATK] = 5;
	m_stats[Stat::PM] = 3;
	m_icon = '@';
	m_pos.first = 5;
	m_pos.second = 2;
}

bool Player::CanMove()
{
	return m_stats[Stat::PM] > 0;
}

void Player::Move()
{
	m_stats[Stat::PM]--;
}
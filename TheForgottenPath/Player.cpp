#include "Player.h"

Player::Player()
{
	m_stats[Stat::HP] = 50;
	m_stats[Stat::MAXHP] = 50;
	m_stats[Stat::ATK] = 5;
	m_stats[Stat::PM] = 3;
	m_stats[Stat::MAXPM] = 3;
	m_icon = '@';
	m_color = 5;
	m_pos.first = 5;
	m_pos.second = 2;
}
#include "Player.h"

Player::Player()
{
	m_stats[Stat::HP] = 50;
	m_stats[Stat::ATK] = 5;
	m_stats[Stat::PM] = 3;
	m_icon = '@';
}
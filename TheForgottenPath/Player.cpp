#include "Player.h"

Player::Player()
{
	m_name = "Player";
	m_icon = '@';
	m_color = 2;	// Vert clair

	m_stats[Stat::MAXHP] = 150;
	m_stats[Stat::HP] = m_stats[Stat::MAXHP];
	m_stats[Stat::DEF] = 5;
	m_stats[Stat::ATK] = 15;
	m_stats[Stat::MAXATK] = 20;
	m_stats[Stat::MAXPM] = 3;
	m_stats[Stat::MAXPA] = 2;

	Respawn();
}

void Player::OnEndTurn()
{
	Entity::OnEndTurn();
	while (!m_previousDirections.empty()) m_previousDirections.pop();
}

void Player::Respawn()
{
	m_stats[Stat::PM] = m_stats[Stat::MAXPM];
	m_stats[Stat::PA] = m_stats[Stat::MAXPA];
}

void Player::CancelLastMove()
{
	m_stats[Stat::PM] += 2;
	m_previousDirections.pop();
}
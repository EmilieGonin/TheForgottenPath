#include "Player.h"

Player::Player()
{
	m_name = "Player";
	m_icon = '@';
	m_color = 2;	// Vert clair
	Respawn();

	m_previousDirection = Direction::None;
}

void Player::SetPreviousDirection(Direction d)
{
	m_previousDirection = d;
}

void Player::OnEndTurn()
{
	Entity::OnEndTurn();
	m_previousDirection = Direction::None;
}

void Player::Respawn()
{
	m_stats[Stat::HP] = 150;
	m_stats[Stat::MAXHP] = 150;
	m_stats[Stat::DEF] = 5;
	m_stats[Stat::ATK] = 15;
	m_stats[Stat::MAXATK] = 20;
	m_stats[Stat::PM] = 3;
	m_stats[Stat::MAXPM] = 3;
	m_stats[Stat::PA] = 2;
	m_stats[Stat::MAXPA] = 2;
}

void Player::CancelLastMove()
{
	m_stats[Stat::PM] += 2;
	m_previousDirection = Direction::None;
}
#pragma once

#include <stack>

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	Direction GetPreviousDirection() const { return m_previousDirections.top(); }
	bool HasPreviousDirections() { return !m_previousDirections.empty(); }
	void AddDirection(Direction d) { m_previousDirections.push(d); }
	void RemoveDirection() { m_previousDirections.pop(); }

	bool HasEnoughPM() override { return m_stats[Stat::PM] >= 0; }

	void OnEndTurn() override;
	void Respawn();
	void CancelLastMove();

private:
	std::stack<Direction> m_previousDirections;
};
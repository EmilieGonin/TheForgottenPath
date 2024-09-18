#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	Direction GetPreviousDirection() const { return m_previousDirection; }
	void SetPreviousDirection(Direction d);

	void OnEndTurn() override;
	void Respawn();
	void CancelLastMove();

private:
	Direction m_previousDirection;
};
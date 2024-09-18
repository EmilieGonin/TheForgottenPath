#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	Direction GetPreviousDirection() const { return m_previousDirection; }

	void OnEndTurn() override;

private:
	Direction m_previousDirection;
};
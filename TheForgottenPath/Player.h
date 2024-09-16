#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player();

	bool CanMove();
	void Move();
};
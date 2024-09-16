#pragma once

#include "Entity.h"

class Monster : public Entity
{
public:
	Monster();

	virtual void specialAttack() const = 0;
};
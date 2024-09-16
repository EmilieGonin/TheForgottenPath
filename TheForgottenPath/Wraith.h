#pragma once

#include "Monster.h"

class Wraith : public Monster
{
public:
	Wraith();

	void specialAttack() const override;
};
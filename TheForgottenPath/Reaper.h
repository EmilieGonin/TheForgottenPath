#pragma once

#include "Monster.h"

class Reaper : public Monster
{
public:
	Reaper();

	void specialAttack() const override;
};
#pragma once

#include "Monster.h"

class Reaper : public Monster
{
public:
	Reaper();

	void SpecialAttack() const override;
};
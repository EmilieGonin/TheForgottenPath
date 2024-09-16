#pragma once

#include "Monster.h"

class Golem : public Monster
{
public:
	Golem();

	void SpecialAttack() const override;
};
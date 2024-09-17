#pragma once

#include "Monster.h"

class Golem : public Monster
{
public:
	Golem();

	void SpecialAttack() const override;
};

class Reaper : public Monster
{
public:
	Reaper();

	void SpecialAttack() const override;
};

class Wraith : public Monster
{
public:
	Wraith();

	void SpecialAttack() const override;
};
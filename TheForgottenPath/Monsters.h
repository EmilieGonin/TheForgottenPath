#pragma once

#include "Monster.h"

class Golem : public Monster
{
public:
	Golem();

	int TakeDamage(Entity* attacker) override;
};

class Reaper : public Monster
{
public:
	Reaper();
};

class Wraith : public Monster
{
public:
	Wraith();
};
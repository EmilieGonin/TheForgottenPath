#pragma once

#include "Monster.h"

class Golem : public Monster
{
public:
	Golem();

	void OnDeath(GameManager* gm) override;
	int TakeDamage(Entity* attacker) override;
};

class Reaper : public Monster
{
public:
	Reaper();

	void OnDeath(GameManager* gm) override;
};

class Wraith : public Monster
{
public:
	Wraith();

	void OnDeath(GameManager* gm) override;
};

class Titan : public Monster
{
public:
	Titan();
};

class Mastiff : public Monster
{
public:
	Mastiff();

	void OnDeath(GameManager* gm) override;
};

class Ethereal : public Monster
{
public:
	Ethereal();

	void OnDeath(GameManager* gm) override;
	int TakeDamage(Entity* attacker) override;
};
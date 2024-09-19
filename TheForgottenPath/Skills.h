#pragma once

#include "Skill.h"

class Shield : public Skill
{
public:
	Shield(Player* p);
	void Use() override;
	void Cancel() override;
};

class Heal : public Skill
{
public:
	Heal(Player* p);
	void Use() override;
};


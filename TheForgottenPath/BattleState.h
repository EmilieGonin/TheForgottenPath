#pragma once
#include "Battle.h"

class Battle;

class BattleState
{
public:
	virtual void enter(Battle*) = 0;
	virtual void toggle(Battle*) = 0;
	virtual void exit(Battle*) = 0;
	virtual ~BattleState() {}
};
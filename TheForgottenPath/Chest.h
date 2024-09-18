#pragma once

#include <vector>
#include <string>

#include "Entity.h"
#include "GameManager.h"

class ConsoleRenderer;

class Chest
{
public:
	Chest();
	void Open(Entity* e, ConsoleRenderer* console);

private:
	Stat m_stat;
	int m_amount;

	Stat SetRandomStat();
};
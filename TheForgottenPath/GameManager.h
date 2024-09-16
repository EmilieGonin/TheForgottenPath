#pragma once

#include <vector>
#include <memory>

#include "Golem.h"
#include "Reaper.h"
#include "Wraith.h"

class GameManager
{
public:
	GameManager();

	Monster GetRandomMonster();
	std::vector<Monster> GetMonsters();

private:
	std::vector<Monster> m_monsters;
};
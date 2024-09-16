#pragma once

#include <vector>
#include <memory>

#include "Player.h"
#include "Golem.h"
#include "Reaper.h"
#include "Wraith.h"

class GameManager
{
public:
	GameManager();

	Player* GetPlayer();
	Monster GetRandomMonster();
	std::vector<Monster> GetMonsters();

private:
	Player* m_player;
	std::vector<Monster> m_monsters;
};
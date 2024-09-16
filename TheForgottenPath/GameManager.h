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
	static GameManager* GetInstance();

	Player* GetPlayer();
	Monster GetRandomMonster();
	std::vector<Monster> GetMonsters();

private:
	Player* m_player;
	std::vector<Monster> m_monsters;
	static GameManager* m_instance;
};
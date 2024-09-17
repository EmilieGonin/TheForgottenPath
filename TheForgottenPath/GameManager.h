#pragma once

#include <vector>

#include "Player.h"
#include "Monsters.h"

class GameManager
{
public:
	GameManager();
	static GameManager* GetInstance();

	Player* GetPlayer();
	Monster GetRandomMonster();
	std::vector<Monster> GetMonsters();
	bool GameIsOver();

private:
	static GameManager* m_instance;
	Player* m_player;
	std::vector<Monster> m_monsters;
	int m_levelsRemaining;
};
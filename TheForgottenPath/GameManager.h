#pragma once

#include <vector>

#include "Player.h"
#include "Monsters.h"

class GameManager
{
public:
	GameManager();
	static GameManager* GetInstance();

	Player* GetPlayer() const { return m_player; }
	std::vector<Monster*> GetMonsters() const { return m_monsters; }
	int GetLevelsRemaning() const { return m_levelsRemaining; }

	bool GameIsOver() const { return m_levelsRemaining <= 0; }

	Monster* GetRandomMonster();
	void StartNewGame();
	void StartNewBattle();
	void WinBattle();

private:
	static GameManager* m_instance;
	Player* m_player;
	std::vector<Monster*> m_monsters;
	int m_levelsRemaining;
};
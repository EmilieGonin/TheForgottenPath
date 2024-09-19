#pragma once

#include <vector>

#include "Player.h"
#include "Monsters.h"

#define TRAP_DAMAGE 15

using std::vector;

class GameManager
{
public:
	GameManager();
	static GameManager* GetInstance();

	Player* GetPlayer() const { return m_player; }
	vector<Monster*> GetMonsters() const { return m_monsters; }
	int GetCurrentLevel() const { return m_currentLevel; }
	int GetLevelsRemaining() const { return m_levelsRemaining; }

	bool GameIsOver() const { return m_levelsRemaining <= 0; }

	Monster* GetRandomMonster();
	void StartNewGame();
	void StartNewBattle();
	void WinBattle();

private:
	static GameManager* m_instance;
	Player* m_player;
	vector<Monster*> m_monsters;
	int m_currentLevel;
	int m_levelsRemaining;
};
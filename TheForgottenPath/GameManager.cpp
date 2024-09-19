#include "GameManager.h"
#include "LevelEditor.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
{
	StartNewGame();
}

GameManager* GameManager::GetInstance()
{
	if (m_instance == nullptr) m_instance = new GameManager();
	return m_instance;
}

Monster* GameManager::GetRandomMonster()
{
    int randomChoice = std::rand() % m_monsters.size();
	return m_monsters[randomChoice];
}

void GameManager::StartNewGame()
{
	LevelEditor* l = new LevelEditor();

	m_player = new Player();
	m_currentLevel = 0;
	m_levelsRemaining = l->GetLevelNumber();
	StartNewBattle();
}

void GameManager::StartNewBattle()
{
	m_player->Respawn();

	m_monsters.clear();
	m_monsters.push_back(new Golem());
	m_monsters.push_back(new Reaper());
	m_monsters.push_back(new Wraith());
	m_monsters.push_back(new Titan());
	m_monsters.push_back(new Mastiff());
	m_monsters.push_back(new Ethereal());
}

void GameManager::WinBattle()
{
	m_levelsRemaining--;
	m_currentLevel++;
}
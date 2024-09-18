#include "GameManager.h"

#include <cstdlib>
#include <ctime>

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
	m_player = new Player();
	m_levelsRemaining = 3;
	StartNewBattle();
}

void GameManager::StartNewBattle()
{
	m_monsters.clear();
	m_monsters.push_back(new Golem());
	m_monsters.push_back(new Reaper());
	m_monsters.push_back(new Wraith());
}

void GameManager::WinBattle()
{
	m_levelsRemaining--;
}
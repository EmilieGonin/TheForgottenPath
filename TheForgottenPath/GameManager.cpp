#include "GameManager.h"

#include <cstdlib>
#include <ctime>

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
{
	m_player = new Player();

	m_monsters.push_back(new Golem());
	m_monsters.push_back(new Reaper());
	m_monsters.push_back(new Wraith());

	m_levelsRemaining = 3;
}

GameManager* GameManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GameManager();
	}

	return m_instance;
}

Player* GameManager::GetPlayer()
{
	return m_player;
}

Monster* GameManager::GetRandomMonster()
{
    std::srand(static_cast<unsigned>(std::time(0)));
    int randomChoice = std::rand() % m_monsters.size();

	return m_monsters[randomChoice];
}

std::vector<Monster*> GameManager::GetMonsters()
{
	return m_monsters;
}

bool GameManager::GameIsOver()
{
	return m_levelsRemaining == 0;
}
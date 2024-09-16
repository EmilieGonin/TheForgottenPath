#include "GameManager.h"
#include <cstdlib>
#include <ctime>

GameManager::GameManager()
{
	m_monsters.push_back(Golem());
	m_monsters.push_back(Reaper());
	m_monsters.push_back(Wraith());
}

Monster GameManager::GetRandomMonster()
{
    std::srand(static_cast<unsigned>(std::time(0)));
    int randomChoice = std::rand() % m_monsters.size();

	return m_monsters[randomChoice];
}

std::vector<Monster> GameManager::GetMonsters()
{
	return std::vector<Monster>();
}
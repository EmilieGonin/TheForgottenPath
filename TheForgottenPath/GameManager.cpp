#include "GameManager.h"

#include <cstdlib>
#include <ctime>

GameManager::GameManager()
{
	m_player = new Player();

	m_monsters.push_back(Golem());
	m_monsters.push_back(Reaper());
	m_monsters.push_back(Wraith());
}

Player* GameManager::GetPlayer()
{
	return m_player;
}

Monster GameManager::GetRandomMonster()
{
    std::srand(static_cast<unsigned>(std::time(0)));
    int randomChoice = std::rand() % m_monsters.size();

	return m_monsters[randomChoice];
}

std::vector<Monster> GameManager::GetMonsters()
{
	return m_monsters;
}
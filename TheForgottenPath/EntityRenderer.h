#pragma once

#include <windows.h>

#include "GameManager.h"
#include "Player.h"
#include "Monster.h"

class ConsoleRenderer;

class EntityRenderer
{
public:
	EntityRenderer(ConsoleRenderer* console);

	void MovePlayer();
    bool MoveMonster(Entity*);
    bool MoveEntity(Direction, Entity*);
	void RemoveEntity(Entity*);

    Entity* GetCloseEntity(Entity*);
	std::pair<int, int> GetNextDestination(Direction d, std::pair<int, int> pos);

	Direction GetPathToPlayer(std::pair<int, int> monsterPos, bool reverse);
	Direction GetPathAwayFromPlayer(std::pair<int, int> monsterPos, bool reverse);

private:
    std::map<int, Direction> m_keyDirections
    {
        { VK_UP, Direction::Up },
        { VK_DOWN, Direction::Down },
        { VK_LEFT, Direction::Left },
        { VK_RIGHT, Direction::Right }
    };

    std::map<Direction, Direction> m_reverseDirections
    {
        { Direction::Up, Direction::Down },
        { Direction::Down, Direction::Up },
        { Direction::Left, Direction::Right },
        { Direction::Right, Direction::Left }
    };

    std::map<int, bool> m_keyStates;

    GameManager* m_gm;
    ConsoleRenderer* m_consoleRenderer;
};
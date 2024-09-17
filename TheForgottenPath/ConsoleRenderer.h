#pragma once

#include "Player.h"
#include "Monster.h"
#include "GameManager.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <windows.h>

using std::vector;
using std::cout;

enum class Direction
{
    Up,
    Down,
    Right,
    Left,
    None
};

class ConsoleRenderer 
{
public:
    ConsoleRenderer();

    void Display();
    void PlayerController();

private:
    static const int kGridWidth = 15;
    static const int kGridHeight = 15;

    static const char kEmpty = '.';
    static const char kWall = '#';
    static const char kValidMove = '*';

    vector<vector<char>> m_grid;

    std::map<int, Direction> m_keyDirections{
        { VK_UP, Direction::Up },
        { VK_DOWN, Direction::Down },
        { VK_LEFT, Direction::Left },
        { VK_RIGHT, Direction::Right }
    };

    std::map<int, bool> m_keyStates;

    std::map<Stat, std::string> m_statsTitle {
    { Stat::HP, "HP" },
    { Stat::ATK, "ATK" },
    { Stat::DEF, "DEF" },
    { Stat::PA, "PA" },
    { Stat::PM, "PM" }
    };

    void InitWalls();
    void SpawnMonsters();
    void SpawnPlayer();

    void MoveEntity(Direction, Entity*);

    void RenderPlayerStats();
    void RenderMonsterStats();
    void RenderAvailableActions();
    void RenderGameMessage();

    void ClearConsole();

    GameManager* m_gm;
};
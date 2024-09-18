﻿#pragma once

#include "Player.h"
#include "Monster.h"
#include "GameManager.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <cmath>

using std::vector;
using std::cout;

class ConsoleRenderer 
{
public:
    ConsoleRenderer();

    Entity* GetCloseEntity(Entity*);

    void Display();
    void PlayerController();
    bool MoveMonster(Entity*);

    void SetLog(std::string);

private:
    static const int kGridWidth = 15;
    static const int kGridHeight = 15;

    static const char kEmpty = '.';
    static const char kWall = '#';
    static const char kValidMove = '*';

    const int kColorValidMove = 14; // Jaune clair
    const int kColorDefault = 7; // Couleur par défaut (gris clair)

    std::string m_log;

    vector<vector<char>> m_grid;

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

    Direction GetPathToPlayer(std::pair<int, int> monsterPos, bool reverse);
    Direction GetPathAwayFromPlayer(std::pair<int, int> monsterPos, bool reverse);

    void DisplayValidMovementCells();
    void ResetValidMovementCells();

    bool MoveEntity(Direction, Entity*);
    std::pair<int, int> GetNextDestination(Direction d, std::pair<int, int> pos);

    void RenderEntityStats(Entity*);
    void RenderAvailableActions(Entity*);
    void RenderGameLog();

    void SetConsoleColor(int color);
    void ClearConsole();

    GameManager* m_gm;
};
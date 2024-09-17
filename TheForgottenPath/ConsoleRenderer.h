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

    //void MovementRange();
    Entity* GetCloseEntity(Entity*);

    void Display();
    void PlayerController();
    void MoveMonster(Entity*);

private:
    static const int kWidth = 15;
    static const int kHeight = 15;

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

    const std::map<Stat, std::string> m_statsTitle = {
    { Stat::HP, "HP" },
    { Stat::ATK, "ATK" },
    { Stat::DEF, "DEF" },
    { Stat::PA, "PA" },
    { Stat::PM, "PM" }
    };

    //cout << m_statsTitle[e.first] << " : " << e.second

    void InitWalls();
    void SpawnMonsters();
    void SpawnPlayer();

    Direction GetPathToPlayer(std::pair<int, int> monsterPos, bool reverse);
    void MoveEntity(Direction, Entity*);
    std::pair<int, int> GetNextDestination(Direction d, std::pair<int, int> pos);

    void RenderPlayerStats();
    void RenderMonsterStats();
    void RenderAvailableActions();
    void RenderGameMessage();

    void ClearConsole();

    GameManager* m_gm;
};
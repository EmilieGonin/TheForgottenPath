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

    void MovementRange();

    void Display() const;
    void PlayerController();


private:
    static const int kWidth = 15;
    static const int kHeight = 15;

    static const char kEmpty = '.';
    static const char kWall = '#';
    static const char kValidMove = '*';

    vector<vector<char>> m_grid;

    void InitWalls();
    void SpawnMonsters();
    void SpawnPlayer();

    void MoveEntity(Direction, Entity*);

    void RenderPlayerStats();
    void RenderMonsterStats();
    void RenderAvailableActions();
    void RenderGameMessage();

    GameManager* m_gm;
};
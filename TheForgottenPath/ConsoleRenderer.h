#pragma once

#include <vector>
#include "Player.h"
#include "Monster.h"
#include "GameManager.h"

using std::vector;

class ConsoleRenderer 
{
public:
    ConsoleRenderer();

    void Display() const;
    void MovementRange();

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
    void RenderPlayerStats();
    void RenderMonsterStats();
    void RenderAvailableActions();
    void RenderGameMessage();

    GameManager* m_gm;
};
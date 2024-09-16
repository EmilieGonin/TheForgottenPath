#pragma once

#include <vector>
#include "Player.h"
#include "Monster.h"
#include "GameManager.h"

using std::vector;

class Dungeon 
{
public:
    Dungeon(Player*);

    void Display() const;
    void MarkValidMoves(int hero_x, int hero_y);

private:
    static const int kWidth = 15;
    static const int kHeight = 15;

    static const char kEmpty = '.';
    static const char kWall = '#';
    static const char kValidMove = '*';

    vector<vector<char>> m_grid;

    void Initialize();
    void PlaceWalls();
    void PlaceMonsters();
};
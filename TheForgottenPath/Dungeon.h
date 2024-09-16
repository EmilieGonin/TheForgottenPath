#pragma once

#include <vector>

using std::vector;

class Dungeon 
{
public:
    Dungeon();

    void Display() const;
    void MarkValidMoves(int hero_x, int hero_y);

private:
    static const int kWidth = 15;
    static const int kHeight = 15;

    static const char kEmpty = '.';
    static const char kHero = '@';
    static const char kGolem = 'G';
    static const char kSpectre = 'S';
    static const char kFaucheur = 'F';
    static const char kWall = '#';
    static const char kValidMove = '*';

    vector<vector<char>> m_grid;
    int m_hero_x_;
    int m_hero_y_;

    void Initialize();
    void PlaceWalls();
    void PlaceMonsters();
};
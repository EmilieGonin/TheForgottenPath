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
    static const int kWidth = 105;
    static const int kHeight = 40;

    static const char kEmpty = '.';
    static const char kHero = '@';
    static const char kGolem = 'G';
    static const char kSpectre = 'S';
    static const char kFaucheur = 'F';
    static const char kWall = '#';
    static const char kValidMove = '*';

    vector<vector<char>> grid;
    int hero_x_;
    int hero_y_;

    void Initialize();
    void PlaceWalls();
    void PlaceMonsters();
};
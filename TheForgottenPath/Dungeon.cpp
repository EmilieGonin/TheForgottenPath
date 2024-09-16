#include "dungeon.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <vector>

using std::fill;
using std::cout;
using std::endl;
using std::vector;

//enum ConsoleColor 
//{
//    DEFAULT_COLOR = 7,  // Couleur par défaut (blanc sur noir)
//    VALID_MOVE_COLOR = 10, // Vert 
//    GOLEM_COLOR = 14,    // Jaune
//    WRAITH_SPECTRE_COLOR = 11,  // Bleu clair 
//    REAPER_COLOR = 12  // Rouge 
//};

//void SetConsoleColor(ConsoleColor color) 
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, color);
//}

Dungeon::Dungeon(Player* player) : m_grid(kHeight, vector<char>(kWidth, kEmpty)) 
{
    InitWalls();
    SpawnMonsters();
    //SpawnPlayer();
    Display();
}

void Dungeon::InitWalls()
{
    for (int row = 0; row < kHeight; ++row)
    {
        for (int col = 0; col < kWidth; ++col)
        {
            if (row == 0 || row == kHeight - 1 || col == 0 || col == kWidth - 1)
            {
                m_grid[row][col] = kWall;
            }
        }
    }
}

void Dungeon::SpawnMonsters() 
{
    GameManager gm;

    for (Monster m : gm.GetMonsters())
    {
        m_grid[m.GetPos().first][m.GetPos().second] = m.GetIcon();
    }
}

void Dungeon::SpawnPlayer(Player* player)
{
    m_grid[player->GetPos().first][player->GetPos().second] = player->GetIcon();
}

void Dungeon::Display() const
{
    for (const auto& row : m_grid)
    {
        for (char cell : row)
        {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

// Marquer les cases de déplacement valides autour du héros
void Dungeon::MarkValidMoves(int hero_x, int hero_y) 
{
    const int range = 2;
    for (int dx = -range; dx <= range; ++dx) 
    {
        for (int dy = -range; dy <= range; ++dy) 
        {
            int new_x = hero_x + dx;
            int new_y = hero_y + dy;
            if (new_x >= 0 && new_x < kHeight && new_y >= 0 && new_y < kWidth && m_grid[new_x][new_y] == kEmpty) 
            {
                m_grid[new_x][new_y] = kValidMove;
            }
        }
    }
}

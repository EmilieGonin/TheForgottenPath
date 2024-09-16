#include "dungeon.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <vector>

using std::fill;
using std::cout;
using std::endl;
using std::vector;

enum ConsoleColor 
{
    DEFAULT_COLOR = 7,  // Couleur par défaut (blanc sur noir)
    VALID_MOVE_COLOR = 10, // Vert 
    GOLEM_COLOR = 14,    // Jaune
    WRAITH_SPECTRE_COLOR = 11,  // Bleu clair 
    REAPER_COLOR = 12  // Rouge 
};

void SetConsoleColor(ConsoleColor color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

Dungeon::Dungeon() : m_grid(kHeight, vector<char>(kWidth, kEmpty)), m_hero_x_(1), m_hero_y_(1) 
{
    Initialize();
    // Placement du héros dans la grille
    m_grid[m_hero_x_][m_hero_y_] = kHero;
}

void Dungeon::Initialize() 
{
    PlaceWalls();
    PlaceMonsters();
}

void Dungeon::PlaceWalls() 
{
    fill(m_grid[0].begin(), m_grid[0].end(), kWall);                       // Mur du haut
    fill(m_grid[kHeight - 1].begin(), m_grid[kHeight - 1].end(), kWall);   // Mur du bas
    for (int i = 0; i < kHeight; ++i) 
    {
        m_grid[i][0] = kWall;                                              // Mur gauche
        m_grid[i][kWidth - 1] = kWall;                                     // Mur droit
    }
}

void Dungeon::PlaceMonsters() 
{
    m_grid[7][3] = kGolem;
    m_grid[5][5] = kSpectre;
    m_grid[7][7] = kFaucheur;
}

void Dungeon::Display() const 
{
    for (int row = 0; row < kHeight; ++row) 
    {
        for (int col = 0; col < kWidth; ++col) 
        {
            char cell = m_grid[row][col];
            switch (cell) 
            {
            case kHero:
                SetConsoleColor(DEFAULT_COLOR);
                cout << cell << ' ';
                break;
            case kGolem:
                SetConsoleColor(GOLEM_COLOR);
                cout << cell << ' ';
                SetConsoleColor(DEFAULT_COLOR);
                break;
            case kSpectre:
                SetConsoleColor(WRAITH_SPECTRE_COLOR);
                cout << cell << ' ';
                SetConsoleColor(DEFAULT_COLOR);
                break;
            case kFaucheur:
                SetConsoleColor(REAPER_COLOR);
                cout << cell << ' ';
                SetConsoleColor(DEFAULT_COLOR);
                break;
            case kValidMove:
                SetConsoleColor(VALID_MOVE_COLOR);
                cout << cell << ' ';
                SetConsoleColor(DEFAULT_COLOR);
                break;
            default:
                SetConsoleColor(DEFAULT_COLOR);
                cout << cell << ' ';
                break;
            }
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

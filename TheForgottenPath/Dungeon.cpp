#include "dungeon.h"
#include <iostream>
#include <algorithm>
#include <windows.h>

using std::fill;
using std::cout;
using std::endl;

enum ConsoleColor 
{
    DEFAULT_COLOR = 7,  // Couleur par d�faut (blanc sur noir)
    VALID_MOVE_COLOR = 10, // Vert clair pour les d�placements valides lorsqu'activ�
};

// Change la couleur du texte dans la console
void SetConsoleColor(ConsoleColor color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

Dungeon::Dungeon() : m_grid(kHeight, vector<char>(kWidth, kEmpty)), m_hero_x_(1), m_hero_y_(1) 
{
    Initialize();
    // Placement du h�ros dans la grille
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
    m_grid[5][12] = kSpectre;
    m_grid[16][7] = kFaucheur;
}

void Dungeon::Display() const {
    for (int row = 0; row < kHeight; ++row) {
        for (int col = 0; col < kWidth; ++col) {
            char cell = m_grid[row][col];
            switch (cell) {
            case kValidMove:
                SetConsoleColor(VALID_MOVE_COLOR); // D�finit la couleur pour les cases de d�placement valide
                cout << cell << ' ';
                SetConsoleColor(DEFAULT_COLOR); // R�initialise la couleur par d�faut
                break;
            default:
                cout << cell << ' ';
                break;
            }
        }
        cout << endl;
    }
}


// Marquer les cases de d�placement valides autour du h�ros
void Dungeon::MarkValidMoves(int hero_x, int hero_y) {
    const int range = 2;
    for (int dx = -range; dx <= range; ++dx) {
        for (int dy = -range; dy <= range; ++dy) {
            int new_x = hero_x + dx;
            int new_y = hero_y + dy;
            if (new_x >= 0 && new_x < kHeight && new_y >= 0 && new_y < kWidth && m_grid[new_x][new_y] == kEmpty) {
                m_grid[new_x][new_y] = kValidMove;
            }
        }
    }
}

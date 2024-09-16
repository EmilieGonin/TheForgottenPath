#include "dungeon.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <vector>

using std::cout;

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

Dungeon::Dungeon() : m_grid(kHeight, std::vector<char>(kWidth, kEmpty)) 
{
    m_gm = GameManager::GetInstance();
    InitWalls();
    SpawnMonsters();
    SpawnPlayer();
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
    for (Monster m : m_gm->GetMonsters())
    {
        m_grid[m.GetPos().first][m.GetPos().second] = m.GetIcon();
    }
}

void Dungeon::SpawnPlayer()
{
    m_grid[m_gm->GetPlayer()->GetPos().first][m_gm->GetPlayer()->GetPos().second] = m_gm->GetPlayer()->GetIcon();
}

void Dungeon::RenderPlayerStats()
{
    for (std::pair<Stat, float> e : m_gm->GetPlayer()->GetStats())
    {
        e.first;
        //std::cout << e.first << ' ';
    }
}

void Dungeon::RenderMonsterStats()
{

}

void Dungeon::RenderAvailableActions()
{

}

void Dungeon::RenderGameMessage()
{

}

void Dungeon::Display() const
{
    // Récupérer la taille actuelle de la console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int console_width = 80; // Valeur par défaut
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculer les marges (espaces à gauche) pour centrer la grille
    int margin_left = (console_width - kWidth * 2) / 2; // *2 car chaque cellule est suivie d'un espace

    for (const auto& row : m_grid) {
        for (int i = 0; i < margin_left; ++i) {
            std::cout << ' ';
        }

        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

// Marquer les cases de déplacement valides autour du héros
void Dungeon::MovementRange() 
{
    const int range = 2;
    for (int dx = -range; dx <= range; ++dx) 
    {
        for (int dy = -range; dy <= range; ++dy) 
        {
            int new_x = m_gm->GetPlayer()->GetPos().first + dx;
            int new_y = m_gm->GetPlayer()->GetPos().second + dy;
            if (new_x >= 0 && new_x < kHeight && new_y >= 0 && new_y < kWidth && m_grid[new_x][new_y] == kEmpty) 
            {
                m_grid[new_x][new_y] = kValidMove;
            }
        }
    }
}

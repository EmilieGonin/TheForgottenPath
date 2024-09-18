#pragma once

#include <vector>
#include <map>

#include "GameManager.h"

class ConsoleRenderer;

#define GRID_WIDTH 15
#define GRID_HEIGHT 15

enum class CellType
{
    Empty,
    Wall,
    ValidMove,
    Obstacle,
    Chest
};

class GridRenderer
{
public:
    GridRenderer(ConsoleRenderer* console);

    std::vector<std::vector<char>>& GetGrid() { return m_grid; }
    std::map<CellType, std::pair<char, int>> GetCellIcons() const { return m_cellIcons; }

    bool IsMoveableCell(std::pair<int, int> coord);

    void InitWalls();
    void InitRandomObstacles(int);
    void InitRandomChests(int);
    void SpawnMonsters();
    void SpawnPlayer();

private:
    std::vector<std::vector<char>> m_grid;

    std::map<CellType, std::pair<char, int>> m_cellIcons // Icon & Color
    {
        { CellType::Empty, std::make_pair('.', 7) },        // Couleur par d�faut (gris clair)
        { CellType::Wall, std::make_pair('X', 7) },
        { CellType::ValidMove, std::make_pair('*', 14) },   // Jaune clair
        { CellType::Obstacle, std::make_pair('#', 8) },     // Gris fonc�
        { CellType::Chest, std::make_pair('=', 12) }        // Rouge clair
    };

    GameManager* m_gm;
    ConsoleRenderer* m_consoleRenderer;
};
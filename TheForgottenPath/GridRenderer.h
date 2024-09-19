#pragma once

#include <vector>
#include <map>

#include "GameManager.h"
#include "Chest.h"

using std::vector;
using std::map;

class ConsoleRenderer;

#define GRID_WIDTH 15
#define GRID_HEIGHT 15

enum class CellType
{
    Empty,
    Wall,
    ValidMove,
    Obstacle,
    Chest,
    Trap
};

class GridRenderer
{
public:
    GridRenderer(ConsoleRenderer* console);

    vector<vector<char>>& GetGrid() { return m_grid; }
    map<CellType, pair<char, int>> GetCellDatas() const { return m_cellDatas; }
    map<pair<int, int>, Chest*> GetChests() const { return m_chests; }

    bool IsBlockedCell(pair<int, int> coord);
    bool IsEntityIcon(char icon);

    void InitWalls();
    void InitRandomElement(int nb, CellType type);
    void SpawnMonsters();
    void SpawnPlayer();

private:

    const int NB_OBSTACLES = 20;    // Nombre d'obstacles
    const int NB_CHESTS = 3;        // Nombre de coffres
    const int NB_TRAPS = 5;         // Nombre de pièges

    vector<vector<char>> m_grid;

    map<CellType, pair<char, int>> m_cellDatas    // Icon & Color
    {
        { CellType::Empty, std::make_pair('.', 7) },        // Couleur par défaut (gris clair)
        { CellType::Wall, std::make_pair('X', 7) },
        { CellType::ValidMove, std::make_pair('*', 14) },   // Jaune clair
        { CellType::Obstacle, std::make_pair('#', 8) },     // Gris foncé
        { CellType::Chest, std::make_pair('=', 6) },        // Jaune foncé
        { CellType::Trap, std::make_pair('!', 12) }         // Rouge clair
    };

    map<pair<int, int>, Chest*> m_chests;

    GameManager* m_gm;
    ConsoleRenderer* m_consoleRenderer;
};
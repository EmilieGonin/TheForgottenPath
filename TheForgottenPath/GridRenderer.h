#pragma once

#include <vector>
#include <map>

#include "GameManager.h"
#include "Chest.h"
#include "LevelEditor.h"

using std::vector;
using std::map;

class ConsoleRenderer;

#define ICON_EMPTY '.'
#define ICON_WALL 'X'
#define ICON_VALID_MOVE '*'
#define ICON_OBSTACLE '#'
#define ICON_CHEST '='
#define ICON_TRAP '!'

#define COLOR_YELLOW_DARK 6
#define COLOR_GREY_LIGHT 7
#define COLOR_GREY_DARK 8
#define COLOR_RED_LIGHT 12
#define COLOR_YELLOW_LIGHT 14

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
    int GetGridWidth() const { return m_gridWidth; }
    int GetGridHeight() const { return m_gridHeight; }
    map<CellType, pair<char, int>> GetCellDatas() const { return m_cellDatas; }
    map<pair<int, int>, Chest*> GetChests() const { return m_chests; }

    bool IsBlockedCell(pair<int, int> coord);
    bool IsEntityIcon(char icon);

    void InitWalls();
    void InitRandomElement(int nb, CellType type);
    void SpawnMonsters();
    void SpawnPlayer();

private:
    int m_gridWidth;
    int m_gridHeight;

    vector<vector<char>> m_grid;

    map<CellType, pair<char, int>> m_cellDatas    // Icon & Color
    {
        { CellType::Empty, std::make_pair(ICON_EMPTY, COLOR_GREY_LIGHT) },              // Icone et couleur des cases vides (Couleur par défaut (gris clair))
        { CellType::Wall, std::make_pair(ICON_WALL, COLOR_GREY_LIGHT) },                // Icone et couleur des murs
        { CellType::ValidMove, std::make_pair(ICON_VALID_MOVE, COLOR_YELLOW_LIGHT) },   // Icone et couleur des cases de mouvement valides (Jaune clair)
        { CellType::Obstacle, std::make_pair(ICON_OBSTACLE, COLOR_GREY_DARK) },         // Icone et couleur des obstacles (Gris foncé)
        { CellType::Chest, std::make_pair(ICON_CHEST, COLOR_YELLOW_DARK) },             // Icone et couleur des coffres (Jaune foncé)
        { CellType::Trap, std::make_pair(ICON_TRAP, COLOR_RED_LIGHT) }                  // Icone et couleur des pièges (Rouge clair)
    };

    map<pair<int, int>, Chest*> m_chests;

    GameManager* m_gm;
    ConsoleRenderer* m_consoleRenderer;
    LevelEditor* m_levelEditor;
};
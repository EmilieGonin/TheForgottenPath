#pragma once

#include "EntityRenderer.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cout;

enum class CellType
{
    Empty,
    Wall,
    ValidMove,
    Obstacle,
    Chest
};

class ConsoleRenderer 
{
public:
    ConsoleRenderer();

    void Display();

    void SetLog(std::string);

    // Entity Renderer
    void PlayerController() { m_entityRenderer->PlayerController(); }
    Entity* GetCloseEntity(Entity* e) { return m_entityRenderer->GetCloseEntity(e); }
    bool MoveMonster(Entity* e) { return m_entityRenderer->MoveMonster(e); }
    void RemoveEntity(Entity* e) { m_entityRenderer->RemoveEntity(e); }

private:
    static const int kGridWidth = 15;
    static const int kGridHeight = 15;

    std::map<CellType, std::pair<char, int>> m_cellIcons // Icon & Color
    {
        { CellType::Empty, std::make_pair('.', 7) },        // Couleur par défaut (gris clair)
        { CellType::Wall, std::make_pair('X', 7) },
        { CellType::ValidMove, std::make_pair('*', 14) },   // Jaune clair
        { CellType::Obstacle, std::make_pair('#', 8) },     // Gris foncé
        { CellType::Chest, std::make_pair('=', 12) }        // Rouge clair
    };

    //static const char kEmpty = '.';
    //static const char kObstacles = '#';
    //static const char KChests = '=';
    //static const char kWalls = 'X';
    //static const char kValidMove = '*';

    //const int kColorValidMove = 14; // Jaune clair
    //const int kColorDefault = 7; // Couleur par défaut (gris clair)
    //const int kColorObstacles = 8; // Gris foncé
    //const int kColorChests = 12; // Rouge clair

    std::string m_log;

    vector<vector<char>> m_grid;

    std::map<Stat, std::string> m_statsTitle {
    { Stat::HP, "HP" },
    { Stat::ATK, "ATK" },
    { Stat::DEF, "DEF" },
    { Stat::PA, "PA" },
    { Stat::PM, "PM" }
    };

    void InitWalls();
    void RandomObstacles(int);
    void RandomChest(int);
    void SpawnMonsters();
    void SpawnPlayer();

    void DisplayValidMovementCells();
    void ResetValidMovementCells();

    void RenderEntityStats(Entity*);
    void RenderAvailableActions(Entity*);
    void RenderGameLog();

    void SetConsoleColor(int color);
    void ClearConsole();

    GameManager* m_gm;
    EntityRenderer* m_entityRenderer;
};
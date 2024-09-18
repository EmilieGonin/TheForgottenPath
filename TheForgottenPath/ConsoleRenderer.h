#pragma once

#include <iostream>
#include <vector>

#include "GridRenderer.h"
#include "EntityRenderer.h"
#include "GameManager.h"

using std::vector;
using std::cout;

class ConsoleRenderer 
{
public:
    ConsoleRenderer();

    void Render();
    void SetLog(std::string);

    // Grid Renderer
    vector<vector<char>>& GetGrid() { return m_gridRenderer->GetGrid(); }
    std::map<CellType, std::pair<char, int>> GetCellIcons() const { return m_gridRenderer->GetCellIcons(); }
    bool IsMoveableCell(std::pair<int, int> coord) { return m_gridRenderer->IsMoveableCell(coord); }

    // Entity Renderer
    void PlayerController() { m_entityRenderer->PlayerController(); }
    Entity* GetCloseEntity(Entity* e) { return m_entityRenderer->GetCloseEntity(e); }
    bool MoveMonster(Entity* e) { return m_entityRenderer->MoveMonster(e); }
    void RemoveEntity(Entity* e) { m_entityRenderer->RemoveEntity(e); }

private:
    std::string m_log;

    std::map<Stat, std::string> m_statsTitle
    {
        { Stat::HP, "HP" },
        { Stat::ATK, "ATK" },
        { Stat::DEF, "DEF" },
        { Stat::PA, "PA" },
        { Stat::PM, "PM" }
    };

    void RenderValidMovementCells();
    void ResetValidMovementCells();

    void RenderEntityStats(Entity*);
    void RenderAvailableActions(Entity*);
    void RenderGameLog();

    std::string RenderSpaces(int nb);

    void SetConsoleColor(int color);
    void ClearConsole();

    GameManager* m_gm;
    GridRenderer* m_gridRenderer;
    EntityRenderer* m_entityRenderer;
};
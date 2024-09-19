#pragma once

#include <iostream>
#include <vector>

#include "GridRenderer.h"
#include "EntityRenderer.h"
#include "GameManager.h"

#define CONSOLE_SIZE 80

using std::vector;
using std::cout;

class ConsoleRenderer 
{
public:
    ConsoleRenderer();

    void Render();
    void SetLog(string s) { m_log = s; }
    map<Stat, string> GetStatsTitle() const { return m_statsTitle; }
    void ResetPreviousMovementCells();

    // Grid Renderer Getters
    vector<vector<char>>& GetGrid() { return m_gridRenderer->GetGrid(); }
    map<CellType, pair<char, int>> GetCellDatas() const { return m_gridRenderer->GetCellDatas(); }
    map<pair<int, int>, Chest*> GetChests() const { return m_gridRenderer->GetChests(); }
    bool IsBlockedCell(pair<int, int> coord) { return m_gridRenderer->IsBlockedCell(coord); }

    // Entity Renderer Getters
    void PlayerController() { m_entityRenderer->MovePlayer(); }
    Entity* GetCloseEntity(Entity* e) { return m_entityRenderer->GetCloseEntity(e); }
    bool MoveMonster(Entity* e) { return m_entityRenderer->MoveMonster(e); }
    void RemoveEntity(Entity* e) { m_entityRenderer->RemoveEntity(e); }

private:
    string m_log;

    map<Stat, string> m_statsTitle
    {
        { Stat::HP, "HP" },
        { Stat::ATK, "ATK" },
        { Stat::DEF, "DEF" },
        { Stat::PA, "PA" },
        { Stat::PM, "PM" },
        { Stat::MAXHP, "MAXHP" },
        { Stat::MAXATK, "MAXATK" },
        { Stat::MAXPA, "MAXPA" },
        { Stat::MAXPM, "MAXPM" }
    };

    void ClearConsole() { std::system("cls"); }
    void SetConsoleColor(int color);

    string RenderSpaces(int nb);
    string RenderLineBreaks(int nb);

    void RenderValidMovementCells();
    void ResetValidMovementCells();

    void RenderEntityStats(Entity*);
    void RenderAvailableActions(Entity*);
    void RenderGameLog() { cout << RenderSpaces(48) << m_log; }

    GameManager* m_gm;
    GridRenderer* m_gridRenderer;
    EntityRenderer* m_entityRenderer;
};
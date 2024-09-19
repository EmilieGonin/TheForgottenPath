#include "GridRenderer.h"

GridRenderer::GridRenderer(ConsoleRenderer* console)
{
    m_gm = GameManager::GetInstance();
    m_consoleRenderer = console;
    m_levelEditor = new LevelEditor();
    int currentLevel = m_gm->GetCurrentLevel();

    std::vector<std::string> level = m_levelEditor->GetLevel(currentLevel);
    LevelData levelData = m_levelEditor->GetLevelData(currentLevel);

    m_gridHeight = level.size();
    m_gridWidth = level[0].size();

    for (const auto& row : level) {
        m_grid.push_back(std::vector<char>(row.begin(), row.end()));
    }

    //m_grid = vector<vector<char>>(GRID_HEIGHT, vector<char>(GRID_WIDTH, m_cellDatas[CellType::Empty].first));

    //InitWalls();
    SpawnMonsters();
    SpawnPlayer();
    InitRandomElement(levelData.m_randomObstacles, CellType::Obstacle);
    InitRandomElement(levelData.m_randomChests, CellType::Chest);
    InitRandomElement(levelData.m_randomTraps, CellType::Trap);
    SpawnChests();
}

bool GridRenderer::IsBlockedCell(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;

    return m_grid[y][x] != m_cellDatas[CellType::Empty].first
        && m_grid[y][x] != m_cellDatas[CellType::ValidMove].first
        && m_grid[y][x] != m_cellDatas[CellType::PreviousMove].first
        && m_grid[y][x] != m_cellDatas[CellType::Chest].first
        && m_grid[y][x] != m_cellDatas[CellType::Trap].first;
}

bool GridRenderer::IsEntityIcon(char icon)
{
    for (auto cell : m_cellDatas)
    {
        if (icon == cell.second.first) return false;
    }

    return true;
}

void GridRenderer::InitWalls()
{
    for (int row = 0; row < m_gridHeight; ++row)
    {
        for (int col = 0; col < m_gridWidth; ++col)
        {
            if (row == 0 || row == m_gridHeight - 1 || col == 0 || col == m_gridWidth - 1)
            {
                m_grid[row][col] = m_cellDatas[CellType::VerticalWall].first;
            }
        }
    }
}

void GridRenderer::InitRandomElement(int nb, CellType type)
{
    int elementAdded = 0;

    while (elementAdded < nb)
    {
        int r = std::rand() % m_gridHeight;
        int c = std::rand() % m_gridWidth;

        // Évite placement sur les murs, les monstres, le joueur ou les cases déjà occupées
        if (m_grid[r][c] == m_cellDatas[CellType::Empty].first)
        {
            m_grid[r][c] = m_cellDatas[type].first;
            ++elementAdded;
        }
    }
}

void GridRenderer::SpawnMonsters()
{
    for (Monster* m : m_gm->GetMonsters())
    {
        bool isFound = false;

        for (int y = 0; y < m_grid.size(); ++y)
        {
            if (isFound) break;

            for (int x = 0; x < m_grid[y].size(); ++x)
            {
                if (m_grid[y][x] == m->GetIcon())
                {
                    m->SetPos(std::make_pair(x, y));
                    isFound = true;
                    break;
                }
            }
        }

        if (!isFound) m->Despawn();
    }
}

void GridRenderer::SpawnPlayer()
{
    for (int y = 0; y < m_grid.size(); ++y)
    {
        for (int x = 0; x < m_grid[y].size(); ++x)
        {
            if (m_grid[y][x] == m_gm->GetPlayer()->GetIcon())
            {
                m_gm->GetPlayer()->SetPos(std::make_pair(x, y));
                return;
            }
        }
    }
}

void GridRenderer::SpawnChests()
{
    for (int y = 0; y < m_grid.size(); ++y)
    {
        for (int x = 0; x < m_grid[y].size(); ++x)
        {
            if (m_grid[y][x] == m_cellDatas[CellType::Chest].first)
            {
                m_chests[std::make_pair(x, y)] = new Chest();
            }
        }
    }
}
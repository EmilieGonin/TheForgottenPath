#include "GridRenderer.h"

GridRenderer::GridRenderer(ConsoleRenderer* console)
{
    m_gm = GameManager::GetInstance();
    m_consoleRenderer = console;
    m_levelEditor = new LevelEditor();

    std::vector<std::string> level = m_levelEditor->GetLevel(0);

    m_gridHeight = level.size();
    m_gridWidth = level[0].size();

    for (const auto& row : level) {
        m_grid.push_back(std::vector<char>(row.begin(), row.end()));
    }

    //m_grid = vector<vector<char>>(GRID_HEIGHT, vector<char>(GRID_WIDTH, m_cellDatas[CellType::Empty].first));

    //InitWalls();
    //SpawnMonsters();
    //SpawnPlayer();
    //InitRandomElement(NB_OBSTACLES, CellType::Obstacle);
    //InitRandomElement(NB_CHESTS, CellType::Chest);
    //InitRandomElement(NB_TRAPS, CellType::Trap);
}

bool GridRenderer::IsBlockedCell(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;

    return m_grid[x][y] != m_cellDatas[CellType::Empty].first
        && m_grid[x][y] != m_cellDatas[CellType::ValidMove].first
        && m_grid[x][y] != m_cellDatas[CellType::Chest].first
        && m_grid[x][y] != m_cellDatas[CellType::Trap].first;
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
                m_grid[row][col] = m_cellDatas[CellType::Wall].first;
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

        // �vite placement sur les murs, les monstres, le joueur ou les cases d�j� occup�es
        if (m_grid[r][c] == m_cellDatas[CellType::Empty].first)
        {
            m_grid[r][c] = m_cellDatas[type].first;
            ++elementAdded;

            if (type == CellType::Chest) m_chests[std::make_pair(r, c)] = new Chest();
        }
    }
}

void GridRenderer::SpawnMonsters()
{
    for (Monster* m : m_gm->GetMonsters())
    {
        if (m->IsDead()) continue;
        m_grid[m->GetPos().first][m->GetPos().second] = m->GetIcon();
    }
}

void GridRenderer::SpawnPlayer()
{
    m_grid[m_gm->GetPlayer()->GetPos().first][m_gm->GetPlayer()->GetPos().second] = m_gm->GetPlayer()->GetIcon();
}
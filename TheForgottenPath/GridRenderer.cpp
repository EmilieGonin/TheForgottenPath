#include "GridRenderer.h"

GridRenderer::GridRenderer(ConsoleRenderer* console)
{
    m_gm = GameManager::GetInstance();
    m_consoleRenderer = console;

    m_grid = std::vector<std::vector<char>>(GRID_HEIGHT, std::vector<char>(GRID_WIDTH, m_cellDatas[CellType::Empty].first));

    InitWalls();
    SpawnMonsters();
    SpawnPlayer();
    InitRandomElement(20, CellType::Obstacle);
    InitRandomElement(5, CellType::Chest);
}

bool GridRenderer::IsMoveableCell(std::pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;

    return m_grid[x][y] != m_cellDatas[CellType::Empty].first
        && m_grid[x][y] != m_cellDatas[CellType::ValidMove].first
        && m_grid[x][y] != m_cellDatas[CellType::Chest].first;
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
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (row == 0 || row == GRID_HEIGHT - 1 || col == 0 || col == GRID_WIDTH - 1)
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
        int r = std::rand() % GRID_HEIGHT;
        int c = std::rand() % GRID_WIDTH;

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
        if (m->IsDead()) continue;
        m_grid[m->GetPos().first][m->GetPos().second] = m->GetIcon();
    }
}

void GridRenderer::SpawnPlayer()
{
    m_grid[m_gm->GetPlayer()->GetPos().first][m_gm->GetPlayer()->GetPos().second] = m_gm->GetPlayer()->GetIcon();
}
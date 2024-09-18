#include "GridRenderer.h"

GridRenderer::GridRenderer(ConsoleRenderer* console)
{
    m_gm = GameManager::GetInstance();
    m_consoleRenderer = console;

    m_grid = std::vector<std::vector<char>>(GRID_HEIGHT, std::vector<char>(GRID_WIDTH, m_cellIcons[CellType::Empty].first));

    InitWalls();
    InitRandomObstacles(20);
    InitRandomChests(5);
    SpawnMonsters();
    SpawnPlayer();
}

bool GridRenderer::IsMoveableCell(std::pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;

    return m_grid[x][y] != m_cellIcons[CellType::Empty].first
        && m_grid[x][y] != m_cellIcons[CellType::ValidMove].first
        && m_grid[x][y] != m_cellIcons[CellType::Chest].first;
}

void GridRenderer::InitWalls()
{
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (row == 0 || row == GRID_HEIGHT - 1 || col == 0 || col == GRID_WIDTH - 1)
            {
                m_grid[row][col] = m_cellIcons[CellType::Wall].first;
            }
        }
    }
}

void GridRenderer::InitRandomObstacles(int nb)
{
    int rows = GRID_HEIGHT;
    int cols = GRID_WIDTH;

    int obstaclesAdded = 0;

    while (obstaclesAdded < nb)
    {
        int r = std::rand() % rows;
        int c = std::rand() % cols;

        // Évite placement des obstacles sur les murs, les monstres, le joueur ou les cases déjà occupées
        if (m_grid[r][c] == m_cellIcons[CellType::Empty].first)
        {
            m_grid[r][c] = m_cellIcons[CellType::Obstacle].first;
            ++obstaclesAdded;
        }
    }
}

void GridRenderer::InitRandomChests(int nb)
{
    int rows = GRID_HEIGHT;
    int cols = GRID_WIDTH;

    int obstaclesAdded = 0;

    while (obstaclesAdded < nb)
    {
        int r = std::rand() % rows;
        int c = std::rand() % cols;

        // Évite placement des obstacles sur les murs, les monstres, le joueur ou les cases déjà occupées
        if (m_grid[r][c] == m_cellIcons[CellType::Empty].first)
        {
            m_grid[r][c] = m_cellIcons[CellType::Chest].first;
            ++obstaclesAdded;
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
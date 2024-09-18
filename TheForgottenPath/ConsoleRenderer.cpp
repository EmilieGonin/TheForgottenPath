#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer()
{
    m_gm = GameManager::GetInstance();
    m_gridRenderer = new GridRenderer(this);
    m_entityRenderer = new EntityRenderer(this);

    Render();
}

void ConsoleRenderer::Render()
{
    Entity* monster = GetCloseEntity(m_gm->GetPlayer());

    ClearConsole();
    RenderValidMovementCells();

    if (monster != nullptr) RenderEntityStats(monster);
    else cout << RenderLineBreaks(4);

    CONSOLE_SCREEN_BUFFER_INFO csbi; // Taille de la console
    int console_width = CONSOLE_SIZE;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calcul des marges pour centrer la grille
    int margin_left = (console_width - GRID_WIDTH * 2) / 2; // *2 car chaque cellule est suivie d'un espace

    for (const auto& row : GetGrid())
    {
        cout << RenderSpaces(margin_left);

        for (char cell : row)
        {
            if (cell == m_gm->GetPlayer()->GetIcon()) SetConsoleColor(m_gm->GetPlayer()->GetColor());
            else if (m_gridRenderer->IsEntityIcon(cell))
            {
                for (Monster* m : m_gm->GetMonsters())
                {
                    if (cell == m->GetIcon()) SetConsoleColor(m->GetColor());
                }
            }
            else
            {
                for (auto cellData : GetCellDatas())
                {
                    if (cell == cellData.second.first) SetConsoleColor(cellData.second.second);
                }
            }

            cout << cell << ' ';
        }
        cout << std::endl;
    }

    cout << "\n";
    RenderEntityStats(m_gm->GetPlayer());
    RenderAvailableActions(monster);
    RenderGameLog();
}

void ConsoleRenderer::SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

std::string ConsoleRenderer::RenderSpaces(int nb)
{
    std::string render;
    for (size_t i = 0; i < nb; i++) render += " ";
    return render;
}

std::string ConsoleRenderer::RenderLineBreaks(int nb)
{
    std::string render;
    for (size_t i = 0; i < nb; i++) render += "\n";
    return render;
}

void ConsoleRenderer::RenderValidMovementCells()
{
    ResetValidMovementCells();

    int pm = m_gm->GetPlayer()->GetStat(Stat::PM);

    int playerY = m_gm->GetPlayer()->GetPos().first;
    int playerX = m_gm->GetPlayer()->GetPos().second;

    // Boucle pour parcourir les cases autour du joueur
    for (int offsetX = -pm; offsetX <= pm; ++offsetX)
    {
        for (int offsetY = -pm; offsetY <= pm; ++offsetY)
        {
            // Calcule les nouvelles coords autour du joueur
            int newX = playerX + offsetX;
            int newY = playerY + offsetY;

            // Check que les coords sont valides et que la cellule est dans la grille
            if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT)
            {
                // Calcule la distance
                if (abs(offsetX) + abs(offsetY) <= pm)
                {
                    // Marque la cellule comme valide uniquement
                    if (GetGrid()[newY][newX] == GetCellDatas()[CellType::Empty].first)
                    {
                        GetGrid()[newY][newX] = GetCellDatas()[CellType::ValidMove].first;
                    }
                }
            }
        }
    }
}

void ConsoleRenderer::ResetValidMovementCells()
{
    for (int row = 0; row < GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < GRID_WIDTH; ++col)
        {
            if (GetGrid()[row][col] == GetCellDatas()[CellType::ValidMove].first)
            {
                GetGrid()[row][col] = GetCellDatas()[CellType::Empty].first;
            }
        }
    }
}

void ConsoleRenderer::RenderEntityStats(Entity* e)
{
    cout << RenderSpaces(46);
    cout << "*********| " << e->GetName() << " |**********" << "\n";
    cout << RenderSpaces(49);
    cout << m_statsTitle[Stat::HP] << " : " << e->GetStat(Stat::HP) << "/" << e->GetStat(Stat::MAXHP) << "   ";
    cout << m_statsTitle[Stat::ATK] << " : " << e->GetStat(Stat::ATK) << "\n";
    cout << RenderSpaces(49);
    cout << m_statsTitle[Stat::PM] << " : " << e->GetStat(Stat::PM) << "/" << e->GetStat(Stat::MAXPM) << "     ";
    cout << m_statsTitle[Stat::PA] << " : " << e->GetStat(Stat::PA) << "/" << e->GetStat(Stat::MAXPA) << "\n";
    cout << RenderSpaces(46);
    cout << "+---------------------------+" << "\n";
}

void ConsoleRenderer::RenderAvailableActions(Entity* monster)
{
    cout << RenderSpaces(46) << "|  End Turn";
    cout << "   " << ">>>" << "    " << "SPACE" << "  |" << "\n";

    monster = GetCloseEntity(m_gm->GetPlayer());

    if (monster != nullptr)
    {
        cout << RenderSpaces(46) << "|  Attack";
        cout << "    " << ">>>" << "    " << "ENTER" << "   |" << "\n";
    }

    cout << RenderSpaces(46);
    cout << "+---------------------------+" << "\n";
}
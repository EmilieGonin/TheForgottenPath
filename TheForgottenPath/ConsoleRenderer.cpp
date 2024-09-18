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
    ClearConsole();
    RenderValidMovementCells();

    Entity* monster = GetCloseEntity(m_gm->GetPlayer());

    if (monster != nullptr)
    {
        RenderEntityStats(monster);
    }
    else
    {
        cout << "\n";
        cout << "\n";
        cout << "\n";
        cout << "\n";
    }

    // R�cup�rer la taille actuelle de la console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int console_width = 80; // Valeur par d�faut
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculer les marges (espaces � gauche) pour centrer la grille
    int margin_left = (console_width - GRID_WIDTH * 2) / 2; // *2 car chaque cellule est suivie d'un espace

    for (const auto& row : GetGrid())
    {
        for (int i = 0; i < margin_left; ++i)
        {
            cout << ' ';
        }

        for (char cell : row)
        {
            if (cell == GetCellIcons()[CellType::ValidMove].first)
            {
                SetConsoleColor(GetCellIcons()[CellType::ValidMove].second);
            }
            else if (cell == GetCellIcons()[CellType::Obstacle].first)
            {
                SetConsoleColor(GetCellIcons()[CellType::Obstacle].second);
            }
            else if (cell == GetCellIcons()[CellType::Chest].first)
            {
                SetConsoleColor(GetCellIcons()[CellType::Chest].second);
            }
            else if (cell == m_gm->GetPlayer()->GetIcon())
            {
                SetConsoleColor(m_gm->GetPlayer()->GetColor());
            }
            else if (cell != GetCellIcons()[CellType::Empty].first && cell != GetCellIcons()[CellType::Wall].first)
            {
                for (Monster* m : m_gm->GetMonsters())
                {
                    if (cell == m->GetIcon())
                    {
                        SetConsoleColor(m->GetColor());
                    }
                }
            }
            else
            {
                SetConsoleColor(GetCellIcons()[CellType::Empty].second);
            }

            cout << cell << ' ';
        }
        cout << std::endl;
    }

    RenderEntityStats(m_gm->GetPlayer());
    RenderAvailableActions(monster);
    RenderGameLog();
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
            // Calcule les nouvelles coordonn�es autour du joueur
            int newX = playerX + offsetX;
            int newY = playerY + offsetY;

            // V�rifie que les coordonn�es sont valides et que la cellule est � l'int�rieur de la grille
            if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT)
            {
                // Calcule la distance de d�placement
                if (abs(offsetX) + abs(offsetY) <= pm)
                {
                    // Marque la cellule comme valide uniquement
                    if (GetGrid()[newY][newX] == GetCellIcons()[CellType::Empty].first)
                    {
                        GetGrid()[newY][newX] = GetCellIcons()[CellType::ValidMove].first;
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
            if (GetGrid()[row][col] == GetCellIcons()[CellType::ValidMove].first)
            {
                GetGrid()[row][col] = GetCellIcons()[CellType::Empty].first;
            }
        }
    }
}

void ConsoleRenderer::SetLog(std::string s)
{
    m_log = s;
}

void ConsoleRenderer::RenderEntityStats(Entity* e)
{
    //cout << "                                             ";
    cout << RenderSpaces(46);
    cout << "*********| " << e->GetName() << " |**********" << "\n";
    //cout << "                                                ";
    cout << RenderSpaces(49);
    cout << m_statsTitle[Stat::HP] << " : " << e->GetStat(Stat::HP) << "/" << e->GetStat(Stat::MAXHP) << "   ";
    cout << m_statsTitle[Stat::ATK] << " : " << e->GetStat(Stat::ATK) << "\n";
    //cout << "                                                ";
    cout << RenderSpaces(49);
    cout << m_statsTitle[Stat::PM] << " : " << e->GetStat(Stat::PM) << "/" << e->GetStat(Stat::MAXPM) << "     ";
    cout << m_statsTitle[Stat::PA] << " : " << e->GetStat(Stat::PA) << "/" << e->GetStat(Stat::MAXPA) << "\n";
    //cout << "                                             ";
    cout << RenderSpaces(46);
    cout << "+---------------------------+" << "\n";
}

void ConsoleRenderer::RenderAvailableActions(Entity* monster)
{
    cout << "                                             " << "|  End Turn";
    cout << "   " << ">>>" << "    " << "SPACE" << "  |" << "\n";

    monster = GetCloseEntity(m_gm->GetPlayer());

    if (monster != nullptr)
    {
        cout << "                                             " << "|  Attack";
        cout << "    " << ">>>" << "    " << "ENTER" << "   |" << "\n";
    }

    cout << "                                             ";
    cout << "+---------------------------+" << "\n";
}

void ConsoleRenderer::RenderGameLog()
{
    cout << "                                               ";
    cout << m_log;
}

std::string ConsoleRenderer::RenderSpaces(int nb)
{
    std::string render;

    for (size_t i = 0; i < nb; i++)
    {
        render += " ";
    }

    return render;
}

void ConsoleRenderer::SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ConsoleRenderer::ClearConsole()
{
    std::system("cls");
}
#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer() : m_grid(kGridHeight, std::vector<char>(kGridWidth, kEmpty)) 
{
    m_gm = GameManager::GetInstance();
    InitWalls();
    SpawnMonsters();
    SpawnPlayer();


    Display();
}

void ConsoleRenderer::InitWalls()
{
    for (int row = 0; row < kGridHeight; ++row)
    {
        for (int col = 0; col < kGridWidth; ++col)
        {
            if (row == 0 || row == kGridHeight - 1 || col == 0 || col == kGridWidth - 1)
            {
                m_grid[row][col] = kWall;
            }
        }
    }
}

void ConsoleRenderer::SpawnMonsters() 
{
    for (Monster* m : m_gm->GetMonsters())
    {
        m_grid[m->GetPos().first][m->GetPos().second] = m->GetIcon();
    }
}

void ConsoleRenderer::SpawnPlayer()
{
    m_grid[m_gm->GetPlayer()->GetPos().first][m_gm->GetPlayer()->GetPos().second] = m_gm->GetPlayer()->GetIcon();
}

void ConsoleRenderer::DisplayValidMovementCells()
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
            if (newX >= 0 && newX < kGridWidth && newY >= 0 && newY < kGridHeight)
            {
                // Calcule la distance de d�placement
                if (abs(offsetX) + abs(offsetY) <= pm)
                {
                    // Marque la cellule comme valide uniquement
                    if (m_grid[newY][newX] == kEmpty)
                    {
                        m_grid[newY][newX] = kValidMove;
                    }
                }
            }
        }
    }
}

void ConsoleRenderer::ResetValidMovementCells()
{

    // R�initialise les cellules valides, en conservant les autres �l�ments
    for (int row = 0; row < kGridHeight; ++row)
    {
        for (int col = 0; col < kGridWidth; ++col)
        {
            // R�initialise uniquement les cellules marqu�es comme valides
            if (m_grid[row][col] == kValidMove)
            {
               {
                    m_grid[row][col] = kEmpty;
                }
            }
        }
    }
}

void ConsoleRenderer::PlayerController()
{
    Direction d = Direction::None;

    for (const auto& pair : m_keyDirections) {
        bool isKeyPressed = GetAsyncKeyState(pair.first) & 0x8000;
        bool wasKeyPressed = m_keyStates[pair.first];

        if (isKeyPressed && !wasKeyPressed) d = pair.second;

        m_keyStates[pair.first] = isKeyPressed;
    }

    if (d != Direction::None) MoveEntity(d, m_gm->GetPlayer());
}

void ConsoleRenderer::MoveMonster(Entity* e)
{
    if (e->GetBehaviour() == Behaviour::Follow)
    {
        MoveEntity(GetPathToPlayer(e->GetPos(), false), e);
    }
    else if (e->GetBehaviour() == Behaviour::Flee)
    {
        MoveEntity(GetPathAwayFromPlayer(e->GetPos(), false), e);
    }
}

Direction ConsoleRenderer::GetPathToPlayer(std::pair<int, int> monsterPos, bool reverse)
{
    std::pair<int, int> playerPos = m_gm->GetPlayer()->GetPos();

    int diffX = reverse ? playerPos.second - monsterPos.second : playerPos.first - monsterPos.first;
    int diffY = reverse ? playerPos.first - monsterPos.first : playerPos.second - monsterPos.second;

    if (std::abs(diffX) > std::abs(diffY))
    {
        return (diffX > 0) ? Direction::Down : Direction::Up;
    }
    else
    {
        return (diffY > 0) ? Direction::Right : Direction::Left;
    }
}

Direction ConsoleRenderer::GetPathAwayFromPlayer(std::pair<int, int> monsterPos, bool reverse)
{
    std::pair<int, int> playerPos = m_gm->GetPlayer()->GetPos();

    int diffX = reverse ? monsterPos.first - playerPos.first : playerPos.first - monsterPos.first;
    int diffY = reverse ? monsterPos.second - playerPos.second : playerPos.second - monsterPos.second;

    if (std::abs(diffX) > std::abs(diffY))
    {
        return (diffX > 0) ? Direction::Right : Direction::Left;
    }
    else
    {
        return (diffY > 0) ? Direction::Down : Direction::Up;
    }
}

void ConsoleRenderer::MoveEntity(Direction d, Entity* e)
{
    std::pair<int, int> previousPos = e->GetPos();
    bool canMove = true;

    std::pair<int, int> nextDestination = GetNextDestination(d, e->GetPos());
    int x = nextDestination.first;
    int y = nextDestination.second;

    if (m_grid[x][y] != kEmpty && m_grid[x][y] != kValidMove)
    {
        if (e != m_gm->GetPlayer())
        {
            nextDestination = GetNextDestination(GetPathToPlayer(e->GetPos(), true), e->GetPos());
            x = nextDestination.first;
            y = nextDestination.second;
            if (m_grid[x][y] != kEmpty && m_grid[x][y] != kValidMove) canMove = false;
        }
        else return;
    }

    if (canMove)
    {
        m_grid[previousPos.first][previousPos.second] = kEmpty;
        m_grid[x][y] = e->GetIcon();
        e->Move(x, y);
    }
    else
    {
        e->StopTurnEarly();
    }

    Display();
}

std::pair<int, int> ConsoleRenderer::GetNextDestination(Direction d, std::pair<int, int> pos)
{
    int x = pos.first;
    int y = pos.second;

    switch (d)
    {
    case Direction::Up:
        x -= 1;
        break;
    case Direction::Down:
        x += 1;
        break;
    case Direction::Right:
        y += 1;
        break;
    case Direction::Left:
        y -= 1;
        break;
    }

    return std::make_pair(x, y);
}

void ConsoleRenderer::RenderEntityStats(Entity* e)
{
    cout << "                                             ";
    cout << "+---------------------------+" << "\n";
    cout << "                                            ";
    cout << "    " << e->GetIcon() << "  ";
    cout << m_statsTitle[Stat::HP] << " : " << e->GetStat(Stat::HP) << "/" << e->GetStat(Stat::MAXHP) << "   ";
    cout << m_statsTitle[Stat::ATK] << " : " << e->GetStat(Stat::ATK) << "\n" << "       ";
    cout << "                                            ";
    cout << m_statsTitle[Stat::PM] << " : " << e->GetStat(Stat::PM) << "/" << e->GetStat(Stat::MAXPM) << "     ";
    cout << m_statsTitle[Stat::PA] << " : " << e->GetStat(Stat::PA) << "/" << e->GetStat(Stat::MAXPA) << "\n";
    cout << "                                             ";
    cout << "+---------------------------+" << "\n";
}


void ConsoleRenderer::RenderAvailableActions(Entity* monster)
{
    cout << "                                                " << "End Turn";
    cout << "   " << ">>>" << "    " << "SPACE" << "\n";

    monster = GetCloseEntity(m_gm->GetPlayer());

    if (monster != nullptr)
    {
        cout << "                                                 " << "Attack";
        cout << "    " << ">>>" << "    " << "ENTER" << "\n";
    }

    cout << "                                             ";
    cout << "+---------------------------+" << "\n";
}

void ConsoleRenderer::RenderGameMessage()
{

}

Entity* ConsoleRenderer::GetCloseEntity(Entity* entityChecking)
{
    std::pair<int, int> posToCheck = entityChecking->GetPos();

    const std::pair<int, int> directions[] = {
        { 0, 1 },  // droite
        { 1, 0 },  // bas
        { 0, -1 }, // gauche
        { -1, 0 }, // haut
    };

    for (const auto& direction : directions)
    {
        int newX = posToCheck.first + direction.first;
        int newY = posToCheck.second + direction.second;

        if (newX >= 0 && newY >= 0 && newX < m_grid.size() && newY < m_grid[0].size())
        {
            char cellIcon = m_grid[newX][newY];
            char playerIcon = m_gm->GetPlayer()->GetIcon();

            if (entityChecking != m_gm->GetPlayer() && cellIcon == m_gm->GetPlayer()->GetIcon())
            {
                return m_gm->GetPlayer();
            }
            
            if (cellIcon != kEmpty) 
            {
                for (Monster* m : m_gm->GetMonsters())
                {
                    if (cellIcon == m->GetIcon()) {
                        return m;
                    }
                }
            }
        }
    }

    return nullptr;
}

void ConsoleRenderer::Display()
{
    ClearConsole();
    DisplayValidMovementCells();

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
    int margin_left = (console_width - kGridWidth * 2) / 2; // *2 car chaque cellule est suivie d'un espace

    for (const auto& row : m_grid) 
    {
        for (int i = 0; i < margin_left; ++i) 
        {
            cout << ' ';
        }

        for (char cell : row) 
        {
            if (cell == kValidMove) 
            {
                SetConsoleColor(kColorValidMove);
            }
            else if (cell == m_gm->GetPlayer()->GetIcon())
            {
                SetConsoleColor(m_gm->GetPlayer()->GetColor());

            }
            else if (cell != kEmpty && cell != kWall)
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
                SetConsoleColor(kColorDefault);
            }

            cout << cell << ' ';
        }
        cout << std::endl;
    }

    RenderEntityStats(m_gm->GetPlayer());
    //cout << "\n";
    //cout << "\n";
    RenderAvailableActions(monster);
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
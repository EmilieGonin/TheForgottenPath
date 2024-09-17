#include "ConsoleRenderer.h"

//enum ConsoleColor 
//{
//    DEFAULT_COLOR = 7,  // Couleur par d�faut (blanc sur noir)
//    VALID_MOVE_COLOR = 10, // Vert 
//    GOLEM_COLOR = 14,    // Jaune
//    WRAITH_SPECTRE_COLOR = 11,  // Bleu clair 
//    REAPER_COLOR = 12  // Rouge 
//};

void SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

ConsoleRenderer::ConsoleRenderer() : m_grid(kHeight, std::vector<char>(kWidth, kEmpty)) 
{
    m_gm = GameManager::GetInstance();
    InitWalls();
    SpawnMonsters();
    SpawnPlayer();

    Display();
}

void ConsoleRenderer::InitWalls()
{
    for (int row = 0; row < kHeight; ++row)
    {
        for (int col = 0; col < kWidth; ++col)
        {
            if (row == 0 || row == kHeight - 1 || col == 0 || col == kWidth - 1)
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
    MoveEntity(GetPathToPlayer(e->GetPos(), false), e);
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

void ConsoleRenderer::MoveEntity(Direction d, Entity* e)
{
    std::pair<int, int> previousPos = e->GetPos();
    bool canMove = true;

    std::pair<int, int> nextDestination = GetNextDestination(d, e->GetPos());
    int x = nextDestination.first;
    int y = nextDestination.second;

    if (m_grid[x][y] != kEmpty)
    {
        if (e != m_gm->GetPlayer())
        {
            nextDestination = GetNextDestination(GetPathToPlayer(e->GetPos(), true), e->GetPos());
            x = nextDestination.first;
            y = nextDestination.second;
            if (m_grid[x][y] != kEmpty) canMove = false;
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

void ConsoleRenderer::RenderPlayerStats()
{
    for (std::pair<Stat, float> e : m_gm->GetPlayer()->GetStats())
    {
        e.first;
        //cout << e.first << ' ';
        //cout << e.first.ToString() << ' ';
    }
}

void ConsoleRenderer::RenderMonsterStats()
{

}

void ConsoleRenderer::RenderAvailableActions()
{

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
            
            if (cellIcon != kEmpty) {
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

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //for (const auto& row : m_grid)
    //{
    //    for (char cell : row)
    //    {
    //        // Trouver l'entit� correspondant au caract�re
    //        Entity* entity = FindEntity(cell); // Impl�mentez FindEntity pour retrouver l'entit� par son ic�ne
    //        if (entity)
    //        {
    //            SetConsoleColor(entity->GetColor());
    //            std::cout << entity->GetIcon() << ' ';
    //            SetConsoleColor(7); // Remettre la couleur par d�faut
    //        }
    //        else
    //        {
    //            std::cout << cell << ' ';
    //        }
    //    }
    //    std::cout << std::endl;
    //}

    // R�cup�rer la taille actuelle de la console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int console_width = 80; // Valeur par d�faut
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculer les marges (espaces � gauche) pour centrer la grille
    int margin_left = (console_width - kWidth * 2) / 2; // *2 car chaque cellule est suivie d'un espace

    for (const auto& row : m_grid) {
        for (int i = 0; i < margin_left; ++i) {
            cout << ' ';
        }

        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << std::endl;
    }
}

void ConsoleRenderer::ClearConsole()
{
    std::system("cls");
}

//// Marquer les cases de d�placement valides autour du h�ros
//void ConsoleRenderer::MovementRange() 
//{
//    const int range = 2;
//    for (int dx = -range; dx <= range; ++dx) 
//    {
//        for (int dy = -range; dy <= range; ++dy) 
//        {
//            int new_x = m_gm->GetPlayer()->GetPos().first + dx;
//            int new_y = m_gm->GetPlayer()->GetPos().second + dy;
//            if (new_x >= 0 && new_x < kHeight && new_y >= 0 && new_y < kWidth && m_grid[new_x][new_y] == kEmpty) 
//            {
//                m_grid[new_x][new_y] = kValidMove;
//            }
//        }
//    }
//}
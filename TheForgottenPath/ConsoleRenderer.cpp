#include "ConsoleRenderer.h"

void SetConsoleColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

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
    for (Monster m : m_gm->GetMonsters())
    {
        m_grid[m.GetPos().first][m.GetPos().second] = m.GetIcon();
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

void ConsoleRenderer::MoveEntity(Direction d, Entity* e)
{
    int x = e->GetPos().first;
    int y = e->GetPos().second;

    m_grid[x][y] = kEmpty;

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

    m_grid[x][y] = e->GetIcon();
    e->Move(x, y);

    Display();
}

void ConsoleRenderer::RenderPlayerStats()
{
    cout << m_statsTitle[Stat::HP] << " : " << m_gm->GetPlayer()->GetStat(Stat::HP) << "/" << "50" << "    ";
    cout << m_statsTitle[Stat::ATK] << " : " << m_gm->GetPlayer()->GetStat(Stat::ATK) << "\n";
    cout << m_statsTitle[Stat::PM] << " : " << m_gm->GetPlayer()->GetStat(Stat::PM) << "/" << "3" << "      ";
    cout << m_statsTitle[Stat::PA] << " : " << m_gm->GetPlayer()->GetStat(Stat::PA) << "/" << "5";
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

void ConsoleRenderer::Display()
{
    ClearConsole();

    // Récupérer la taille actuelle de la console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int console_width = 80; // Valeur par défaut
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Calculer les marges (espaces à gauche) pour centrer la grille
    int margin_left = (console_width - kGridWidth * 2) / 2; // *2 car chaque cellule est suivie d'un espace

    for (const auto& row : m_grid) {
        for (int i = 0; i < margin_left; ++i) {
            cout << ' ';
        }

        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << std::endl;
    }

    RenderPlayerStats();

}

void ConsoleRenderer::ClearConsole()
{
    std::system("cls");
}
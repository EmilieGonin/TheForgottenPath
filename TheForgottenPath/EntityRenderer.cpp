#include "EntityRenderer.h"
#include "ConsoleRenderer.h"
#include "Utilities.h"

EntityRenderer::EntityRenderer(ConsoleRenderer* console)
{
    m_gm = GameManager::GetInstance();
    m_consoleRenderer = console;
}

void EntityRenderer::MovePlayer()
{
    Player* p = m_gm->GetPlayer();
    Direction d = Direction::None;

    for (const auto& pair : m_keyDirections) {
        bool isKeyPressed = GetAsyncKeyState(pair.first) & 0x8000;
        bool wasKeyPressed = m_keyStates[pair.first];

        if (isKeyPressed && !wasKeyPressed) d = pair.second;

        m_keyStates[pair.first] = isKeyPressed;
    }

    if (d == Direction::None) return;

    MoveEntity(d, p);

    if (p->GetPreviousDirection() == m_reverseDirections[d])
    {
        p->CancelLastMove();
        m_consoleRenderer->Render();
        return;
    }

    p->SetPreviousDirection(d);
}

bool EntityRenderer::MoveMonster(Entity* e)
{
    if (e->GetBehaviour() == Behaviour::Follow)
    {
        return MoveEntity(GetPathToPlayer(e->GetPos(), false), e);
    }
    else if (e->GetBehaviour() == Behaviour::Flee)
    {
        return MoveEntity(GetPathAwayFromPlayer(e->GetPos(), false), e);
    }

    return false;
}

bool EntityRenderer::MoveEntity(Direction d, Entity* e)
{
    char emptyIcon = m_consoleRenderer->GetCellDatas()[CellType::Empty].first;
    char chestIcon = m_consoleRenderer->GetCellDatas()[CellType::Chest].first;
    char trapIcon = m_consoleRenderer->GetCellDatas()[CellType::Trap].first;

    pair<int, int> previousPos = e->GetPos();
    bool canMove = true;

    pair<int, int> nextDestination = GetNextDestination(d, e->GetPos());
    int x = nextDestination.first;
    int y = nextDestination.second;

    char cellIcon = m_consoleRenderer->GetGrid()[y][x];

    if (m_consoleRenderer->IsBlockedCell(nextDestination))
    {
        if (e != m_gm->GetPlayer())
        {
            nextDestination = GetNextDestination(GetPathToPlayer(e->GetPos(), true), e->GetPos());
            x = nextDestination.first;
            y = nextDestination.second;
            cellIcon = m_consoleRenderer->GetGrid()[y][x];

            if (m_consoleRenderer->IsBlockedCell(nextDestination)) canMove = false;
        }
        else return false;
    }
    else if (cellIcon == chestIcon)
    {
        if (e == m_gm->GetPlayer())
        {
            m_consoleRenderer->GetChests()[nextDestination]->Open(e, m_consoleRenderer);
        }
        else canMove = false;
    }
    else if (cellIcon == trapIcon)
    {
        e->SetStat(Stat::HP, -TRAP_DAMAGE);
        if (e == m_gm->GetPlayer()) m_consoleRenderer->SetLog("You took " + std::to_string(TRAP_DAMAGE) + " damages from trap !");
    }

    if (!canMove)
    {
        e->StopMovementEarly();
        return false;
    }

    m_consoleRenderer->GetGrid()[previousPos.second][previousPos.first] = emptyIcon;
    m_consoleRenderer->GetGrid()[y][x] = e->GetIcon();
    e->Move(x, y);
    m_consoleRenderer->Render();
    return true;
}

void EntityRenderer::RemoveEntity(Entity* e)
{
    m_consoleRenderer->GetGrid()[e->GetPos().second][e->GetPos().first] = m_consoleRenderer->GetCellDatas()[CellType::Empty].first;
}

Entity* EntityRenderer::GetCloseEntity(Entity* entityChecking)
{
    pair<int, int> posToCheck = entityChecking->GetPos();

    const pair<int, int> directions[] = {
        { 0, 1 },  // droite
        { 1, 0 },  // bas
        { 0, -1 }, // gauche
        { -1, 0 }, // haut
    };

    for (const auto& direction : directions)
    {
        int newX = posToCheck.first + direction.first;
        int newY = posToCheck.second + direction.second;

        if (newX >= 0 && newY >= 0 && newX < m_consoleRenderer->GetGrid()[0].size() && newY < m_consoleRenderer->GetGrid().size())
        {
            char cellIcon = m_consoleRenderer->GetGrid()[newY][newX];
            char playerIcon = m_gm->GetPlayer()->GetIcon();

            if (entityChecking != m_gm->GetPlayer() && cellIcon == m_gm->GetPlayer()->GetIcon())
            {
                return m_gm->GetPlayer();
            }

            if (cellIcon != m_consoleRenderer->GetCellDatas()[CellType::Empty].first)
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

pair<int, int> EntityRenderer::GetNextDestination(Direction d, pair<int, int> pos)
{
    int x = pos.first;
    int y = pos.second;

    switch (d)
    {
    case Direction::Left:
        x -= 1;
        break;
    case Direction::Right:
        x += 1;
        break;
    case Direction::Down:
        y += 1;
        break;
    case Direction::Up:
        y -= 1;
        break;
    }

    return std::make_pair(x, y);
}

Direction EntityRenderer::GetPathToPlayer(pair<int, int> monsterPos, bool reverse)
{
    pair<int, int> playerPos = m_gm->GetPlayer()->GetPos();

    int diffX = reverse ? playerPos.second - monsterPos.second : playerPos.first - monsterPos.first;
    int diffY = reverse ? playerPos.first - monsterPos.first : playerPos.second - monsterPos.second;

    if (std::abs(diffX) > std::abs(diffY))
    {
        return (diffX > 0) ? Direction::Right : Direction::Left;
    }
    else
    {
        return (diffY > 0) ? Direction::Down : Direction::Up;
    }
}

Direction EntityRenderer::GetPathAwayFromPlayer(pair<int, int> monsterPos, bool reverse)
{
    pair<int, int> playerPos = m_gm->GetPlayer()->GetPos();

    int diffX = reverse ? monsterPos.first - playerPos.first : playerPos.first - monsterPos.first;
    int diffY = reverse ? monsterPos.second - playerPos.second : playerPos.second - monsterPos.second;

    if (std::abs(diffX) > std::abs(diffY))
    {
        return (diffX > 0) ? Direction::Left : Direction::Right;
    }
    else
    {
        return (diffY > 0) ? Direction::Up : Direction::Down;
    }
}
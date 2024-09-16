#include "GameManager.h"
#include "Dungeon.h"

int main()
{
    GameManager* gm = new GameManager();
    Dungeon dungeon(gm->GetPlayer());

    dungeon.MovementRange(gm.GetPlayer());

    return 0;
}
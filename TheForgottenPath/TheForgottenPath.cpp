#include "GameManager.h"
#include "dungeon.h"

int main()
{
    GameManager gm;
    Dungeon dungeon(gm.GetPlayer());

    dungeon.MovementRange(gm.GetPlayer());

    return 0;
}
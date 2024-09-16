#include "GameManager.h"
#include "dungeon.h"

int main()
{
    GameManager gm;
    Dungeon dungeon(gm.GetPlayer());

    dungeon.MarkValidMoves(1, 1);

    dungeon.Display();

    return 0;
}
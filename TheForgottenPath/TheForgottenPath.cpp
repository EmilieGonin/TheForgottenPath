#include "dungeon.h"

int main()
{
    Dungeon dungeon;

    dungeon.MarkValidMoves(1, 1);

    dungeon.Display();

    return 0;
}

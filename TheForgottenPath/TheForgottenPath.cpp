#include "GameManager.h"
#include "Dungeon.h"

int main()
{
    GameManager* gm = new GameManager();
    Dungeon dungeon(gm->GetPlayer());

    dungeon.MarkValidMoves(1, 1);

    dungeon.Display();

    return 0;
}
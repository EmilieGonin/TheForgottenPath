#include "GameManager.h"
#include "Dungeon.h"

int main()
{
    GameManager* gm = new GameManager();
    Dungeon dungeon;

    dungeon.MovementRange();

    return 0;
}
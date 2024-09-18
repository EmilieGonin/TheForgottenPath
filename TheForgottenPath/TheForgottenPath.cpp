#include "GameManager.h"
#include "ConsoleRenderer.h"
#include "Battle.h"

int main()
{
    srand(static_cast<unsigned int>(std::time(nullptr)));

    GameManager* gm = new GameManager();
    gm->StartNewGame();

    while (!gm->GameIsOver())
    {
        gm->StartNewBattle();
        Battle* battle = new Battle();

        while (!battle->BattleIsOver()) battle->Update();
        delete battle;
    }

    delete gm;
    return 0;
}
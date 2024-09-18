#include "GameManager.h"
#include "ConsoleRenderer.h"
#include "Battle.h"

#include <chrono>
#include <thread>

int main()
{
    srand(static_cast<unsigned int>(std::time(nullptr)));

    GameManager* gm = GameManager::GetInstance();

    while (!gm->GameIsOver())
    {
        Battle* battle = new Battle();

        while (!battle->BattleIsOver()) battle->Update();
        delete battle;
    }

    delete gm;
    return 0;
}
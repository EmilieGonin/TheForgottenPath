#include "GameManager.h"
#include "ConsoleRenderer.h"
#include "Battle.h"

int main()
{
    // Initialisation de l'al�atoire (� faire une seule fois, par exemple dans la fonction main)
    srand(static_cast<unsigned int>(std::time(nullptr)));

    bool playerTurn = true;

    GameManager* gm = new GameManager();
    //ConsoleRenderer dungeon;

    //dungeon.MovementRange();

    //while (true) // Conditions de win / lose
    //{
    //    while (playerTurn)
    //    {
    //        // on attends soit input espace soit input entr�e valide -> playerTurn false

    //        // On v�rifie si le joueur peut encore se d�placer
    //        if (gm->GetPlayer()->CanMove())
    //        {
    //            // On v�rifie si le joueur utilise les touches de d�placement
    //            if (true) // Fonction dans dungeon qui check les touches et d�place le sprite
    //            {
    //                gm->GetPlayer()->Move();
    //            }
    //        }

    //        if (true) // � c�t� d'un mob -> check la grid du dungeon
    //        {
    //            // on affiche les stats du mob
    //            // on check si le joueur utilise la touche entr�e
    //        }

    //        // on check touche espace -- uniquement en cas de d�placement ?
    //    }
    //}

    while (!gm->GameIsOver())
    {
        Battle* battle = new Battle();

        while (!battle->BattleIsOver()) battle->Update();
        delete battle;
    }

    delete gm;
    return 0;
}
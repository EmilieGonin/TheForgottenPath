#include "GameManager.h"
#include "ConsoleRenderer.h"
#include "Battle.h"

int main()
{
    // Initialisation de l'aléatoire (à faire une seule fois, par exemple dans la fonction main)
    srand(static_cast<unsigned int>(std::time(nullptr)));

    bool playerTurn = true;

    GameManager* gm = new GameManager();
    //ConsoleRenderer dungeon;

    //dungeon.MovementRange();

    //while (true) // Conditions de win / lose
    //{
    //    while (playerTurn)
    //    {
    //        // on attends soit input espace soit input entrée valide -> playerTurn false

    //        // On vérifie si le joueur peut encore se déplacer
    //        if (gm->GetPlayer()->CanMove())
    //        {
    //            // On vérifie si le joueur utilise les touches de déplacement
    //            if (true) // Fonction dans dungeon qui check les touches et déplace le sprite
    //            {
    //                gm->GetPlayer()->Move();
    //            }
    //        }

    //        if (true) // à côté d'un mob -> check la grid du dungeon
    //        {
    //            // on affiche les stats du mob
    //            // on check si le joueur utilise la touche entrée
    //        }

    //        // on check touche espace -- uniquement en cas de déplacement ?
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
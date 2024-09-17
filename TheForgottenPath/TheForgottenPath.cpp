#include "GameManager.h"
#include "Dungeon.h"

int main()
{
    bool playerTurn = true;

    GameManager* gm = new GameManager();
    Dungeon dungeon;

    dungeon.MovementRange();

    while (true) // Conditions de win / lose
    {
        while (playerTurn)
        {
            // on attends soit input espace soit input entrée valide -> playerTurn false

            // On vérifie si le joueur peut encore se déplacer
            if (gm->GetPlayer()->CanMove())
            {
                // On vérifie si le joueur utilise les touches de déplacement
                if (true) // Fonction dans dungeon qui check les touches et déplace le sprite
                {
                    gm->GetPlayer()->Move();
                }
            }

            if (true) // à côté d'un mob -> check la grid du dungeon
            {
                // on affiche les stats du mob
                // on check si le joueur utilise la touche entrée
            }

            // on check touche espace -- uniquement en cas de déplacement ?
        }
    }

    return 0;
}
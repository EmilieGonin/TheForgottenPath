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
            // on attends soit input espace soit input entr�e valide -> playerTurn false

            // On v�rifie si le joueur peut encore se d�placer
            if (gm->GetPlayer()->CanMove())
            {
                // On v�rifie si le joueur utilise les touches de d�placement
                if (true) // Fonction dans dungeon qui check les touches et d�place le sprite
                {
                    gm->GetPlayer()->Move();
                }
            }

            if (true) // � c�t� d'un mob -> check la grid du dungeon
            {
                // on affiche les stats du mob
                // on check si le joueur utilise la touche entr�e
            }

            // on check touche espace -- uniquement en cas de d�placement ?
        }
    }

    return 0;
}
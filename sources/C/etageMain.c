#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../H/etage.h"
#include "../H/menu.h"
#include "../H/piece.h"
#include "../H/item.h"
#include "../H/monster.h"

Etage* etageMain(){
    //Piece* pieces = getAllPieces(); // Nous servira peut-être plus tard pour mettre en mémoire toutes les pieces.
    int nbrSalles = getNumberPieces();

    Etage* e = createMap();
    int p = randomId(e,nbrSalles);
    //On va placer aléatoirement les salles dans l'étages
    // On doit prendre en considération la taille de l'étage CHECK
    // Le fait d'avoir 4 possibilité qui peuvent diminuer selon la position de la salle précedente CHECK

    placerSalles(e);   // On affiche l'étage

    //Piece* tabPieces[14] = {}; // Tableau de pieces de la salle

    for(int i =0; i<14; i+=1){
        if(e->Idsalles[i] == -1){
            Piece* spawner = createPiece();
            e->piece[i] = spawner;
        }else if (e->Idsalles[i] == -2)
        {
            Piece *itemRoom = createPiece();
            itemRoom->piece[itemRoom->height/2][itemRoom->width/2] = 'I';
            Item * iR = randomItem();
            e->piece[i] = itemRoom;
        }else if (e->Idsalles[i] == -3)
        {
            Piece* boss = createPiece();
            e->piece[i] = boss;
        }else if (e->Idsalles[i] == -4)
        {
            Piece* itemRoomBonus = createPiece();
            itemRoomBonus->piece[itemRoomBonus->height/2][itemRoomBonus->width/2] = 'I';
            Item * iR = randomItem();
            e->piece[i] = itemRoomBonus;
        }else{
            Piece* toAdd = getPiece(e->Idsalles[i]);
            int j = 0;
            int nbrMonster = randomNbMonster(); // Choisi aléatorement le nombre de monstre
            while (j<nbrMonster)
            {   
                //Monster* monster = randomMonster(); // Pioche aléatoirement un mostre dans le fichier
                int * coor = randomCoordonnee(toAdd);
                if(toAdd->piece[coor[0]][coor[1]] == ' '){

                    toAdd->piece[coor[0]][coor[1]] = 'M';
                    //printf("%d %d\n",coor[0],coor[1]);
                    j+=1;
                }
            }
            e->piece[i] = toAdd;
            //printPiece(toAdd,0);
        }
    }

    // Maintenant, on va recupérer et mettre en mémoire les salles qui on été tirer au sort    
    return e;
}

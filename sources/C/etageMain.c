#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../H/etage.h"
#include "../H/menu.h"
#include "../H/piece.h"

void etageMain(){
    //printf("On est la");
    //Piece* pieces = getAllPieces(); // Nous servira peut-être plus tard pour mettre en mémoire toutes les pieces.
    int nbrSalles = getNumberPieces();

    Etage* e = createMap();
    int p=randomId(e,nbrSalles);
    //On va placer aléatoirement les salles dans l'étages
    // On doit prendre en considération la taille de l'étage CHECK
    // Le fait d'avoir 4 possibilité qui peuvent diminuer selon la position de la salle précedente CHECK

    placerSalles(e);   // On affiche l'étage
    Piece* tabPieces[14] = {}; 
    for(int i =0; i<14; i+=1){
        if(e->Idsalles[i] == -1){
            Piece* spawner = createPiece();
            tabPieces[i] = spawner;
        }else if (e->Idsalles[i] == -2)
        {
            Piece* itemRoom = createPiece();
            tabPieces[i] = itemRoom;
        }else if (e->Idsalles[i] == -3)
        {
            Piece* boss = createPiece();
            tabPieces[i] = boss;
        }else if (e->Idsalles[i] == -4)
        {
            Piece* itemRoom = createPiece();
            tabPieces[i] = itemRoom;
        }else{
            Piece* toAdd = getPiece(e->Idsalles[i]);
            tabPieces[i] = toAdd;
        }
    }

    // Maintenant, on va recupérer et mettre en mémoire les salles qui on été tirer au sort    
    //On affiche l'etage + ses informations
    printEtage(e);
    printPiece(tabPieces[10],0);
    //freeEtage(e);
}

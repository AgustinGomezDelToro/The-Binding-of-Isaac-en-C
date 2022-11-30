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
    //printf("%d",nbrSalles);
    Etage* e = createMap();
    int p=randomId(e,nbrSalles);
    //On va placer aléatoirement les salles dans l'étages
    // On doit prendre en considération la taille de l'étage CHECK
    // Le fait d'avoir 4 possibilité qui peuvent diminuer selon la position de la salle précedente CHECK

    placerSalles(e);

    // Maintenant, on va recupérer et mettre en mémoire les salles qui on été tirer au sort    

    //On affiche l'etage + ses informations
    
    printEtage(e);
    freeEtage(e);
}

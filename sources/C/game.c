#include <stdio.h>
#include <stdlib.h>
#include "../H/game.h"
#include "../H/etage.h"
#include "../H/menu.h"
#include "../H/gameFunction.h"

void game(){
    selecPlayer();

    Etage* etage = etageMain();

    printEtage(etage);
    for (int i = 0; i < 14; i+=1)
    {
        printPiece(etage->piece[i],0);
    }
}
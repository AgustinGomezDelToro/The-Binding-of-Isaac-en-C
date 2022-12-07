#include <stdio.h>
#include <stdlib.h>
#include "../H/game.h"
#include "../H/etage.h"
#include "../H/menu.h"
#include "../H/gameFunction.h"

void game(){
    selecPlayer();

    Etage* etage = etageMain();
    Piece *test = createPiece();
    
    int x = test->width/2;
    int y = test->height/2;

    int lastX=0;
    int lastY=0;
    launchGame(etage,x,y);
    system("clear");
    
}
/*
*  Filename : gameFunction.c
*
*  Made by : MALLIA Jonathan
*
*  Description :
*/

#include "../H/gameFunction.h"
#include "../H/piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

// int main(void)
// {
//   while(!kbhit())
//     puts("Press a key!");
//   printf("You pressed '%c'!\n", getchar());
//   return 0;
// }

void selecPlayer(){
    int choice = 0;
    system("clear");
    while (choice != -1)
    {
        do{
            printf("********************************************************\n");
            printf("********************Choose your Hero********************\n");
            printf("********************************************************\n\n");
            //system("clear");
            printf("1 - Briatte 3 hpMax | 3.50 dmg\n");
            printf("2 - Chevaillier 1 hpMax | 2.5 dmg | 8 shield | flight\n");
            printf("3 - Hennou 6 hpMax | 2 dmg\n");
            printf("4 - Revenir a l'écran principale\n");
            printf("Faites votre choix et appuyé sur entrer : ");
            scanf("%d",&choice);
        }while(choice<=0 || choice>4);
        switch (choice) {
            case 1:
                system("clear");
                return;
            case 2:
                system("clear");
                return;
            case 3:
                system("clear");
                return;
            case 4:
                choice = -1;
                system("clear");
                return;
        }
    }
}

void launchGame(Etage* etage,int lastX,int lastY){
    Piece* actu = etage->piece[10];
    int jeu = 1;
    actu->piece[lastY][lastX] = 'P';
    while (jeu!=0)
    {
        printPiece(etage->piece[10],0);
        char dir = ' ';

        while (!kbhit())
        {
        }

        dir = getchar();
        if(dir=='Z' || dir=='z' && actu->piece[lastY -1][lastX] != 'W' || actu->piece[lastY -1][lastX] == 'D'){
            actu->piece[lastY][lastX] = ' ';
            lastY = lastY - 1;
            actu->piece[lastY][lastX] = 'P';
            etage->piece[10] = actu;
        }else if (dir=='Q' || dir=='q' && actu->piece[lastY][lastX -1] == ' ')
        {
            actu->piece[lastY][lastX] = ' ';
            lastX = lastX -1;
            actu->piece[lastY][lastX] = 'P';
            etage->piece[10] = actu;
        }else if (dir=='S' || dir=='s' && actu->piece[lastY+1][lastX] == ' ')
        {
            actu->piece[lastY][lastX] = ' ';
            lastY = lastY+1;
            actu->piece[lastY][lastX] = 'P';
            etage->piece[10] = actu;
         }else if (dir=='D' || dir=='d' && actu->piece[lastY][lastX+1] == ' ')
         {
            actu->piece[lastY][lastX] = ' ';
            lastX = lastX + 1;
            actu->piece[lastY][lastX] = 'P';
            etage->piece[10] = actu;
        }
        system("clear");
        
    }
}
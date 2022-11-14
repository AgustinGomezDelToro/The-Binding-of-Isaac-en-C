/*
*  Filename : piece.h
*
*  Made by : MALLIA Jonathan
*
*  Description : 
*/

#include "sources/H/menu.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
    int choice = 0;
    system("clear");
    while (choice != -1)
    {
        system("clear");
        do{
            printf("1 - Interface des Pieces\n");
            printf("2 - Interfaces des Items\n");
            printf("3 - Interfaces des Items\n");
            printf("4 - Fermer le programme\n");
            printf("Faites votre choix et appuyé sur entrer : ");
            scanf("%d",&choice);
        }while(choice<=0 || choice>4);
        int id=0;
        switch (choice) {
            case 1:
                pieceMain();
                break;
            case 2:
                itemMain();
                break;
            case 3:
                monsterMain(); //Partie d'Agustin
                break;
            case 4:
                choice = -1;
                break;
        }
    }
    return 0;
}
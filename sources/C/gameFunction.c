/*
*  Filename : gameFunction.c
*
*  Made by : MALLIA Jonathan
*
*  Description :
*/

#include "../H/gameFunction.h"
#include <stdio.h>
#include <stdlib.h>


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
/*
*  Filename : main.c
*
*  Made by : Vincent PHAN
*
*  Description : Main program for the Item CRUD
*/

#include "monster.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]){
    int choice = 0;
    do{
        system("clear");
        printf("1 - Créer un monstre\n");
        printf("2 - Modifier un monstre\n");
        printf("3 - Supprimer un monstre\n");
        printf("4 - Afficher tous les monstres\n");
        printf("Faites votre choix et appuyé sur entrer : ");
        scanf("%d",&choice);
    }while(choice<=0 || choice>4);

    switch (choice) {
        case 1:
            system("clear");
            Item* a = createItem();
            char* file = "ressources/monster.mtbob";
            printItem(a);
            addItemToFile(a, file);
            freeItem(a);
            break;
        case 2:
            //permet de modifier un objet
            system("clear");
            modifyItem();

            break;
        case 3:
            system("clear");
            deleteItem();
            break;
        case 4:
            system("clear");
            printAllItem();
            break;
    }
    //returner au menu principal
    printf("\n");
    printf("revenir au menu principal? (1 pour oui, 0 pour non) : ");
    scanf("%d",&choice);
    if(choice == 1){
        main(argc, argv);
    }
    else  {
        printf("\n");
        printf("Au revoir !!!\n");
        printf("\n");
    }
    return 0;
}
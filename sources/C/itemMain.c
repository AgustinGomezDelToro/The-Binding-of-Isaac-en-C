/*
*  Filename : main.c
*
*  Made by : Vincent PHAN
*
*  Description : Main program for the Item CRUD
*/

#include "../H/menu.h"
#include "../H/item.h"
#include <stdlib.h>
#include <stdio.h>

void itemMain(){
    int choice = 0;
    system("clear");
    while(choice != -1) {
        do {
            printf("1 - Créer un objet\n");
            printf("2 - Modifier un objet\n");
            printf("3 - Supprimer un objet\n");
            printf("4 - Afficher tous les objets\n");
            printf("5 - Quitter\n");
            printf("Faites votre choix et appuyé sur entrer : ");
            choice = checkInt();
        } while (choice <= 0 || choice > 5);

        switch (choice) {
            case 1:
                system("clear");
                Item *a = createItem();
                char *file = "ressources/item.itbob";
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
            case 5:
                choice = -1;
                system("clear");
                break;
        }
    }
}
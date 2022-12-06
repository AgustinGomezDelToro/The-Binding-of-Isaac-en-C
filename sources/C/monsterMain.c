/*
*  Filename : main.c
*
*  Made by : Agustin Gomez del toro
*
*  Description : Main program for the Monster CRUD
*/

#include "../H/monster.h"
#include "../H/menu.h"
#include <stdlib.h>
#include <stdio.h>

void monsterMain(){
    int choice = 0;
    char* file = "ressources/monster.mtbob";
    system("clear");
    while (choice != -1)
    {
        do{
            printf("1 - Créer un monstre\n");
            printf("2 - Modifier un monstre\n");
            printf("3 - Supprimer un monstre\n");
            printf("4 - Afficher tous les monstres\n");
            printf("5 - Quitter\n");
            printf("6 - Générer un monstre aléatoire\n");
            printf("Faites votre choix et appuyé sur entrer : ");
            scanf("%d",&choice);
        }while(choice<=0 || choice>6);

        switch (choice) {
            case 1:
                system("clear");
                Monster* a = createMonster();
                printMonster(a);
                addMonsterToFile(a, file);
                freeMonster(a);
                break;
            case 2:
                //permet de modifier un objet
                system("clear");
                modifyMonster();
                break;
            case 3:
                system("clear");
                deleteMonster();
                break;
            case 4:
                system("clear");
                printAllMonster();
                break;
            case 5:
                system("clear");
                choice = -1;
                break;
            case 6:
                system("clear");
                Monster* f = randomMonster();
                printMonster(f);
                freeMonster(f);
                break;
        }
    }
}
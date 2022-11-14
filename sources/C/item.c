/*
*  Filename : item.c
*
*  Made by : Vincent PHAN
*
*  Description :  Function for the Item CRUD
*/

#include "../H/item.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_1 "ressources/item.itbob"
#define TEMP_FILE "ressources/item_temp.itbob"



/// \def Create an Item
/// \return
Item* createItem(){
    Item* a= malloc(sizeof(Item));
    printf("Entrer le nom de l'objet : ");
    scanf("%s",a->nameItem);
    printf("\nEntrer le bonus de point de vie : ");
    scanf("%f",&a->hpMax);
    printf("\nEntrer le bonus en armure : ");
    scanf("%f",&a->shield);
    printf("\nEntrer le bonus en dégât : ");
    scanf("%f",&a->dmg);
    printf("\nTir perçant ");
    scanf("%d",&a->ps);
    printf("\nTir spectral ");
    scanf("%d",&a->ss);
    printf("\nL'objet permet-il de voler? ");
    scanf("%d", &a->flight);
    return a;

}

/// \def Print an Item
/// \param a Take an Item
void printItem(Item* a){
    printf("name=%s\nhpMax=%.1f\nshield=%.1f\ndmg=%.1f\nps=%i\nss=%i\nflight=%i\n",a->nameItem,a->hpMax,a->shield,a->dmg,a->ps,a->ss,a->flight);
}
/// \def Free memory
/// \param a
void freeItem(Item* a){
    free(a);
}

/// \def Add item to a file
/// \param a
void addItemToFile(Item* a, char* file){
    FILE* f = fopen(file,"r+");
    int nbItems = 0;
    if (f != NULL){
        fseek(f,0, SEEK_END); //va à la fin du fichier
        if(ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            fprintf(f,"{%d}\n", nbItems += 1); //Affiche le nombre d'objets

            //affiche l'objet
            fprintf(f,"---\n");
            fprintf(f,"name=%s\nhpMax=%.1f\nshield=%.1f\ndmg=%.1f\nps=%i\nss=%i\nflight=%i\n",a->nameItem,a->hpMax,a->shield,a->dmg,a->ps,a->ss,a->flight);
            fprintf(f,"---\n");
        } else{ //Fichier pas vide
            rewind(f); //on retourne au début du fichier
            fscanf(f,"{%d}\n",&nbItems); // on recupère le nombre d'objets
            fseek(f,0, SEEK_END); //on retourne à la fin
            fprintf(f,"name=%s\nhpMax=%.1f\nshield=%.1f\ndmg=%.1f\nps=%i\nss=%i\nflight=%i\n",a->nameItem,a->hpMax,a->shield,a->dmg,a->ps,a->ss,a->flight);
            fprintf(f,"---\n");

            //Mise à jour du nombre d'objets
            fseek(f,0, SEEK_SET);
            fprintf(f, "{%d}\n", nbItems += 1);
        }
        //printf("Objet ajouté\n");
    } else{
        printf("Error in openning file");
    }
    fclose(f);
}

/// \def Modify an Item in the item.itbob file
void modifyItem() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");  //ouverture du fichier item.itbob
    FILE *f_temp = fopen(TEMP_FILE, "w+"); //ouverture du fichier temporaire
    int nbItems = 0;
    int i = 0;
    int found = 0;
    Item* item_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        }else{
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            char nameItem[20];
            printf("Entrer le nom de l'objet à modifier : ");
            scanf("%s", nameItem);
            item_temp->hpMax = 0;
            item_temp->shield = 0;
            item_temp->dmg = 0;
            item_temp->ps = 0;
            item_temp->ss = 0;
            item_temp->flight = 0;
            while(i < nbItems) {
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", item_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
                fscanf(f, "shield=%f\n", &item_temp->shield);
                fscanf(f, "dmg=%f\n", &item_temp->dmg);
                fscanf(f, "ps=%d\n", &item_temp->ps);
                fscanf(f, "ss=%d\n", &item_temp->ss);
                fscanf(f, "flight=%d\n", &item_temp->flight);
                if (strcmp(nameItem, item_temp->nameItem) == 0) {
                    found = 1;
                    printf("Entrer le nom de l'objet à modifier : ");
                    scanf("%s", item_temp->nameItem);
                    printf("\nEntrer le bonus de point de vie : ");
                    scanf("%f", &item_temp->hpMax);
                    printf("\nEntrer le bonus en armure : ");
                    scanf("%f", &item_temp->shield);
                    printf("\nEntrer le bonus en dégât : ");
                    scanf("%f", &item_temp->dmg);
                    printf("\nTir perçant ");
                    scanf("%d", &item_temp->ps);
                    printf("\nTir spectral ");
                    scanf("%d", &item_temp->ss);
                    printf("\nL'objet permet-il de voler? ");
                    scanf("%d", &item_temp->flight);
                }
                addItemToFile(item_temp, TEMP_FILE);
                i += 1;
            }
        }
    } else {
        printf("Error in openning file\n");
    }
    fclose(f);
    fclose(f_temp);
    freeItem(item_temp);
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    if(found == 0){
        printf("Objet non trouvé\n");
    }else{
        printf("Objet modifié\n");
    }
}

/// \def Delete an Item
void deleteItem() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");  //ouverture du fichier item.itbob
    FILE *f_temp = fopen(TEMP_FILE, "w+"); //ouverture du fichier temporaire
    int nbItems = 0;
    int i = 0;
    int found = 0;
    Item* item_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        }else{
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            char nameItem[20];
            printf("Entrer le nom de l'objet à modifier : ");
            scanf("%s", nameItem);
            item_temp->hpMax = 0;
            item_temp->shield = 0;
            item_temp->dmg = 0;
            item_temp->ps = 0;
            item_temp->ss = 0;
            item_temp->flight = 0;
            while(i < nbItems) {
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", item_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
                fscanf(f, "shield=%f\n", &item_temp->shield);
                fscanf(f, "dmg=%f\n", &item_temp->dmg);
                fscanf(f, "ps=%d\n", &item_temp->ps);
                fscanf(f, "ss=%d\n", &item_temp->ss);
                fscanf(f, "flight=%d\n", &item_temp->flight);
                if (strcmp(nameItem, item_temp->nameItem) != 0) {
                    addItemToFile(item_temp, TEMP_FILE);
                } else{
                    found = 1;
                }
                i += 1;
            }
        }
    } else {
        printf("Error in openning file\n");
    }
    fclose(f);
    fclose(f_temp);
    freeItem(item_temp);
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    if(found == 0){
        printf("Objet non trouvé\n");
    }else{
        printf("Objet supprimé\n");
    }
}

///\def Print all the Items available
void printAllItem(){
    FILE* f = fopen(FILE_1,"r+");
    int nbItems = 0;
    int i = 0;
    Item* item_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        }else{
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            while (i < nbItems){
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", item_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
                fscanf(f, "shield=%f\n", &item_temp->shield);
                fscanf(f, "dmg=%f\n", &item_temp->dmg);
                fscanf(f, "ps=%d\n", &item_temp->ps);
                fscanf(f, "ss=%d\n", &item_temp->ss);
                fscanf(f, "flight=%d\n", &item_temp->flight);
                printItem(item_temp);
                printf("\n");
                i += 1;
            }
        }
    } else {
        printf("Error in openning file\n");
    }
    fclose(f);
    freeItem(item_temp);
}
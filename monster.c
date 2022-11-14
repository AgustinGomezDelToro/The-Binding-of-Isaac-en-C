#include "monster.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_1 "ressources/monster.mtbob"
#define TEMP_FILE "ressources/monster_temp.mtbob"



/// \def Create a monster
/// \return
Item* createMonster(){
    Item* a= malloc(sizeof(Item));
    printf("Entrer le nom du monstre : ");
    scanf("%s",a->nameItem);
    printf("\nEntrer le bonus de point de vie : ");
    scanf("%f",&a->hpMax);
    printf("\nTir normal : ");
    scanf("%d",&a->shoot);
    printf("\nTir spectral :");
    scanf("%d",&a->ss);
    printf("\nL'objet permet-il de voler? ");
    scanf("%d", &a->flight);
    return a;
}

/// \def Print a monster
/// \param a Take a monster
void printMonster(Item* a){
    printf("name=%s\nhpMax=%.1f\nshoot=%i\nss=%i\nflight=%i\n",a->nameItem,a->hpMax,a->shoot,a->ss,a->flight);
}
/// \def Free memory
/// \param a
void freeMonster(Item* a){
    free(a);
}

/// \def Add a monster to a file
/// \param a
void addMonsterToFile(Item* a, char* file){
    FILE* f = fopen(file,"r+");
    int nbItems = 0;
    if (f != NULL){
        fseek(f,0, SEEK_END); //va à la fin du fichier
        if(ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            fprintf(f,"{%d}\n", nbItems += 1); //Affiche le nombre d'objets

            //affiche l'objet
            fprintf(f,"---\n");
            fprintf(f,"name=%s\nhpMax=%.1f\nshoot=%i\nss=%i\nflight=%i\n",a->nameItem,a->hpMax,a->shoot,a->ss,a->flight);

            fprintf(f,"---\n");
        } else{ //Fichier pas vide
            rewind(f); //on retourne au début du fichier
            fscanf(f,"{%d}\n",&nbItems); // on recupère le nombre d'objets
            fseek(f,0, SEEK_END); //on retourne à la fin
            fprintf(f,"name=%s\nhpMax=%.1f\nshoot=%i\nss=%i\nflight=%i\n",a->nameItem,a->hpMax,a->shoot,a->ss,a->flight);
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

/// \def Modify a monster in the monster.mtbob file
void modifyMonster() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");  //ouverture du fichier monster.mtbob
    FILE *f_temp = fopen(TEMP_FILE, "w+"); //ouverture du fichier temporaire
    int nbItems = 0;
    int i = 0;
    int found = 0;
    Item* monster_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        }else{
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            char nameItem[20];
            printf("Entrer le nom du monstre à modifier : ");
            scanf("%s", nameItem);
            monster_temp->hpMax = 0;
            monster_temp->shoot = 0;
            monster_temp->ss = 0;
            monster_temp->flight = 0;
            while(i < nbItems) {
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", monster_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
                fscanf(f, "shoot=%d\n", &monster_temp->shoot);
                fscanf(f, "ss=%d\n", &monster_temp->ss);
                fscanf(f, "flight=%d\n", &monster_temp->flight);
                if (strcmp(nameItem, monster_temp->nameItem) == 0) {
                    found = 1;
                    printf("Entrer le nom du monstre à modifier : ");
                    scanf("%s", monster_temp->nameItem);
                    printf("\nEntrer le bonus de point de vie : ");
                    scanf("%f", &monster_temp->hpMax);
                    printf("\nEntrer le nombre de tirs : ");
                    scanf("%d", &monster_temp->shoot);
                    printf("\nTir spectral ");
                    scanf("%d", &monster_temp->ss);
                    printf("\nL'objet permet-il de voler? ");
                    scanf("%d", &monster_temp->flight);
                }
                addMonsterToFile(monster_temp, TEMP_FILE);
                i += 1;
            }
        }
    } else {
        printf("Error in openning file\n");
    }
    fclose(f);
    fclose(f_temp);
    freeMonster(monster_temp);
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    if(found == 0){
        printf("Objet non trouvé\n");
    }else{
        printf("Objet modifié\n");
    }
}

/// \def Delete a monster
void deleteMonster() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");  //ouverture du fichier monster.mtbob
    FILE *f_temp = fopen(TEMP_FILE, "w+"); //ouverture du fichier temporaire
    int nbItems = 0;
    int i = 0;
    int found = 0;
    Item* monster_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        }else{
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            char nameItem[20];
            printf("Entrer le nom du monstre à supprimer : ");
            scanf("%s", nameItem);
            monster_temp->hpMax = 0;
            monster_temp->shoot = 0;
            monster_temp->ss = 0;
            monster_temp->flight = 0;
            while(i < nbItems) {
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", monster_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
                fscanf(f, "shoot=%d\n", &monster_temp->shoot);
                fscanf(f, "ss=%d\n", &monster_temp->ss);
                fscanf(f, "flight=%d\n", &monster_temp->flight);
                if (strcmp(nameItem, monster_temp->nameItem) != 0) {
                    addMonsterToFile(monster_temp, TEMP_FILE);
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
    freeMonster(monster_temp);
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    if(found == 0){
        printf("Objet non trouvé\n");
    }else{
        printf("Objet supprimé\n");
    }
}

///\def Print all monsters available
void printAllMonster(){
    FILE* f = fopen(FILE_1,"r+");
    int nbItems = 0;
    int i = 0;
    Item* monster_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        }else{
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            while (i < nbItems){
                //printf("voici tous les objets disponibles : \n");
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", monster_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
                fscanf(f, "shoot=%d\n", &monster_temp->shoot);
                fscanf(f, "ss=%d\n", &monster_temp->ss);
                fscanf(f, "flight=%d\n", &monster_temp->flight);
                printMonster(monster_temp);
                printf("\n");
                i += 1;
            }
        }
    } else {
        printf("Error in openning file\n");
    }
    fclose(f);
    freeMonster(monster_temp);
}
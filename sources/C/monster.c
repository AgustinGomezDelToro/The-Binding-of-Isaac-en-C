/*
*  Filename : Monster.c
*
*  Made by : Agustin Gomez del toro
*
*  Description :  Function for the Monster CRUD
*/

#include "../H/monster.h"
#include "../H/item.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILE_1 "ressources/monster.mtbob"
#define TEMP_FILE "ressources/monster_temp.mtbob"

/// \def Création d'un monstre
/// \return un pointeur sur le monstre créé
Monster* createMonster() {
    Monster* a = malloc(sizeof(Monster)); //allocation de la mémoire
    do { //on demande à l'utilisateur de saisir un nom de monstre
        printf("Entrer le nom du monstre : ");
        scanf("%s", a->nameMonster);
        while ((getchar()) != '\n');
    } while(foundMonster(a->nameMonster) != 0); //on vérifie que le monstre n'existe pas déjà
    do { //on demande à l'utilisateur les caractéristiques du monstre
        printf("\nEntrer les points de vie du monstre (compris entre 1 et 1000) : ");
        a->hpMax=checkFloat(); //on vérifie que l'utilisateur a bien saisi un nombre
    } while(a->hpMax < 1 || a->hpMax > 1000); //on vérifie que le bonus est compris entre 1 et 1000
    do {
        printf("\nLe monstre peut-il voler? (O si vrai ou 1 si faux) :");
        a->shoot = checkInt(); //on vérifie que l'utilisateur a bien saisi un nombre
    } while(a->shoot != 1 && a->shoot != 0); //on vérifie que le tir perçant est vrai ou faux
    do {
        printf("\nTir spectral (O si vrai ou 1 si faux) :");
        a->ss = checkInt();
    } while(a->ss < 0 || a->ss > 1); //on vérifie que le tir spectral est vrai ou faux
    do {
        printf("\nLe monstre permet-il de voler? (O si vrai ou 1 si faux):");
        a->flight = checkInt();
    } while(a->flight != 1 && a->flight != 0);

    return a;
}

/// \def Modification d'un monstre
void modifyMonster() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");          //ouverture du fichier Monster.mtbob
    FILE *f_temp = fopen(TEMP_FILE, "w+");  //ouverture du fichier temporaire
    int nbMonsters = 0;
    int found = 0;
    char nameMonster[20];
    char bool[5];
    Monster* monster_temp = malloc(sizeof(Monster));
    if (f != NULL) {
        fseek(f, 0, SEEK_END);   //va à la fin du fichier
        if (ftell(f) == 0) {                //Premier passage ici si le fichier est vide
            printf("Aucun monstre n'a été trouvé\n");
        } else {
            rewind(f);                               //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbMonsters); //on récupère le nombre de monstres
            printf("Entrer le nom du monstre à modifier : ");
            scanf("%s", nameMonster);
            while ((getchar()) != '\n');
            for (int i = 0; i < nbMonsters; i += 1) {
                monster_temp->hpMax = 0;
                monster_temp->shoot = 0;
                monster_temp->ss = 0;
                monster_temp->flight = 0;
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", monster_temp->nameMonster); //on récupère le nom du monstre
                fscanf(f, "hpMax=%f\n", &monster_temp->hpMax); //on récupère les points de vie du monstre
                //Lis le booléen shoot
                if(fscanf(f, "shoot=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                        monster_temp->shoot = 1;
                    } else { //sinon on met la valeur à 0
                        monster_temp->shoot = 0;
                    }
                }
                //lis le booléen tir spectral
                if(fscanf(f, "ss=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        monster_temp->ss = 1;
                    } else {
                        monster_temp->ss = 0;
                    }
                }
                //lis le booléen vol
                if(fscanf(f, "flight=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        monster_temp->flight = 1;
                    } else {
                        monster_temp->flight = 0;
                    }
                }
                if (strcmp(nameMonster, monster_temp->nameMonster) != 0) { //si le nom du monstre n'est pas celui recherché alors on l'écrit dans le fichier temporaire
                    addMonsterToFile(monster_temp, TEMP_FILE);
                } else { //sinon on demande à l'utilisateur de saisir les nouvelles caractéristiques du monstre
                    do { //on demande à l'utilisateur les points de vie du monstre
                        printf("\nEntrer les nouveaux points de vie du monstre (compris entre 1 et 1000) : ");
                        monster_temp->hpMax = checkFloat(); //on vérifie que l'utilisateur a bien saisi un nombre
                    } while(monster_temp->hpMax < 1 || monster_temp->hpMax > 1000); //on vérifie que le bonus est compris entre 1 et 1000
                    do {
                        printf("\nLe monstre peut-il tirer? (O si vrai ou 1 si faux) :");
                        monster_temp->shoot = checkInt(); //on vérifie que l'utilisateur a bien saisi un nombre
                    } while(monster_temp->shoot != 1 && monster_temp->shoot != 0); //on vérifie que le tir perçant est vrai ou faux
                    do {
                        printf("\nTir spectral (O si vrai ou 1 si faux) :");
                        monster_temp->ss = checkInt();
                    } while(monster_temp->ss < 0 || monster_temp->ss > 1); //on vérifie que le tir spectral est vrai ou faux
                    do {
                        printf("\nLe monstre peut-il voler? (O si vrai ou 1 si faux):");
                        monster_temp->flight = checkInt();
                    } while(monster_temp->flight != 1 && monster_temp->flight != 0);
                    found = 1;
                    addMonsterToFile(monster_temp, TEMP_FILE); //on ajoute le monstre modifié dans le fichier temporaire
                }
            }
        }
    } else { //Erreur si le fichier ne s'ouvre pas
        printf("Error in openning file\n");
    }
    fclose(f);
    fclose(f_temp);
    freeMonster(monster_temp);
    remove(FILE_1);
    rename(TEMP_FILE, FILE_1);
    if(found == 0) {
        printf("Monstre non trouvé\n");
    } else {
        printf("Monstre modifié\n");
    }
}

/// \def Suppression d'un monstre
void deleteMonster() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");  //ouverture du fichier Monster.mtbob
    FILE *f_temp = fopen(TEMP_FILE, "w+"); //ouverture du fichier temporaire
    int nbMonsters = 0;
    int found = 0;
    char nameMonster[20];
    char bool[5];
    Monster* monster_temp = malloc(sizeof(Monster));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun monstre n'a été trouvé\n");
        } else {
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbMonsters); // on récupère le nombre de monstres
            printf("Entrer le nom du monstre à supprimer : ");
            scanf("%s", nameMonster);
            while ((getchar()) != '\n');
            for(int i = 0; i < nbMonsters; i += 1) {
                monster_temp->hpMax = 0;
                monster_temp->shoot = 0;
                monster_temp->ss = 0;
                monster_temp->flight = 0;
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", monster_temp->nameMonster);
                fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
                //Lis le booléen shoot
                if(fscanf(f, "shoot=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                        monster_temp->shoot = 1;
                    } else { //sinon on met la valeur à 0
                        monster_temp->shoot = 0;
                    }
                }
                //lis le booléen tir spectral
                if(fscanf(f, "ss=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        monster_temp->ss = 1;
                    } else {
                        monster_temp->ss = 0;
                    }
                }
                //lis le booléen vol
                if(fscanf(f, "flight=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        monster_temp->flight = 1;
                    } else {
                        monster_temp->flight = 0;
                    }
                }
                if (strcmp(nameMonster, monster_temp->nameMonster) != 0) { //si le nom du monstre n'est pas celui recherché alors on l'écrit dans le fichier temporaaire
                    addMonsterToFile(monster_temp, TEMP_FILE);
                } else { //sinon on ne l'écrit pas dans le fichier temporaire
                    found = 1; //on met found à 1 pour indiquer que le monstre a été trouvé
                }
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
    if(found == 0) {
        printf("Monstre non trouvé\n");
    } else {
        printf("Monstre supprimé\n");
    }
}

/// \def Affichage du monstre
/// \param a Le monstre à afficher
void printMonster(Monster* a) {
    //Affichage du monstre
    printf("name=%s\n",a->nameMonster); //on affiche le nom du monstre
    printf("hpMax=%.1f\n",a->hpMax); //on affiche les points de vie
    printf("shoot=%s\n", a->shoot ? "true" : "false"); //si shoot = 1 alors on affiche true sinon si shoot = 0 on affiche false
    printf("ss=%s\n", a->ss ? "true" : "false"); //si ss = 1 alors on affiche true sinon si ss = 0 on affiche false
    printf("flight=%s\n", a->flight ? "true" : "false"); //si flight = 1 alors on affiche true sinon si flight = 0 on affiche false
}

/// \def Libère la mémoire allouée à un monstre
/// \param a Le monstre à libérer
void freeMonster(Monster* a) {
    free(a);
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

///\def Affichage de tous les monstres
void printAllMonster() {
    FILE* f = fopen(FILE_1,"r"); //ouverture du fichier Monster.mtbob
    int nbMonsters = 0;
    char bool[5];
    Monster* monster_temp = malloc(sizeof(Monster)); //allocation de la mémoire pour le monstre temporaire
    if (f != NULL) {
        fseek(f, 0, SEEK_END);
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun monstre n'a été trouvé\n");
        } else {
            fseek(f, 0, SEEK_SET); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbMonsters); // on récupère le nombre de monstres
            printf("Voici les %d monstres :\n", nbMonsters);
            for(int i = 0; i < nbMonsters; i += 1) {  //on parcourt tous les monstres du fichier
                monster_temp->hpMax = 0;
                monster_temp->shoot = 0;
                monster_temp->ss = 0;
                monster_temp->flight = 0;
                fscanf(f, "---\n");
                //on récupère les valeurs du monstre
                fscanf(f, "name=%s\n", monster_temp->nameMonster);
                fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
                //on récupère les booléens du monstre
                if(fscanf(f, "shoot=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                        monster_temp->shoot = 1;
                    } else { //sinon on met la valeur à 0
                        monster_temp->shoot = 0;
                    }
                }
                //lis le bonus tir spectral
                if(fscanf(f, "ss=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        monster_temp->ss = 1;
                    } else {
                        monster_temp->ss = 0;
                    }
                }
                //lis le bonus vol
                if(fscanf(f, "flight=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        monster_temp->flight = 1;
                    } else {
                        monster_temp->flight = 0;
                    }
                }
                //on affiche le monstre
                printMonster(monster_temp);
                printf("\n");
            }
        }
    } else { //si le fichier n'a pas pu être ouvert
        printf("Error in openning file\n");
    }
    fclose(f); //on ferme le fichier
    freeMonster(monster_temp); //on libère la mémoire allouée au monstre temporaire
}

/// \def Ajout d'un monstre dans le fichier
/// \param a Le monstre à ajouter
void addMonsterToFile(Monster* a, char* file) {
    FILE* f = fopen(file,"r+"); //ouverture du fichier Monster.mtbob
    char save[10000];
    if (fgetc(f) == EOF) {
        rewind(f);
        fprintf(f, "{0}\n---\n");
    }
    rewind(f);

    int nbMonsters = 0;
    fscanf(f, "{%d}\n", &nbMonsters); // on récupère le nombre de monstres
    rewind(f);

    if (nbMonsters == 9) {
        int c;
        int i;
        for (i = 0; (c = getc(f)) != EOF; i += 1) {
            save[i] = c;
        }
        for (int j = i; j > 0; j--) {
            save[j] = save[j - 1];
        }
        rewind(f);
        for (int j = 0; j <= i; j++) {
            fputc(save[j], f);
        }
        rewind(f);
    }

    fprintf(f, "{%d}", nbMonsters);
    if (f != NULL) {
        fseek(f,0, SEEK_END); //on se place à la fin du fichier
        if(ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            fprintf(f,"{%d}\n", nbMonsters += 1); //Affiche le nombre de monstres
            //Affiche le monstre
            fprintf(f,"---\n");
            fprintf(f,"name=%s\n",a->nameMonster); //on écrit le nom du monstre dans le fichier
            if (a->hpMax != 0) { //si le monstre a un bonus de vie
                fprintf(f,"hpMax=%.1f\n",a->hpMax); //on écrit le bonus de vie dans le fichier
            }
            if (a->shoot == 1) { //si le monstre a le bonus tir perçant
                fprintf(f,"shoot=true\n"); //on écrit le bonus tir perçant dans le fichier
            }
            if (a->ss == 1) { //si le monstre a le bonus tir spectral
                fprintf(f,"ss=true\n"); //on écrit le bonus tir spectral dans le fichier
            }
            if (a->flight == 1) { //si le monstre a le bonus vol
                fprintf(f,"flight=true\n"); //on écrit le bonus vol dans le fichier
            }
            fprintf(f,"---\n");
        } else { //si le fichier n'est pas vide
            fseek(f, 0, SEEK_SET); //on retourne au début du fichier
            fscanf(f,"{%d}\n",&nbMonsters); // on récupère le nombre de monstres
            //Mise à jour du nombre de monstres
            fseek(f, 0, SEEK_SET); //on retourne au début du fichier
            fprintf(f, "{%d}\n", nbMonsters += 1);
            //Écriture du monstre dans le fichier
            fseek(f,0, SEEK_END); //on retourne à la fin du fichier
            fprintf(f,"name=%s\n",a->nameMonster);
            //on affiche les paramètres seulement s'ils sont changés
            if (a->hpMax != 0) {
                fprintf(f,"hpMax=%.1f\n",a->hpMax);
            }
            if (a->shoot == 1) {
                fprintf(f,"shoot=true\n");
            }
            if (a->ss == 1) {
                fprintf(f,"ss=true\n");
            }
            if (a->flight == 1) {
                fprintf(f,"flight=true\n");
            }
            fprintf(f,"---\n");

        }
    } else {
        printf("Error in openning file");
    }
    fclose(f);
}

/// \def Recherche si un monstre existe dans le fichier
/// \param a Le monstre à rechercher
int foundMonster(char nameMonster[20]) {
    FILE *f = fopen(FILE_1, "r");
    int nbMonsters = 0;
    char bool[5];
    Monster *monster_temp = malloc(sizeof(Monster));
    fscanf(f, "{%d}\n", &nbMonsters);
    for (int i = 0; i < nbMonsters; i += 1) {
        monster_temp->hpMax = 0;
        monster_temp->shoot = 0;
        monster_temp->ss = 0;
        monster_temp->flight = 0;
        fflush(stdin);
        fscanf(f, "---\n");
        fscanf(f, "name=%s\n", monster_temp->nameMonster);
        fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
        if(fscanf(f, "shoot=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                monster_temp->shoot = 1;
            } else { //sinon on met la valeur à 0
                monster_temp->shoot = 0;
            }
        }
        //lis le bonus tir spectral
        if(fscanf(f, "ss=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->ss = 1;
            } else {
                monster_temp->ss = 0;
            }
        }
        //lis le bonus vol
        if(fscanf(f, "flight=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->flight = 1;
            } else {
                monster_temp->flight = 0;
            }
        }
        if (strcmp(monster_temp->nameMonster, nameMonster) == 0) { //si le nom du monstre est le même que celui recherché
            printf("monstre trouvé\n");
            return 1;
        }
    }
    fclose(f);
    freeMonster(monster_temp);
    return 0;
}

/// \def Fonction qui retourne un Monster random
/// \return Un Monster random
Monster *randomMonster() {
    FILE *f = fopen(FILE_1, "r");
    int nbMonsters = 0;
    char bool[5];
    Monster *monster_temp = malloc(sizeof(Monster));
    fscanf(f, "{%d}\n", &nbMonsters);
    srand(time(NULL));
    int random = 1 + rand() % nbMonsters; //on choisit un nombre aléatoire entre 0 et le nombre de monstres
    for (int i = 0; i < random; i += 1) {
        monster_temp->hpMax = 0;
        monster_temp->shoot = 0;
        monster_temp->ss = 0;
        monster_temp->flight = 0;
        fflush(stdin);
        fscanf(f, "---\n");
        fscanf(f, "name=%s\n", monster_temp->nameMonster);
        fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
        if (fscanf(f, "shoot=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->shoot = 1;
            } else {
                monster_temp->shoot = 0;
            }
        }
        if (fscanf(f, "ss=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->ss = 1;
            } else {
                monster_temp->ss = 0;
            }
        }
        if (fscanf(f, "flight=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->flight = 1;
            } else {
                monster_temp->flight = 0;
            }
        }
    }
    fclose(f);
    return monster_temp;
}
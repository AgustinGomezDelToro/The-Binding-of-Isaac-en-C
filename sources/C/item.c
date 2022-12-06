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
#include <ctype.h>

#define FILE_1 "ressources/item.itbob"
#define TEMP_FILE "ressources/item_temp.itbob"


/// \def Création d'un objet
/// \return un pointeur sur l'objet créé
Item* createItem() {
    Item* a= malloc(sizeof(Item)); //allocation de la mémoire
    do { //on demande à l'utilisateur de saisir un nom d'objet
        printf("Entrer le nom de l'objet : ");
        scanf("%s", a->nameItem);
        while ((getchar()) != '\n');
    } while(foundItem(a->nameItem) != 0); //on vérifie que l'objet n'existe pas déjà
    do { //on demande à l'utilisateur le bonus de l'objet
        printf("\nEntrer le bonus de point de vie (compris entre 0 et 1000) : ");
        a->hpMax=checkFloat(); //on vérifie que l'utilisateur a bien saisi un nombre
    } while(a->hpMax < 0 || a->hpMax > 1000); //on vérifie que le bonus est compris entre 0 et 1000
    do {
        printf("\nEntrer le bonus d'armure (compris entre -100 et 100) : ");
        a->shield = checkFloat();
    } while(a->shield < -100 || a->shield > 100); //on vérifie que le bonus est compris entre -100 et 100
    do {
        printf("\nEntrer le bonus de dégât (compris entre -100 et 100) : ");
        a->dmg = checkFloat();
    } while(a->dmg < -100 || a->dmg > 100);
    do {
        printf("\nTir perçant (O si vrai ou 1 si faux) :");
        a->ps = checkInt(); //on vérifie que l'utilisateur a bien saisi un nombre
    } while(a->ps != 1 && a->ps != 0); //on vérifie que le tir perçant est vrai ou faux
    do {
        printf("\nTir spectral (O si vrai ou 1 si faux) :");
        a->ss = checkInt();
    } while(a->ss < 0 || a->ss > 1); //on vérifie que le tir spectral est vrai ou faux
    do {
        printf("\nL'objet permet-il de voler? (O si vrai ou 1 si faux):");
        a->flight = checkInt();
    } while(a->flight != 1 && a->flight != 0);

    return a;
}

/// \def Modification d'un objet
void modifyItem() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");          //ouverture du fichier item.itbob
    FILE *f_temp = fopen(TEMP_FILE, "w+");  //ouverture du fichier temporaire
    int nbItems = 0;
    int found = 0;
    char nameItem[20];
    char bool[5];
    Item* item_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END);   //va à la fin du fichier
        if (ftell(f) == 0) {                //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        } else {
            rewind(f);                            //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); //on récupère le nombre d'objets
            //char bool[5];
            printf("Entrer le nom de l'objet à modifier : ");
            scanf("%s", nameItem);
            while ((getchar()) != '\n');
            for (int i = 0; i < nbItems; i++) {
                item_temp->hpMax = 0;
                item_temp->shield = 0;
                item_temp->dmg = 0;
                item_temp->ps = 0;
                item_temp->ss = 0;
                item_temp->flight = 0;
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", item_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
                fscanf(f, "shield=%f\n", &item_temp->shield);
                fscanf(f, "dmg=%f\n", &item_temp->dmg);
                if(fscanf(f, "ps=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                        item_temp->ps = 1;
                    } else { //sinon on met la valeur à 0
                        item_temp->ps = 0;
                    }
                }
                //lis le bonus tir spectral
                if(fscanf(f, "ss=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        item_temp->ss = 1;
                    } else {
                        item_temp->ss = 0;
                    }
                }
                //lis le bonus vol
                if(fscanf(f, "flight=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        item_temp->flight = 1;
                    } else {
                        item_temp->flight = 0;
                    }
                }
                if (strcmp(nameItem, item_temp->nameItem) != 0) {
                    addItemToFile(item_temp, TEMP_FILE);
                } else {
                    do { //on demande à l'utilisateur le bonus de l'objet
                        printf("\nEntrer le bonus de point de vie (compris entre 0 et 1000) : ");
                        item_temp->hpMax = checkFloat(); //on vérifie que l'utilisateur a bien saisi un nombre
                    } while(item_temp->hpMax < 0 || item_temp->hpMax > 1000); //on vérifie que le bonus est compris entre 0 et 1000
                    do {
                        printf("\nEntrer le bonus d'armure (compris entre -100 et 100) : ");
                        item_temp->shield = checkFloat();
                    } while(item_temp->shield < -100 || item_temp->shield > 100); //on vérifie que le bonus est compris entre -100 et 100
                    do {
                        printf("\nEntrer le bonus de dégât (compris entre -100 et 100) : ");
                        item_temp->dmg = checkFloat();
                    } while(item_temp->dmg < -100 || item_temp->dmg > 100);
                    do {
                        printf("\nTir perçant (O si vrai ou 1 si faux) :");
                        item_temp->ps = checkInt(); //on vérifie que l'utilisateur a bien saisi un nombre
                    } while(item_temp->ps != 1 && item_temp->ps != 0); //on vérifie que le tir perçant est vrai ou faux
                    do {
                        printf("\nTir spectral (O si vrai ou 1 si faux) :");
                        item_temp->ss = checkInt();
                    } while(item_temp->ss < 0 || item_temp->ss > 1); //on vérifie que le tir spectral est vrai ou faux
                    do {
                        printf("\nL'objet permet-il de voler? (O si vrai ou 1 si faux):");
                        item_temp->flight = checkInt();
                    } while(item_temp->flight != 1 && item_temp->flight != 0);
                    found = 1;
                    addItemToFile(item_temp, TEMP_FILE);
                }
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
    if(found == 0) {
        printf("Objet non trouvé\n");
    } else {
        printf("Objet modifié\n");
    }
}

/// \def Suppression d'un objet
void deleteItem() {
    system("clear");
    FILE *f = fopen(FILE_1, "r+");  //ouverture du fichier item.itbob
    FILE *f_temp = fopen(TEMP_FILE, "w+"); //ouverture du fichier temporaire
    int nbItems = 0;
    int found = 0;
    char nameItem[20];
    char bool[5];
    Item* item_temp = malloc(sizeof(Item));
    if (f != NULL) {
        fseek(f, 0, SEEK_END); //va à la fin du fichier
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        } else {
            rewind(f); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            printf("Entrer le nom de l'objet à supprimer : ");
            scanf("%s", nameItem);
            while ((getchar()) != '\n');
            for(int i = 0; i < nbItems; i++) {
                item_temp->hpMax = 0;
                item_temp->shield = 0;
                item_temp->dmg = 0;
                item_temp->ps = 0;
                item_temp->ss = 0;
                item_temp->flight = 0;
                fscanf(f, "---\n");
                fscanf(f, "name=%s\n", item_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
                fscanf(f, "shield=%f\n", &item_temp->shield);
                fscanf(f, "dmg=%f\n", &item_temp->dmg);
                if(fscanf(f, "ps=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                        item_temp->ps = 1;
                    } else { //sinon on met la valeur à 0
                        item_temp->ps = 0;
                    }
                }
                //lis le bonus tir spectral
                if(fscanf(f, "ss=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        item_temp->ss = 1;
                    } else {
                        item_temp->ss = 0;
                    }
                }
                //lis le bonus vol
                if(fscanf(f, "flight=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        item_temp->flight = 1;
                    } else {
                        item_temp->flight = 0;
                    }
                }
                if (strcmp(nameItem, item_temp->nameItem) != 0) {
                    addItemToFile(item_temp, TEMP_FILE);
                } else {
                    found = 1;
                }
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
    if(found == 0) {
        printf("Objet non trouvé\n");
    } else {
        printf("Objet supprimé\n");
    }
}

/// \def Affichage d'un objet
/// \param a L'objet à afficher
void printItem(Item* a) {
    //Affichage de l'objet
    printf("name=%s\n",a->nameItem); //on affiche le nom de l'objet
    printf("hpMax=%.1f\n",a->hpMax);
    printf("shield=%.1f\n",a->shield);
    printf("dmg=%.1f\n",a->dmg);
    printf("ps=%s\n", a->ps ? "true" : "false"); //si ps = 1 alors on affiche true sinon si ps = 0 on affiche false
    printf("ss=%s\n", a->ss ? "true" : "false"); //si ss = 1 alors on affiche true sinon si ss = 0 on affiche false
    printf("flight=%s\n", a->flight ? "true" : "false"); //si flight = 1 alors on affiche true sinon si flight = 0 on affiche false
}

/// \def Libère la mémoire allouée à un objet
/// \param a L'objet à libérer
void freeItem(Item* a) {
    free(a);
}

///\def Affichage de tous les objets
void printAllItem() {
    FILE* f = fopen(FILE_1,"r"); //ouverture du fichier item.itbob
    int nbItems = 0;
    char bool[5];
    Item* item_temp = malloc(sizeof(Item)); //allocation de la mémoire pour l'objet temporaire
    if (f != NULL) {
        fseek(f, 0, SEEK_END);
        if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            printf("Aucun objet n'a été trouvé\n");
        } else {
            fseek(f, 0, SEEK_SET); //on retourne au début du fichier
            fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
            printf("Voici les %d objets :\n", nbItems);
            for(int i = 0; i < nbItems; i++) {  //on parcourt tous les objets du fichier
                item_temp->hpMax = 0;
                item_temp->shield = 0;
                item_temp->dmg = 0;
                item_temp->ps = 0;
                item_temp->ss = 0;
                item_temp->flight = 0;
                fscanf(f, "---\n");
                //on récupère les valeurs de l'objet
                fscanf(f, "name=%s\n", item_temp->nameItem);
                fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
                fscanf(f, "shield=%f\n", &item_temp->shield);
                fscanf(f, "dmg=%f\n", &item_temp->dmg);
                //on récupère les booléens de l'objet
                //lis le bonus tir perçant
                if(fscanf(f, "ps=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                        item_temp->ps = 1;
                    } else { //sinon on met la valeur à 0
                        item_temp->ps = 0;
                    }
                }
                //lis le bonus tir spectral
                if(fscanf(f, "ss=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        item_temp->ss = 1;
                    } else {
                        item_temp->ss = 0;
                    }
                }
                //lis le bonus vol
                if(fscanf(f, "flight=%s\n", bool)) {
                    if (strcmp(bool, "true") == 0) {
                        item_temp->flight = 1;
                    } else {
                        item_temp->flight = 0;
                    }
                }
                //on affiche l'objet
                printItem(item_temp);
                printf("\n");
            }
        }
    } else { //si le fichier n'a pas pu être ouvert
        printf("Error in openning file\n");
    }
    fclose(f); //on ferme le fichier
    freeItem(item_temp); //on libère la mémoire allouée à l'objet temporaire
}

/// \def Ajout d'un objet dans le fichier
/// \param a L'objet à ajouter
void addItemToFile(Item* a, char* file) {
    char save[100000];
    FILE* f = fopen(file,"r+"); //ouverture du fichier item.itbob
    
    if (fgetc(f) == EOF)
  {
    rewind(f);
    fprintf(f, "{0}\n---\n");
  }
  rewind(f);
    
    int nbItems = 0;
 fscanf(f, "{%d}\n", &nbItems);
  rewind(f);

  if (nbItems == 9)
  {
    printf("We are inside\n");
    int c;
    int i;
    for (i = 0; (c = getc(f)) != EOF; i++)
    {
      save[i] = c;
    }
    for (int j = i; j > 0; j--)
    {
      save[j] = save[j - 1];
    }
    rewind(f);
    for (int j = 0; j <= i; j++)
    {
      fputc(save[j], f);
    }
    rewind(f);
  }

  fprintf(f, "{%d}", nbItems);

    if (f != NULL) {
        fseek(f,0, SEEK_END); //on se place à la fin du fichier
        if(ftell(f) == 0) {  //Premier passage ici si le fichier est vide
            fprintf(f,"{%d}\n", nbItems += 1); //Affiche le nombre d'objets
            //Affiche l'objet
            fprintf(f, "\n");
            fprintf(f,"---\n");
            fprintf(f,"name=%s\n",a->nameItem); //on écrit le nom de l'objet dans le fichier
            if (a->hpMax != 0) { //si l'objet a un bonus de vie
                fprintf(f,"hpMax=%.1f\n",a->hpMax); //on écrit le bonus de vie dans le fichier
            }
            if (a->shield != 0) {
                fprintf(f,"shield=%.1f\n",a->shield);
            }
            if (a->dmg != 0) {
                fprintf(f,"dmg=%.1f\n",a->dmg);
            }
            if (a->ps == 1) { //si l'objet a le bonus tir perçant
                fprintf(f,"ps=true\n"); //on écrit le bonus tir perçant dans le fichier
            }
            if (a->ss == 1) { //si l'objet a le bonus tir spectral
                fprintf(f,"ss=true\n"); //on écrit le bonus tir spectral dans le fichier
            }
            if (a->flight == 1) { //si l'objet a le bonus vol
                fprintf(f,"flight=true\n"); //on écrit le bonus vol dans le fichier
            }
            fprintf(f,"---\n");
        } else { //si le fichier n'est pas vide
            fseek(f, 0, SEEK_SET); //on retourne au début du fichier
            fscanf(f,"{%d}\n",&nbItems); // on récupère le nombre d'objets
            //Mise à jour du nombre d'objets
            fseek(f,0, SEEK_SET);
            fprintf(f, "{%d}\n", nbItems += 1);
            //Écriture de l'objet dans le fichier
            fseek(f,0, SEEK_END); //on retourne à la fin du fichier
            fprintf(f,"name=%s\n",a->nameItem);
            if (a->hpMax != 0) {
                fprintf(f,"hpMax=%.1f\n",a->hpMax);
            }
            if (a->shield != 0) {
                fprintf(f,"shield=%.1f\n",a->shield);
            }
            if (a->dmg != 0) {
                fprintf(f,"dmg=%.1f\n",a->dmg);
            }
            if (a->ps == 1) {
                fprintf(f,"ps=true\n");
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
/// \def Recherche si un objet existe dans le fichier
/// \param a L'objet à rechercher
/// \return 1 si l'objet existe, 0 sinon
int foundItem(char nameItem[20]) {
    FILE *f = fopen(FILE_1, "r");
    int nbItems = 0;
    char bool[5];
    Item *item_temp = malloc(sizeof(Item));
    fscanf(f, "{%d}\n", &nbItems);
    for (int i = 0; i < nbItems; i++) {
        item_temp->hpMax = 0;
        item_temp->shield = 0;
        item_temp->dmg = 0;
        item_temp->ps = 0;
        item_temp->ss = 0;
        item_temp->flight = 0;
        fflush(stdin);
        fscanf(f, "---\n");
        fscanf(f, "name=%s\n", item_temp->nameItem);
        fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
        fscanf(f, "shield=%f\n", &item_temp->shield);
        fscanf(f, "dmg=%f\n", &item_temp->dmg);
        if(fscanf(f, "ps=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) { //si le booléen est true alors on met la valeur à 1
                item_temp->ps = 1;
            } else { //sinon on met la valeur à 0
                item_temp->ps = 0;
            }
        }
        //lis le bonus tir spectral
        if(fscanf(f, "ss=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                item_temp->ss = 1;
            } else {
                item_temp->ss = 0;
            }
        }
        //lis le bonus vol
        if(fscanf(f, "flight=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                item_temp->flight = 1;
            } else {
                item_temp->flight = 0;
            }
        }
        if (strcmp(item_temp->nameItem, nameItem) == 0) { //si le nom de l'objet est le même que celui recherché
            printf("Objet trouvé\n");
            return 1;
        }
    }
    fclose(f);
    freeItem(item_temp);
    return 0;
}

/// \def Fonction qui permet de vérifier si on entre bien un nombre à virgule et le retourne
float checkFloat() {
    int i;
    int point; //variable qui permet de vérifier si on a déjà entré un point
    int testChar; //variable qui permet de vérifier si on a entré un caractère
    int neg; //variable qui permet de vérifier si on a entré un nombre négatif
    int isFloat = 0;
    char str[20];
    float nb;
    while (isFloat == 0) { //tant que l'on n'a pas entré un nombre à virgule
        i = 0;
        point = 0;
        testChar = 0;
        neg = 0;
        scanf("%s", str);
        while ((getchar()) != '\n'); //on vide le buffer
        while (str[i] != '\0') { //tant que l'on n'est pas à la fin de la chaîne de caractères
            if (isalpha(str[i]) != 0 || isblank(str[i]) != 0) { //si on a entré un caractère
                testChar += 1;
            } else if (str[i] == '.') { //si on a entré un point
                point += 1;
            } else if (str[i] == '-') { //si on a entré un nombre négatif
                neg += 1;
            }
            i += 1;
        }
        if(point > 1 || testChar > 0 || neg > 1) { //si on a entré plusieurs points, plusieurs tirets ou des caractères
            printf("Erreur: Entrer un nombre : \n");
        } else { //si on a entré un nombre
            nb = atof(str); //on convertit la chaîne de caractères en float
            isFloat = 1; //on sort de la boucle
        }
    }
    return nb; //on retourne le nombre
}

/// \def Fonction qui permet de vérifier si on entre bien un nombre entier
/// \return Le nombre entier entré si c'est bon, sinon 0
int checkInt() {
    int i;
    int testChar;
    int neg;
    int point;
    int isInt = 0;
    char str[20];
    int nb;
    while (isInt == 0) {
        i = 0;
        testChar = 0;
        point = 0;
        neg = 0;
        scanf("%s", str);
        while ((getchar()) != '\n'); //on vide le buffer
        while (str[i] != '\0') {
            if (isalpha(str[i]) != 0) {
                testChar = 1;
            } else if (str[i] == '-') {
                neg += 1;
            } else if (str[i] == '.') {
                point += 1;
            }
            i += 1;
        }
        if (testChar == 1 || neg > 0 ||
            point > 0) { //si on a entré des caractères, un nombre négatif ou un nombre à virgule
            printf("Erreur: Veuillez entrer un nombre entier: "); //on redemande de entrer un nombre
        } else {
            nb = atoi(str); //on convertit la chaîne de caractères en int
            isInt = 1; //on sort de la boucle
        }
    }
    return nb; //on retourne le nombre
}

/// \def Fonction qui retourne un Item random
/// \return Un Item random
Item *randomItem() {
    FILE *f = fopen(FILE_1, "r");
    int nbItems = 0;
    char bool[5];
    Item *item_temp = malloc(sizeof(Item));
    fscanf(f, "{%d}\n", &nbItems);
    srand(time(NULL));
    int random = 1 + rand() % nbItems; //on choisit un nombre aléatoire entre 1 et le nombre d'objets
    for (int i = 0; i < random; i += 1 ) {
        item_temp->hpMax = 0;
        item_temp->shield = 0;
        item_temp->dmg = 0;
        item_temp->ps = 0;
        item_temp->ss = 0;
        item_temp->flight = 0;
        fflush(stdin);
        fscanf(f, "---\n");
        fscanf(f, "name=%s\n", item_temp->nameItem);
        fscanf(f, "hpMax=%f\n", &item_temp->hpMax);
        fscanf(f, "shield=%f\n", &item_temp->shield);
        fscanf(f, "dmg=%f\n", &item_temp->dmg);
        if(fscanf(f, "ps=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                item_temp->ps = 1;
            } else {
                item_temp->ps = 0;
            }
        }
        if(fscanf(f, "ss=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                item_temp->ss = 1;
            } else {
                item_temp->ss = 0;
            }
        }
        if(fscanf(f, "flight=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                item_temp->flight = 1;
            } else {
                item_temp->flight = 0;
            }
        }
    }
    fclose(f);
    return item_temp;
}
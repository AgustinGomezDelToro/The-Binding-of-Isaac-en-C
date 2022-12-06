#include "../H/monster.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILE_1 "ressources/monster.mtbob"
#define TEMP_FILE "ressources/monster_temp.mtbob"

/// \def Create a Monster
/// \return
Monster *createMonster()
{
  Monster *a = malloc(sizeof(Monster));
  do
  {
    printf("Entrer le nom du monstre : ");
    scanf("%s", a->nameItem);
  } while (strlen(a->nameItem) == 1);
  do
  {
    printf("\nEntrer le bonus de point de vie (compris entre 0 et 1000) : ");
    scanf("%f", &a->hpMax);
  } while (a->hpMax < 0 || a->hpMax > 1000);
  do
  {
    printf("\nTir normal : (1 si vrai ou 0 si faux)  : ");
    scanf("%d", &a->shoot);
  } while (a->shoot != 1 && a->shoot != 0);
  do
  {
    printf("\nTir spectral (1 si vrai ou 0 si faux) :");
    scanf("%d", &a->ss);
  } while (a->ss != 1 && a->ss != 0);
  do
  {
    printf("\nL'objet permet-il de voler? (1 si vrai ou 0 si faux):");
    scanf("%d", &a->flight);
  } while (a->flight != 0 && a->flight != 1);

  return a;
} // fait
// vider le buffer
void viderBuffer()
{
  int c = 0;
  while (c != '\n' && c != EOF)
  {
    c = getchar();
  }
}

/// \def Print a Monster
/// \param a Take an Item
void printMonster(Monster *monster)
{
  printf("name=%s\n", monster->nameItem);
  printf("hpMax=%.1f\n", monster->hpMax);
  printf("shoot=%s\n", monster->shoot ? "true" : "false");
  printf("ss=%s\n", monster->ss ? "true" : "false");
  printf("flight=%s\n", monster->flight ? "true" : "false");
}

/// \def Free memory
/// \param a
void freeMonster(Monster *a)
{
  free(a);
}
/// \def Add item to a Monster
/// \param a
void addMonsterToFile(Monster *a, char *file)
{
  char save[100000];
  FILE *f = fopen(file, "r+");

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

  fprintf(f, "{%d}", nbItems + 1);

  fseek(f, 0, SEEK_END);
  fprintf(f, "name=%s\n", a->nameItem);
  fprintf(f, "hpMax=%.1f\n", a->hpMax);
  if (a->shoot)
  {
    fprintf(f, "shoot=true\n");
  }
  if (a->ss)
  {
    fprintf(f, "ss=true\n");
  }
  if (a->flight)
  {
    fprintf(f, "flight=true\n");
  }
  fprintf(f, "---\n");
  fclose(f);
} // fait

/// \def Modify an Item in the monster.mtbob file
void modifyMonster()
{
  system("clear");
  FILE *f = fopen(FILE_1, "r+");         // ouverture du fichier monster.mtbob
  FILE *f_temp = fopen(TEMP_FILE, "w+"); // ouverture du fichier temporaire
  int nbItems = 0;
  int i = 0;
  int found = 0;
  Monster *monster_temp = malloc(sizeof(Monster));
  if (f != NULL)
  {
    fseek(f, 0, SEEK_END); // va à la fin du fichier
    if (ftell(f) == 0)
    { // Premier passage ici si le fichier est vide
      printf("Aucun monstre n'a été trouvé\n");
    }
    else
    {
      rewind(f);                     // on retourne au début du fichier
      fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
      char nameItem[20];
      printf("Entrer le nom du monstre à modifier : ");
      scanf("%s", nameItem);
      monster_temp->hpMax = 0;
      monster_temp->shoot = 0;
      monster_temp->ss = 0;
      monster_temp->flight = 0;
      while (i < nbItems)
      {
        fscanf(f, "---\n");
        fscanf(f, "name=%s\n", monster_temp->nameItem);
        fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
        if (fscanf(f, "shoot=true\n"))
        {
          monster_temp->shoot = 1;
        }
        if (fscanf(f, "ss=true\n"))
        {
          monster_temp->ss = 1;
        }
        if (fscanf(f, "flight=true\n"))
        {
          monster_temp->flight = 1;
        }
        if (strcmp(nameItem, monster_temp->nameItem) == 0)
        {
          found = 1;

          do
          {
            printf("\nEntrer le nouveau bonus de point de vie : ");
            scanf("%f", &monster_temp->hpMax);
          } while (monster_temp->hpMax < 0 || monster_temp->hpMax > 50);
          do
          {
            printf("\nTir normal O ou 1 :");
            scanf("%d", &monster_temp->shoot);
          } while (monster_temp->shoot != 1 && monster_temp->shoot != 0);
          do
          {
            printf("\nTir spectral O ou 1 :");
            scanf("%d", &monster_temp->ss);
          } while (monster_temp->ss != 1 && monster_temp->ss != 0);
          do
          {
            printf("\nL'objet permet-il de voler? O ou 1 :");
            scanf("%d", &monster_temp->flight);
          } while (monster_temp->flight != 1 && monster_temp->flight != 0);
        }
        addMonsterToFile(monster_temp, TEMP_FILE);
        i += 1;
      }
    }
  }
  else
  {
    printf("Error in openning file\n");
  }
  fclose(f);
  fclose(f_temp);
  freeMonster(monster_temp);
  remove(FILE_1);
  rename(TEMP_FILE, FILE_1);
  if (found == 0)
  {
    printf("Monstre non trouvé\n");
  }
  else
  {
    printf("Monstre modifié\n");
  }
} // Fait

/// \def Delete a Monster
void deleteMonster()
{
  FILE *f = fopen(FILE_1, "r");

  // Vérifier si le fichier est vide
  if (getc(f) == EOF)
  {
    printf("Le fichier est vide!\n");
    return;
  }

  // Lire le nom du monstre
  char bool[1024];
  char nom[1024];
  printf("Entrez le nom du monstre à supprimer : ");
  scanf("%s", nom);

  // Read all monsters
  rewind(f);
  Monster **monsters = malloc(sizeof(Monster *) * 100);

  // Read number of monsters
  int nbItems;
  fscanf(f, "{%d}\n---\n", &nbItems);
  printf("Le nombre de monstre est = %d\n", nbItems);

  char *line;
  size_t len = 0;

  for (int i = 0; i < nbItems; i++)
  {
    monsters[i] = malloc(sizeof(Monster));

    getline(&line, &len, f);
    sscanf(line, "name=%s\n", monsters[i]->nameItem);
    free(line);

    getline(&line, &len, f);
    sscanf(line, "hpMax=%f\n", &(monsters[i]->hpMax));
    free(line);

    for (int j = 0; j < 4; j++)
    {
      getline(&line, &len, f);
      if (strcmp(line, "---\n") == 0)
      {
        printf("Je suis la\n");
        free(line);
        break;
      }
      if (sscanf(line, "shoot=%s\n", bool))
      {
        monsters[i]->shoot = strcmp("true", bool) == 0;
      }
      if (sscanf(line, "ss=%s\n", bool))
      {
        monsters[i]->ss = strcmp("true", bool) == 0;
      }
      if (sscanf(line, "flight=%s\n", bool))
      {
        monsters[i]->flight = strcmp("true", bool) == 0;
      }
      free(line);
    }
  }

  for (int i = 0; i < nbItems; i++)
  {
    printMonster(monsters[i]);
  }

  fclose(f);

  // Search monster to delete
  int j = -1;
  for (int i = 0; i < nbItems; i++)
  {
    if (strcmp(nom, monsters[i]->nameItem) == 0)
    {
      j = i;
      break;
    }
  }

  if (j == -1)
  {
    printf("Aucun monstre ne correspond à votre recherche\n");
  }
  else
  {
    f = fopen(FILE_1, "w");
    if (nbItems > 1)
    {
      fprintf(f, "{%d}\n---\n", j == -1 ? nbItems : nbItems - 1);
      for (int i = 0; i < nbItems; i++)
      {
        if (i != j)
        {
          fprintf(f, "name=%s\n", monsters[i]->nameItem);

          fprintf(f, "hpMax=%.1lf\n", monsters[i]->hpMax);

          if (monsters[i]->shoot)
          {
            fprintf(f, "shoot=true\n");
          }

          if (monsters[i]->ss)
          {
            fprintf(f, "ss=true\n");
          }

          if (monsters[i]->flight)
          {
            fprintf(f, "flight=true\n");
          }

          fprintf(f, "---\n");
        }
      }
    }
    fclose(f);
  }
}

///\def Print all the monster available
void printAllMonster()
{
  FILE *f = fopen(FILE_1, "r");
  int nbItems = 0;
  fscanf(f, "{%d}\n", &nbItems);

  if (nbItems == 0)
  {
    printf("Aucun objet n'a été trouvé\n");
  }
  else
  {

    char name_history[nbItems][20];
    int nbNames = 0;

    printf("Voici tous les objets disponibles : \n");

    printf("---\n");

    Monster *monster = malloc(sizeof(Monster));

    for (int i = 0; i < nbItems; i++)
    {
      char bool[10];
      fscanf(f, "---\n");

      // Read name
      fscanf(f, "name=%s\n", monster->nameItem);

      // Read hpMax
      fscanf(f, "hpMax=%f\n", &monster->hpMax);

      // Read shoort
      if (fscanf(f, "shoot=%s\n", bool) == 1)
        monster->shoot = strcmp(bool, "true") == 0;
      else
        monster->shoot = 0;

      // Read ss
      if (fscanf(f, "ss=%s\n", bool) == 1)
        monster->ss = strcmp(bool, "true") == 0;
      else
        monster->ss = 0;

      // Read flight
      if (fscanf(f, "flight=%s\n", bool) == 1)
        monster->flight = strcmp(bool, "true") == 0;
      else
        monster->flight = 0;

      // Verifier si le monstre existe déjà
      int exists = 0;
      for (int j = 0; j < nbNames; j++)
      {
        if (strcmp(name_history[j], monster->nameItem) == 0)
        {
          exists = 1;
          break;
        }
      }

      if (exists)
      {
        printf("Le monstre %s existe deja\n", monster->nameItem);
      }
      else
      {
        // Print Monster
        printMonster(monster);
        strcpy(name_history[nbNames], monster->nameItem);
        nbNames++;
      }
      printf("---\n");
    }

    free(monster);
  }

  // FILE* f = fopen(FILE_1,"r+");
  // int nbItems = 0;
  // int i = 0;
  // Monster* monster_temp = malloc(sizeof(Monster));
  // if (f != NULL) {
  //     fseek(f, 0, SEEK_END); //va à la fin du fichier
  //     if (ftell(f) == 0) {  //Premier passage ici si le fichier est vide
  //         printf("Aucun objet n'a été trouvé\n");
  //     }else{
  //         rewind(f); //on retourne au début du fichier
  //         fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets
  //         printf("voici tous les objets disponibles : \n");
  //         while (i < nbItems){
  //             fscanf(f, "---\n");
  //             fscanf(f, "name=%s\n", monster_temp->nameItem);
  //             fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
  //             if(fscanf(f, "shoot=true\n")){
  //                 monster_temp->shoot = 1;
  //             }
  //             if(fscanf(f, "ss=true\n")){
  //                 monster_temp->ss = 1;
  //             }
  //             if(fscanf(f, "flight=true\n")){
  //                 monster_temp->flight = 1;
  //             }
  //             printMonster(monster_temp);
  //             printf("\n");
  //             i += 1;
  //         }
  //     }
  // } else {
  //     printf("Error in openning file\n");
  // }
  // fclose(f);
  // freeMonster(monster_temp);
}

int foundMonster(char nameItem[20])
{
  FILE *f = fopen(FILE_1, "r");
  int nbItems = 0;
  int i = 0;
  Monster *monster_temp = malloc(sizeof(Monster));
  rewind(f);                     // on retourne au début du fichier
  fscanf(f, "{%d}\n", &nbItems); // on récupère le nombre d'objets

  while (i < nbItems)
  {
    fscanf(f, "---\n");
    fscanf(f, "name=%s\n", monster_temp->nameItem);
    fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
    fscanf(f, "shoot=%d\n", &monster_temp->shoot);
    if (fscanf(f, "shoot=true\n"))
    {
      monster_temp->shoot = 1;
    }
    if (fscanf(f, "ss=true\n"))
    {
      monster_temp->ss = 1;
    }
    if (fscanf(f, "flight=true\n"))
    {
      monster_temp->flight = 1;
    }
    fflush(stdin);
    if (strcmp(nameItem, monster_temp->nameItem) != 0)
    {
      fclose(f);
      freeMonster(monster_temp);
      return 1;
    }
  }
  fclose(f);
  freeMonster(monster_temp);
  return 0;
}


Monster* randomMonster() {
  FILE* f = fopen(FILE_1,"r");
    int nbItems = 0;
    char bool[5];
    Monster *monster_temp = malloc(sizeof(Monster));
    fscanf(f, "{%d}\n", &nbItems);
    srand(time(NULL));
    int random = 1 + rand() % nbItems; //on choisit un nombre aléatoire entre 0 et le nombre d'objets
    for (int i = 0; i < random; i += 1 ) {
        monster_temp->hpMax = 0;
        monster_temp->shoot = 0;
        monster_temp->ss = 0;
        monster_temp->flight = 0;
        fflush(stdin);
        fscanf(f, "---\n");
        fscanf(f, "name=%s\n", monster_temp->nameItem);
        fscanf(f, "hpMax=%f\n", &monster_temp->hpMax);
        if(fscanf(f, "shoot=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->shoot = 1;
            } else {
                monster_temp->shoot = 0;
            }
        }
        if(fscanf(f, "ss=%s\n", bool)) {
            if (strcmp(bool, "true") == 0) {
                monster_temp->ss = 1;
            } else {
                monster_temp->ss = 0;
            }
        }
        if(fscanf(f, "flight=%s\n", bool)) {
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
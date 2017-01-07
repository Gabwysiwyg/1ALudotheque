#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main (void)
{
    //Menu();
    Client **tCli, **tClient;                       //
    Jeu **Game;                                     //
    int nb=0, nbj=0, i;                             //
    char name[20], surname[20], nomGame[100];       //
                         //                         //
    tCli = loadClient(&nb);                         //
    tClient=(Client **)malloc(sizeof(Client *));    //
    if (tClient == NULL){                           //
        printf("Erreur malloc tClient\n");          //
        exit(1);                                    //          CLIENT
    }                                               //
    //tClient = newClient(tCli, &nb);                 //          Obligé de retourner un tableau avec la newClient sinon segFault
    /*printf("Name\n");                             //
    scanf("%*c%s", name);                           //
    printf("Surname\n");                            //
    scanf("%*c%s", surname);                        //
    delClient(tClient, &nb, name, surname);         //
    printf("nb: %d\n", nb);*/                       //
    for(i=0; i < nb; i++)                           //
        printf("%s, %s, %s, %s, %d\n", tCli[i]->nom, tCli[i]->prenom, tCli[i]->adresse, tCli[i]->ville, tCli[i]->codeP);
    printf("\n");

    Game=loadGameList (&nbj);
                                                                                    //
    /*printf("Name\n");                                                               //
    scanf("%*c%s", name);                                                           //  
    printf("Surname\n");                                                            //
    scanf("%*c%s", surname);                                                        //
    printf("Nom Game\n");                                                            //          JEU/EMPRUNTS
    scanf("%*c%s", nomGame);                                                        //       
                                                                                    //
    newEmprunt(name, surname, nomGame, Game, nbj, tClient, nb);    */                 //
                                                                                    //
    for(i=0; i < nb; i++)                                                           //
        printf("%s, %s, %s, %s, %d, %s\n", tCli[i]->nom, tCli[i]->prenom, tCli[i]->adresse, tCli[i]->ville, tCli[i]->codeP, tCli[i]->lEmpr->empr.jeu.nom);



    free(*tCli);
    //free(tClient);
    free(*Game);
	return 0;
}
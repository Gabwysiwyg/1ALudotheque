#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main (void)
{
    Client **tCli;                  //
    Jeu **tJeu;
    Afternoon *tAft;
    int nbc=0, nbj=0, nba=0;
    bool t;

    tCli = loadClient(&nbc);

    tJeu = loadGameList (&nbj);

    //tAft = loadAfternoon(&nba, tCli, nbc);

    //Menu(tCli, nbc, tJeu, nbj);

    printf("%s\n", tCli[0]->nom);

    //printf("%s\n", tAft[0].jeu.nom);


    saveClient(tCli, nbc);

    saveEmprunt(tCli, nbc);

    //saveAft(tAft, nba);
    free(tCli);
    free(tJeu);
	return 0;
}
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

    loadEmprunt(tCli, nbc, tJeu, nbj);

    //tAft = loadAfternoon(&nba, tCli, nbc);
    

    //Menu(tCli, nbc, tJeu, nbj);
    //newEmprunt(tJeu, nbj, tCli, nbc);

    saveClient(tCli, nbc);

    saveEmprunt(tCli, nbc);

    saveAft(tAft, nba);
    free(tCli);
    free(tJeu);
	return 0;
}
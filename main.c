#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main (void)
{
    Client **tCli;                  //
    Jeu **tJeu;                                     //
    int nbc=0, nbj=0;
    bool t;
                                                    //
    tCli = loadClient(&nbc);                         //
    tJeu = loadGameList (&nbj);
     printf("%d", findJeu(tJeu, nbj, "Hylics", &t));

    Menu(tCli, nbc, tJeu, nbj);




	return 0;
}
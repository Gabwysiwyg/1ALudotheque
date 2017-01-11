#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main (void)
{
    Client **tCli;                  
    Jeu **tJeu;
    Afternoon *tAft;
    int nbc=0, nbj=0, nba=0, end = 0;
    bool t;

   while (!end)
   {
        char *s = CreatePrompt();
        if (s != NULL)
        {
            printf ("%s", s);
            fflush (stdout);
            free(s), s = NULL;
        }

        {
            char line[128]="";
            fgets(line, sizeof line, stdin);
            end = strcmp(line, "Quit Bitch\n") == 0;
        }

        tCli = loadClient(&nbc);
        tJeu = loadGameList (&nbj);
        loadEmprunt(tCli, nbc, tJeu, nbj);
        tAft = loadAfternoon(&nba, tCli, nbc);

        Menu(tCli, nbc, tJeu, nbj, tAft, nba);

        




        saveClient(tCli, nbc);
        saveEmprunt(tCli, nbc);
        saveAft(tAft, nba);

        free(tCli);
        free(tJeu);
        free(tAft);
    }
    return 0;
}

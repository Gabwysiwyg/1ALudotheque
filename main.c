#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>*/
#include "fonctions.h"

//gcc -I/usr/local/include/sdl2 *.c -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -o lol //POUR COMPILER ET APPELER LIB
//ERREUR = INSERE UN NEW CLIENT EN TETE ET TU VERRAS QUE LE NOM DU CLIENT SUIVANT EST DELETE.

int main (void)
{
    Client **tCli;                  
    Jeu **tJeu;
    Afternoon *tAft;
    int nbc=0, nbj=0, nba=0, i;
    bool t;
    


    tCli = loadClient(&nbc);
    tJeu = loadGameList (&nbj);
    loadEmprunt(tCli, nbc, tJeu, nbj);
    tAft = loadAfternoon(&nba, tCli, nbc);
    //InterfGraphique();
    
    for(i=0; i < nbc; i++)
        if (isLate(*tCli[i]))
            tCli[i]->retard = 1;
    Menu(tCli, nbc, tJeu, nbj, tAft, nba);

    return 0;
    
}

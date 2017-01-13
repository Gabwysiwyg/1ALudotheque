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
    int nbc=0, nbj=0, nba=0, endPrompt=0;
    bool t;

    tCli = loadClient(&nbc);
    tJeu = loadGameList (&nbj);
    loadEmprunt(tCli, nbc, tJeu, nbj);
    tAft = loadAfternoon(&nba, tCli, nbc);

    //InterfGraphique();
    
    Menu(tCli, &nbc, tJeu, &nbj, tAft, &nba);

    tAft = checkTime(tCli, nbc, tJeu, nbj, tAft, &nba);
    
    saveClient(tCli, nbc);
    saveEmprunt(tCli, nbc);
    saveAft(tAft, nba);

    //free(tAft); //fix TODO
    free(tJeu);
    free(tCli);

    return 0;
    
}

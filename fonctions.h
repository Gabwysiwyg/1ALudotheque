#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>*/
#include "client.h"


typedef struct maillonC {
	Client cli;
	struct maillonC *nxt;
} MaillonC, *liCli;


typedef struct {
	Jeu jeu;
	Date date;
	int nbPdisp; //nb de places dispo
	int nbPtot; //nb de places totales
	liCli lCli;
} Afternoon;


int printMenu (); //Done
void Menu(Client **tCli, int nbc, Jeu **tJeu, int nbj, Afternoon *tAft, int nba); //Done
Jeu readJeu(FILE *fe); //Done
Jeu **loadGameList (int *nb); // Done
void saveGameList(Jeu **tJeu, int nb); //Done
void printGameList(Jeu **tJeu, int nb); //Done
int findJeu(Jeu **tJeu, int nb, char *nom, bool *t); //Done
void saveAft(Afternoon tAft[], int nb); //Done

Afternoon *loadAfternoon(int *nb, Client **tCli, int nbc); //Done
Afternoon *newAfternoon(Afternoon *otAft, int *nba, Jeu **tJeu, int nb); //Done
Afternoon *delAfternoon(Afternoon *otAft, int wh, int *nba, Jeu **tJeu, int nbj); //Done
void printAftReg(Afternoon *tAft, int nba); //Done


void regForAfternoon(Afternoon *tAft, int nba, Client **tCli, int nbc); //Done
liCli insCliAft(Client cli, Afternoon aft); //Done

Afternoon *checkTime(Client **tCli, int nb, Jeu **tJeu, int nbj, Afternoon *tAft, int *nba); //Done


int InterfGraphique(void); //Done

void quit(Client **tCli, int nbc, Jeu **tJeu, int nbj, Afternoon *tAft, int *nba); //Done

void mail(Client cli); //Done
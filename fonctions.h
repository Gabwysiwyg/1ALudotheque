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


int printMenu ();
void Menu(Client **tCli, int nbc, Jeu **tJeu, int nbj, Afternoon *tAft, int nba);
Jeu readJeu(FILE *fe); //Done
Jeu **loadGameList (int *nb); // Done
void saveGameList(Jeu **tJeu, int nb);
void printGameList(Jeu **tJeu, int nb);
int findJeu(Jeu **tJeu, int nb, char *nom, bool *t); //DICHOTOMIQUE VOIR COURS //TODO PROBLEME DANS LA FONCTION!
void saveAft(Afternoon tAft[], int nb); //Done

Afternoon *loadAfternoon(int *nb, Client **tCli, int nbc); //Done
Afternoon *newAfternoon(Afternoon *otAft, int *nba, Jeu **tJeu, int nb); //Done
Afternoon *delAfternoon(Afternoon *otAft, int wh, int *nba, Jeu **tJeu, int nbj);
void printAftReg(Afternoon *tAft, int nba);


void regForAfternoon(Afternoon *tAft, int nba, Client **tCli, int nbc); //Done
liCli insCliAft(Client cli, Afternoon aft); //Done

int subDate(Date d1, Date d2); // Done
Afternoon *checkTime(Client **tCli, int nb, Jeu **tJeu, int nbj, Afternoon *tAft, int *nba);


int InterfGraphique(void);

void quit(Client **tCli, int nbc, Jeu **tJeu, int nbj, Afternoon *tAft, int *nba);

void mail(Client cli);
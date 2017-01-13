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



void printMenu(int *choix); // Done
void Menu (Client **tCli, int nbc, Jeu **tJeu, int nbj, Afternoon *tAft, int nba); // Done

Jeu readJeu(FILE *fe); //Done
Jeu **loadGameList (int *nb); // Done

void saveAft(Afternoon tAft[], int nb); //Done

Afternoon *loadAfternoon(int *nb, Client **tCli, int nbc); //Done
Afternoon *newAfternoon(Afternoon *otAft, int *nba, Jeu **tJeu, int nb); //Done
void regForAfternoon(Afternoon *tAft, int nba, Client **tCli, int nbc); //Done
liCli insCliAft(Client cli, Afternoon aft); //Done

int subDate(Date d1, Date d2); // Done
void checkTime(Client **tCli, int nb); //TODO Fix maybe


int InterfGraphique(void);

char * CreatePrompt (void); //Done but not complete
void Prompt (int end); //Done but not complete
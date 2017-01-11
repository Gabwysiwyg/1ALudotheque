#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void Menu (Client **tCli, int nbc, Jeu **tJeu, int nbj); // Done

Jeu readJeu(FILE *fe); //Done
Jeu **loadGameList (int *nb); // Done

void newEmprunt(Jeu **tJeu, int nbj, Client **tCli, int nbc);
void saveEmprunt(Client **tCli, int nb); //Done

Afternoon *loadAfternoon(int *nb, Client **tCli, int nbc);
Afternoon *newAfternoon(Afternoon *otAft, int *nba, Jeu **tJeu, int nb); //TODO Faire la fonction avec tab pointeurs
void regForAfternoon(Afternoon tAft[], int nba, Client **tCli, int nbc);
liCli insCliAft(Client cli, Afternoon aft);

int subDate(Date d1, Date d2); // Done
void checkTime(Client **tCli, int nb);

Date getDate();
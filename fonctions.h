#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"


typedef struct{
	int jour;
	int mois;
	int an;
} Date;



typedef struct {
	char nom[40];
	int nbdisp; //nb d'exemplaires dispo
	int nbtot; //nb d'exemplaires total
} Jeu;

typedef struct {
	Client client;
	Jeu jeu;
	Date date;
	bool retard; //1 si en retard
} Emprunt;

typedef struct {
	Jeu jeu;
	Date date;
	int nbPdisp; //nb de places dispo
	int nbPtot; //nb de places totales
} ApresMidi;



void printMenu(int *choix);
void Menu ();


Jeu * putListInTab (Jeu *tJeu);
void newEmprunt(Client client, Jeu jeu);

void newAfternoon(Jeu jeu, Date date, int nbtot);
void regForAfternoon(Client client, ApresMidi apMidi);

int subDate(Date d1, Date d2);
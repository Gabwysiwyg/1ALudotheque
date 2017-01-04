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
} Afternoon;



void printMenu(int *choix); // Done
void Menu (); // Done


Jeu * putListInTab (Jeu tJeu[]); // Done
Emprunt * newEmprunt(Client client, Jeu jeu, Jeu tJeu[]); // Done

Afternoon * newAfternoon(Jeu jeu, Date date, int nbtot); // Done
void regForAfternoon(Client client, Afternoon aftern);

int subDate(Date d1, Date d2); // Done
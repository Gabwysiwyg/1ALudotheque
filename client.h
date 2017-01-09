	#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct {
	char nom[100];
	int nbdisp; //nb d'exemplaires dispo
	int nbtot; //nb d'exemplaires total
} Jeu;

typedef struct{
	int jour;
	int mois;
	int an;
} Date;

typedef struct {
	Jeu jeu;
	Date date;
	bool retard; //1 si en retard
} Emprunt;

typedef struct maillonE {
	Emprunt empr;
	struct maillonE *nxt;
} MaillonE, *lEmprunt;

typedef struct {
	char nom[20];
	char prenom[20];
	char adresse[50];
	char ville[20];
	int codeP;
	lEmprunt lEmpr;
	bool paye; //1 si il a payé
	int nbEmp;
} Client;

Client readClient(FILE *file); //read client info in file // Done
Client ** loadClient(int *nbmax); //load tCli from file, and sort them while inserting //Done
void rightShift(Client **tCli, int nbmax, int n); //Done

int cmpNomPrenom(Client c1, Client c2); //strcmp with name & surname // Done
void saveClient(Client **tClient, int nb);


int findCli(Client **tCli, int nb, char *nom, char *prenom, bool *t); //DICHOTOMIQUE //Done
Client ** newClient(Client **tCli, int *nb); // Done
void updateCli(Client *cli); // Done
void leftShift(Client **tCli, int nb, int n); //Done
void delClient(Client **tCli, int *nb); //Done
lEmprunt insEmpr(Client cli, Emprunt empr); //Done
int nbEmpr(Client cli); //Done
void loadEmprunt(Client **tCli, int nb, Jeu **tJeu, int nbj)


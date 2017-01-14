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
	char codeP[6];
	lEmprunt lEmpr;
	bool paye; //1 si il a payé
	Date dIns;
	bool retard;
} Client;



Client **loadClient(int *nbmax); //load tCli from file, and sort them while inserting //Done
Client readClient(FILE *file); //read client info in file // Done
int findCli(Client **tCli, int nb, char *nom, char *prenom, bool *t); //DICHOTOMIQUE //Done
Client ** newClient(Client **tCli, int *nb);
bool regexMatch(char *patt, char *str);
void rightShift(Client **tCli, int nbmax, int n); //Done
void UpdateGlobale (Client **tCli, int nb); //Done
void updateCli(Client *cli); // Done
void newSouscription(Client **tCli, int nb, int ind); //Done
void delClient(Client **tCli, int *nb); //Done
void leftShift(Client **tCli, int nb, int n); //Done
void saveClient(Client **tClient, int nb);
int cmpNomPrenom(Client c1, Client c2); //strcmp with name & surname // Done
void mailToClient(Client **tCli, int nb);


void loadEmprunt(Client **tCli, int nb, Jeu **tJeu, int nbj);
void newEmprunt(Jeu **tJeu, int nbj, Client **tCli, int nbc);
lEmprunt insEmpr(Client cli, Emprunt empr); //Done
lEmprunt supEmprtete(lEmprunt l);
lEmprunt supEmpr(lEmprunt l, char *nom, bool *t);
void delEmpr(Client **tCli, int nbc, Jeu **tJeu, int nbj);
void saveEmprunt(Client **tCli, int nb); //Done
int nbEmpr(Client cli); //Done
bool isLate(Client cli);

int findJeu(Jeu **tJeu, int nb, char *nom, bool *t);

Date getDate(); //Done

int inputFindCli(Client **tCli, int nb);
int inputFindJeu(Jeu **tJeu, int nb);
Client InputNewCliAndRetry (Client cli, int nb); //TODO regex






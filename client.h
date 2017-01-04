#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct {
	char nom[30];
	char prenom[20];
	char adresse[50];
	char ville[20];
	int codeP;
	bool paye; //1 si il a payé
	int nbEmp;
} Client;





Client readClient(FILE *file); //read client info in file // Done
int loadClient(Client **tCli); //load tCli from file, and sort them while inserting
void rightShift(Client **tCli, int nbmax, int n);

int cmpNomPrenom(Client c1, Client c2); //strcmp with name & surname // Done

int findCli(Client **tCli, int nb, char *nom, char *prenom, bool *t); //DICHOTOMIQUE
void newClient(); // Done
void updateCli(Client *cli); // Done
void leftShift(Client **tCli, int nb, int n);
void delClient(Client **tCli, int *nb, char *nom, char *prenom);
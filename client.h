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

typedef struct elemCli elemCli;
struct elemCli {
	Client client;
	elemCli *nxt;
};

typedef struct {
	elemCli *start; //pntr to the first element of the list
	elemCli *end; //pntr to the last element of the list
	int size; //nb of elements in the list
} liClient;

void initLiCli(liClient *li); //init client list
void loadLiClient(liClient *li); //load client list from file
void insTriLiCLi(liClient *li, Client cli); //insert client in sorted list
Client readClient(FILE *file); //read client info in file

int cmpNomPrenom(Client c1, Client c2); //strcmp with name & surname


void newClient(liClient *li);
void updateCli(Client client);
elemCli * findCli(liClient li, char *nom, char *prenom); //returns previous pntr (easier for delete)
void delCli();
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {false, true} bool;

typedef struct{
	int jour;
	int mois;
	int annee;
} Date;

typedef struct {
	char nom[30];
	char prenom[20];
	char adresse[50];
	char ville[20];
	int codeP;
	bool paye; //1 si il a payé
	int nbEmp;
} Client;

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

typedef struct elemCli elemCli;
typedef elemCli {
	Client client;
	elemCli *nxt;
};

typedef struct {
	elemCli *start; //pntr to the first element of the list
	elemCli *end; //pntr to the last element of the list
	int size; //nb of elements in the list
} liClient;

void printMenu(int *choix);
void Menu ();

int cmpNomPrenom(Client c1, Client c2); //strcmp with name & surname
void initLiCli(liClient *li); //init client list
Client readClient(FILE *file); //read client info in file
void insTriLiCLi(liClient *li, Client cli); //insert client in sorted list
void loadLiClient(liClient *li); //load client list from file

elemCli * findCli(liClient li, char *nom, char *prenom); //returns previous pntr (easier for delete)
void newClient(liClient *li);
void updateCli(Client client);
void delCli();
void newEmprunt(Client client, Jeu jeu);
void newAfternoon(Jeu jeu, Date date, int nbtot);
void regForAfternoon(Client client, ApresMidi apMidi);

int subDate(Date d1, Date d2);
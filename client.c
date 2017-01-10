#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "client.h"


Client readClient(FILE *file)
{
	Client cli;

	fgets(cli.nom, 20, file);
    cli.nom[strlen(cli.nom)-1] = '\0'; //nom

	fgets(cli.prenom, 20, file);
    cli.prenom[strlen(cli.prenom)-1] = '\0'; //prenom

	fgets(cli.adresse, 50, file);
    cli.adresse[strlen(cli.adresse)-1] = '\0'; //adresse

	fgets(cli.ville, 20, file);
    cli.ville[strlen(cli.ville)-1] = '\0'; //ville

	fscanf(file, "%d%*c", &(cli.codeP)); //code postal
    fscanf(file, "%d/%d/%d", &(cli.dIns.jour), &(cli.dIns.mois), &(cli.dIns.an)); //code postal

	cli.paye = true;
    cli.retard = false;
    cli.lEmpr = NULL;
	return cli;
}


Client ** loadClient(int *nbmax)
{
    int i;
    Client **tCli;
    FILE *fe;
    fe = fopen("client.don", "r");
    if (fe == NULL)
    {
        printf("can't open file\n");
        exit(1);
    }

    fscanf(fe, "%d\n", nbmax); //get nb of client in file

    tCli = (Client **)malloc(*nbmax * sizeof(Client *)); //alloc memory for array
    if (tCli == NULL)
    {
        printf("malloc tCli\n");
        exit(1);
    }

    printf("%d\n", *nbmax);
    for (i=0; i < *nbmax; i++)
    {   

        tCli[i] = (Client *)malloc(sizeof(Client)); //alloc memory for client
        if (tCli[i] == NULL)
        {
            printf("malloc tCli[i]\n");
            exit(1);
        }
        *tCli[i] = readClient(fe); //get client from file //insert client

    }

    fclose(fe);
    return tCli; //return nb of client
}

void rightShift(Client **tCli, int nbmax, int n)
{
    int i;
    for (i=nbmax; i > n; i--)
    {
        tCli[i] = tCli[i-1];
    }
}

int cmpNomPrenom(Client c1, Client c2)
{
    int j;
    for (j = 0 ; j<20 ; j++){
        c1.nom[j]=tolower(c1.nom[j]);
        c2.nom[j]=tolower(c2.nom[j]);
        c1.prenom[j]=tolower(c1.prenom[j]);
        c2.prenom[j]=tolower(c2.prenom[j]);
    }
    if (strcmp(c1.nom, c2.nom) > 0)
        return 1;
    else if(strcmp(c1.nom, c2.nom) < 0)
        return -1;

    //IF NAME ARE THE SAME
    else if (strcmp(c1.prenom, c2.prenom) > 0)
        return 1;
    else if(strcmp(c1.prenom, c2.prenom) < 0)
        return -1;
    else //if name & surname are equal
        return 0;

}







int findCli(Client **tCli, int nb, char *nom, char *prenom, bool *t) //DICHOTOMIQUE VOIR COURS 
{

    Client cli;

    strcpy(cli.nom, nom);
    strcpy(cli.prenom, prenom);

    *t = false;
    int inf = 0, sup = nb-1, m;
    while (inf <= sup)
    {
        m = (sup+inf)/2;

        if (cmpNomPrenom(cli, *tCli[m]) == 0)
        {
            *t = true;
            return m;
        }
        else if (cmpNomPrenom(cli, *tCli[m]) < 0)
            sup = m-1;
        else
            inf = m+1;

    }
    
    return inf;
}

void saveClient(Client **tClient, int nb)
{
    FILE *fe;
    int i;
    fe=fopen("client.don", "w");
    if(fe == NULL){
        printf("Erreur ouverture fichier\n");
        exit(1);
    }                         
    for(i=0; i < nb; i++)
    {
        fprintf(fe,"%s\n%s\n%s\n%s\n%d\n", tClient[i]->nom, tClient[i]->prenom, tClient[i]->adresse, tClient[i]->ville, tClient[i]->codeP);
    }
    fclose(fe);
}




Client ** newClient(Client **tCli, int *nb) 
{
    int wh;
    bool t;
    Client cli;
    char rep;
    Client **tmp;
    printf("Nom: ");
    fgets(cli.nom, 20, stdin);
    cli.nom[strlen(cli.nom)-1] = '\0'; //nom

    printf("Prenom: ");
    fgets(cli.prenom, 20, stdin);
    cli.prenom[strlen(cli.prenom)-1] = '\0'; //prenom

    printf("Adresse: ");
    fgets(cli.adresse, 50, stdin);
    cli.adresse[strlen(cli.adresse)-1] = '\0'; //adresse

    printf("Ville: ");
    fgets(cli.ville, 20, stdin);
    cli.ville[strlen(cli.ville)-1] = '\0'; //ville

    printf("Code postal: ");
    scanf("%d%*c", &(cli.codeP)); //code postal
    cli.paye = false;

    cli.lEmpr = NULL;

    wh = findCli(tCli, *nb, cli.nom, cli.prenom, &t); //find where to insert

    if (t == true) //if user exists
    {
        printf("User found, update informations ? (y/n)\n"); //ask to update
        scanf("%*c%c", &rep);
        if (rep == 'y')
        {
            updateCli(tCli[wh]);        
            return tCli;
        }
        else
            return tCli;
    }
    (*nb)++;

    tmp = (Client **)realloc(tCli, (*nb)*sizeof(Client *)); //realloc tmp to contain place for new client
    
    rightShift(tmp, *nb, wh); //shift clients 

    tmp[wh] = (Client *)malloc(sizeof(Client)); //alloc memory for new client
    if (tmp[wh] == NULL)
    {
        printf("malloc tCli[i]\n");
        exit(1);
    }

    *tmp[wh] = cli; //put new client in array
    tCli = tmp; //replace old array with new

    //saveClient(tCli, wh);

    return tCli;
}

void updateCli(Client *cli) //TODO optimiser si mauvaise saisie.
{
    char ans;
    
    printf("Update nom ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o')
    {
        printf("Nouveau nom: \n");
        fgets(cli->nom, 20, stdin);
        cli->nom[strlen(cli->nom)-1] = '\0'; //nom
    }

    printf("Update prenom ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o')
    {
        printf("Nouveau prenom: \n");
        fgets(cli->prenom, 20, stdin);
        cli->prenom[strlen(cli->prenom)-1] = '\0'; //nom
    }

    printf("Update adresse ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o')
    {
        printf("Nouvelle adresse: \n");
        fgets(cli->adresse, 50, stdin);
        cli->adresse[strlen(cli->adresse)-1] = '\0'; //nom
    }

    printf("Update code postal ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o') //if we change postal code we also change city
    {
        printf("Nouveau code postal: \n");
        scanf("%s", cli->nom);
        printf("Nouvelle ville: \n");
        scanf("%s", cli->ville);
    }

	printf("Update ville ? (o/n)\n");
	scanf("%*c%c", &ans);
	if (ans == 'o')
	{
	   printf("Nouvelle ville: \n");
	   scanf("%s", cli->ville);
	}
}

void leftShift(Client **tCli, int nb, int n) 
{
    int i;
    for (i = n; i < nb; i++)
        tCli[i] = tCli[i+1];
}

void delClient(Client **tCli, int *nb)
{
    bool t;
    int wh;
    Client **tmp, cli;

    printf("Nom: ");
    fgets(cli.nom, 30, stdin);
    cli.nom[strlen(cli.nom)-1] = '\0'; //nom

    printf("Prenom: ");
    fgets(cli.prenom, 20, stdin);
    cli.prenom[strlen(cli.prenom)-1] = '\0'; //prenom


    wh = findCli(tCli, nb, cli.nom, cli.prenom, &t);
    if (t == false)
    {
        printf("User not found\n");
        return;
    }

    leftShift(tCli, *nb, wh);
    (*nb)--;
    tmp = (Client **)realloc(tCli, (*nb)*sizeof(Client *));
    if (tmp == NULL)
    {
        printf("malloc tmpDel\n");
        exit(1);
    }

    tCli = tmp;
}



lEmprunt insEmpr(Client cli, Emprunt emprunt)
{
    MaillonE *m;
    m = (MaillonE *)malloc(sizeof(Emprunt));
    if (m == NULL)
    {
        printf("error malloc maillon emprunt\n");
        exit(1);
    }

    m->empr = emprunt;
    m->nxt = cli.lEmpr;
    return m;
}

int nbEmpr(Client cli)
{
    int nb = 0;
    while (cli.lEmpr != NULL)
    {
        cli.lEmpr = cli.lEmpr->nxt;
        nb++;
    }
    return nb;
}



void loadEmprunt(Client **tCli, int nb, Jeu **tJeu, int nbj) //TODO test
{
    FILE *fe;
    Emprunt empr;
    date d;
    char *game;
    int whC, whJ;
    bool t;
    fe=fopen("emprunts.don", "r");
    if (fe ==NULL)
    {
        printf("Issue during file oppening\n");
        exit(1);
    }


    fgets(nom, 20, fe);
    nom[strlen(nom)-1] = '\0';
    fgets(prenom, 20, fe);
    prenom[strlen(prenom)-1] = '\0';
    fscanf(fe, "%d/%d/%d", &(d.jour), &(d.mois), &(d.an));
    
    fgets(game, 100, fe);
    game[strlen(game)-1] = '\0';

    while (!feof(fe))
    {
        whC = findClient(tCli, nb, nom, prenom, &t);
        if (t == false)
        {
            printf("user not found\n");
            return;
        }
        whJ = findJeu(tJeu, nbj, game, &t);
        if (t == false)
        {
            printf("game not found\n");
            return;
        }

        empr.jeu = tJeu[whJ];
        empr.date = d;
        empr.retard = false;
        tCli[whC].lEmpr = insEmpr(tCli[whC], empr);
    }
}

lEmprunt supEmprtete(lEmprunt l)
{
    MaillonE *tmp;
    tmp = l->nxt;
    free(l);
    return tmp;
}


lEmprunt supEmpr(Lemprunt l, char *nom, bool *t)
{
    if (l == NULL)
        return l;
    if (strcmp(nom, l->jeu.nom) == 0)
        {
            *t = true;
            return supEmprtete(l);
        }
    return supEmpr(l->nxt, nom);
}

void delEmpr(Client **tCli, int nbc, Jeu **tJeu, int nbj)
{
    char *nom, *prenom, *game;
    int whJ, whC;
    bool t;
    lEmprunt tmp;

    printf("Nom: ");
    fgets(nom, 30, stdin);
    nom[strlen(nom)-1] = '\0'; //nom

    printf("Prenom: ");
    fgets(prenom, 20, stdin);
    prenom[strlen(prenom)-1] = '\0'; //prenom

    t = false;
    whC = findCli(tCli, nbc, nom, prenom, &t);
    if (t == false)
    {
        printf("User not found\n");
        return;
    }

    t = false;
    fgets(game, 100, fe);
    game[strlen(game)-1] = '\0';
    whJ = findJeu(tJeu, nbj, game, &t);
    if (t == false)
    {
        printf("Game not found\n");
        return;
    }

    t = false;
    tCli[whC]->lEmpr = supEmpr(tCli[whC]->lEmpr, game, &t);
    if (t == true)
        return;
    
    printf("You didn't rent this game\n");
}


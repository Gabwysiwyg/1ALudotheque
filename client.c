#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"


Client readClient(FILE *file)
{
	Client cli;

	fgets(cli.nom, 30, file);
    cli.nom[strlen(cli.nom)-1] = '\0'; //nom

	fgets(cli.prenom, 20, file);
    cli.prenom[strlen(cli.prenom)-1] = '\0'; //prenom

	fgets(cli.adresse, 50, file);
    cli.adresse[strlen(cli.adresse)-1] = '\0'; //adresse

	fgets(cli.ville, 20, file);
    cli.ville[strlen(cli.ville)-1] = '\0'; //ville

	fscanf(file, "%d%*c", &(cli.codeP)); //code postal

	cli.paye = 0;
	cli.nbEmp = 0;
    cli.lEmpr = NULL;
	return cli;
}


int loadClient(Client **tCli)
{
    int nbmax, i, wh;
    bool t;
    Client cli;
    FILE *fe;
    fe = fopen("client.don", "r");
    if (fe == NULL)
    {
        printf("can't open file\n");
        exit(1);
    }

    fscanf(fe, "%d%*c", &nbmax); //get nb of client in file

    tCli = (Client **)malloc(nbmax * sizeof(Client *)); //alloc memory for array
    if (tCli == NULL)
    {
        printf("malloc tCli\n");
        exit(1);
    }

    for (i=0; i < nbmax; i++)
    {   

        tCli[i] = (Client *)malloc(sizeof(Client)); //alloc memory for client
        if (tCli[i] == NULL)
        {
            printf("malloc tCli[i]\n");
            exit(1);
        }
        *tCli[i] = readClient(fe); //get client from file //insert client

    }
    printf("%s\n", tCli[0]->nom);

    fclose(fe);
    return nbmax; //return nb of client
}

void rightShift(Client **tCli, int nbmax, int n)
{
    int i;
    for (i=nbmax; i > n; i--)
    {
        tCli[i] = tCli[i-1];
    }
}

int cmpNomPrenom(Client c1, Client c2) //TODO: investigate lower case/upper case behavior
{
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
    //printf("yolo\n");
    int inf = 0, sup = nb-1, m;
    while (inf <= sup)
    {
        m = (inf+sup)/2;

        if (cmpNomPrenom(cli, *tCli[m]) == 0)
        {
            *t = true;
            return m;
        }
        if (cmpNomPrenom(cli, *tCli[m]) < 0)
            sup = m-1;
        else
            inf = m+1;
    }
    
    return inf;
}





void newClient(Client **tCli, int *nb)
{
    int wh;
    bool t;
    Client cli;
    char c;
    Client **tmp;
    printf("Nom: ");
    fgets(cli.nom, 30, stdin);
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
    scanf("%d", &(cli.codeP)); //code postal
    cli.paye = false;
    cli.nbEmp = 0;
    cli.lEmpr = NULL;

    printf("%s\n", tCli[0]->prenom);

    wh = findCli(tCli, *nb, cli.nom, cli.prenom, &t); //find where to insert
    if (t == true) //if user exists
    {
        printf("User found, update informations ? (y/n)\n"); //ask to update
        c = getchar();
        if (c == 'y')
        {
            updateCli(tCli[wh]);        
            return;
        }
        else
            return;
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

}

void updateCli(Client *cli)
{
    char ans;
    
    printf("Update nom ?");
    ans = getchar();
    if (ans == 'o')
    {
        printf("Nouveau nom: ");
        scanf("%s", cli->nom);
    }

    printf("Update prenom ?");
    ans = getchar();
    if (ans == 'o')
    {
        printf("Nouveau prenom: ");
        scanf("%s", cli->prenom);
    }

    printf("Update adresse ?");
    ans = getchar();
    if (ans == 'o')
    {
        printf("Nouvelle adresse: ");
        scanf("%s", cli->adresse);
    }

    printf("Update code postal ?");
    ans = getchar();
    if (ans == 'o') //if we change postal code we also change city
    {
        printf("Nouveau code postal: ");
        scanf("%s", cli->nom);
        printf("Nouvelle ville: ");
        scanf("%s", cli->ville);
    }
    else {
	    printf("Update ville ?");
	    ans = getchar();
	    if (ans == 'o')
	    {
	        printf("Nouvelle ville: ");
	        scanf("%s", cli->ville);
	    }
	}
}

void leftShift(Client **tCli, int nb, int n) 
{
    int i;
    for (i = n; i < nb; i++)
        tCli[i] = tCli[i+1];
}

void delClient(Client **tCli, int *nb, char *nom, char *prenom)
{
    bool t;
    int wh;
    Client **tmp;
    wh = findCli(tCli, *nb, nom, prenom, &t);
    if (t == false)
    {
        printf("user not found\n");
        return;
    }

    leftShift(tCli, *nb, wh);
    tmp = (Client **)realloc(tCli, (*nb-1)*sizeof(Client *));
    if (tmp == NULL)
    {
        printf("malloc tmpDel\n");
        exit(1);
    }

    tCli = tmp;
}



lEmprunt insEmpr(Client cli, Emprunt emprunt)
{
    Maillon *m;
    m = (Maillon *)malloc(sizeof(Emprunt));
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

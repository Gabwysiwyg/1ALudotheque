#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>
#include <math.h>
#include "client.h"




Client ** loadClient(int *nbmax) //LIT LE FICHIER ET MET LES CLIENTS DANS UN TABLEAU
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

Client readClient(FILE *file) //LIT UN CLIENT DEPUIS LE FLOT
{
    Date d = getDate();
	Client cli;

	fgets(cli.nom, 20, file);
    cli.nom[strlen(cli.nom)-1] = '\0'; //nom

	fgets(cli.prenom, 20, file);
    cli.prenom[strlen(cli.prenom)-1] = '\0'; //prenom

	fgets(cli.adresse, 50, file);
    cli.adresse[strlen(cli.adresse)-1] = '\0'; //adresse

	fgets(cli.ville, 20, file);
    cli.ville[strlen(cli.ville)-1] = '\0'; //ville

	fscanf(file, "%s%*c", cli.codeP); //code postal
    fscanf(file, "%d/%d/%d%*c", &(cli.dIns.jour), &(cli.dIns.mois), &(cli.dIns.an));
    
    if (subDate(d, cli.dIns) < -365)//on vérifie si l'abonnement est encore valide
	   cli.paye = 1;
    else
        cli.paye = 0;

    cli.retard = false;
    cli.lEmpr = NULL;
	return cli;
}

int findCli(Client **tCli, int nb, char *nom, char *prenom, bool *t) //RECHERCHE DICHOTOMIQUE
{

    Client cli;
    int cmp;
    strcpy(cli.nom, nom);
    strcpy(cli.prenom, prenom);

    *t = false;
    int inf = 0, sup = nb-1, m;
    while (inf <= sup && *t == false)
    {
        m = (sup+inf)/2;
        cmp = cmpNomPrenom(cli, *tCli[m]); //on compare noms et prénom des deux prénoms dans l'alphabet
        if (cmp == 0)
        {
            *t = true;
            return m;
        }
        else if (cmp < 0)
            sup = m-1;
        else
            inf = m+1;

    }
    
    return inf;
}

Client ** newClient(Client **tCli, int *nb) //CRÉATION D'UN CLIENT
{
    int wh;
    bool t, match = false;
    Client cli;
    char rep;
    Client **tmp;

    //regex email: ^[a-zA-Z]*@.*\\..*$

    while (match == false)
    {
        printf("Nom: \n");
        fgets(cli.nom, 20, stdin);
        cli.nom[strlen(cli.nom)-1] = '\0';

        match = regexMatch("^([a-zA-Z]*( |\\-)?)*$", cli.nom); //on vérifie si l'input correspond a cette expression régulière
    }
    match = false;
    while (match == false)
    {
        printf("Prenom: \n");
        fgets(cli.prenom, 20, stdin);
        cli.prenom[strlen(cli.prenom)-1] = '\0';

        match = regexMatch("^([a-zA-Z]*( |\\-)?)*$", cli.prenom); //on vérifie si l'input correspond a cette expression régulière
    }

    wh = findCli(tCli, *nb, cli.nom, cli.prenom, &t); //on cherche si le client existe déjà

    if (t == true) //si il existe, on propose de modifier ses infos, et on quitte
    {
        printf("User found, update data ? (o/n)\n");
        scanf("%c%*c", &rep);
        while (rep != 'o'|| rep != 'O'|| rep != 'n'|| rep != 'N')
        {
            printf("Mauvaise saisie, update data ? (o/n)\n");
            scanf("%c%*c", &rep);
        }
        if (rep == 'o' || rep == 'O')
            updateCli(tCli[wh]);

        return tCli;
    }

    match = false;
    while (match == false)
    {
        printf("Ville: \n");
        fgets(cli.ville, 20, stdin);
        cli.ville[strlen(cli.ville)-1] = '\0';

        match = regexMatch("^([a-zA-Z]*( |\\-)?)*$", cli.ville); //on vérifie si l'input correspond a cette expression régulière
    }

    printf("Adresse: \n");
    fgets(cli.adresse, 50, stdin);
    cli.adresse[strlen(cli.adresse)-1] = '\0';

    match = false;
    while (match == false)
    {
        printf("Code postal ?\n");
        scanf("%s", cli.codeP);

        match = regexMatch("^[0-9]{5}$", (char *)cli.codeP); //on vérifie si l'input correspond a cette expression régulière

        if (strcmp(cli.codeP, "98000") > 0)
            printf("Mauvaise saisie, réessayez\n");
    }

    cli.paye = 1;
    cli.lEmpr = NULL;
    cli.retard = 0;
    cli.dIns = getDate();
    
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

bool regexMatch(char *patt, char *str) //FONCTION POUR TESTER DES EXPRESSIONS RÉGULIÈRES
{
    regex_t pattern;
    int status;

    if (regcomp(&pattern, patt, REG_EXTENDED) != 0) //on compile l'expression
    {
        printf("couldn't compile regex %s\n", patt);
        exit(1);
    }

    status = regexec(&pattern, str, (size_t) 0, NULL, 0); //on teste la chaine de charactères
    regfree(&pattern);

    if (!status) //on regarde le résultat
        return true;

    //si la vérification a échouée
    printf("Mauvaise saisie, réessayez.\n");
    return false;

}


void rightShift(Client **tCli, int nbmax, int n) //DÉCALAGE A DROITE D'UN TABLEAU
{
    int i;
    for (i=nbmax; i > n; i--)
    {
        tCli[i] = tCli[i-1];
    }
}

void UpdateGlobale (Client **tCli, int nb) //MODIFICATION DES INFORMATIONS ET DE L'ABONNEMENTD'UN CLIENT
{
    char nom[20], prenom[20], rep;
    int ind;
    bool t;
    ind = inputFindCli(tCli, nb);  
    if (ind == -1)
    {
        printf("Opération annulée\n");
        return;
    }  

    printf("Voulez vous resouscrire à notre offre ? (o/n)\n");
    scanf("%c", &rep);
    while (rep != 'o'&& rep != 'O' && rep != 'n' && rep != 'N')
    {
        printf("Mauvaise saisie, voulez vous resouscrire à notre offre ? (o/n)\n");
        scanf("%*c%c", &rep);
        printf("%c\n", rep);
    }

    if (rep == 'O'|| rep == 'o')
    {
        newSouscription(tCli, nb, ind);
        printf("Done! Merci de votre fidélité!\n");
    }
    
    printf("Voulez vous modifier vos données personelles ? (o/n)\n");
    scanf("%*c%c", &rep);
    while (rep != 'o' && rep != 'O' && rep != 'n' && rep != 'N')
    {
        printf("Mauvaise saisie, réessayez (o/n)\n");
        scanf("%*c%c", &rep);
    }
    if (rep == 'O' || rep == 'o')
        updateCli(tCli[ind]);
}

void updateCli(Client *cli) //MODIFICATION DES INFORMATIONS PERSONNELLES D'UN CLIENT
{
    char ans, tmp;
    
    printf("Update nom ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {   
        scanf("%*c");
        printf("Nouveau nom: \n");
        fgets(cli->nom, 20, stdin);
        cli->nom[strlen(cli->nom)-1] = '\0'; //nom
    }

    printf("Update prenom ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
        tmp = getchar();
        printf("Nouveau prenom: \n");
        fgets(cli->prenom, 20, stdin);
        cli->prenom[strlen(cli->prenom)-1] = '\0'; //nom
    }

    printf("Update adresse ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
        tmp = getchar();
        printf("Nouvelle adresse: \n");
        fgets(cli->adresse, 50, stdin);
        cli->adresse[strlen(cli->adresse)-1] = '\0'; //nom
    }

    printf("Update code postal ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O') //if we change postal code we also change city
    {
        tmp = getchar();
        printf("Nouveau code postal: \n");
        scanf("%s", cli->codeP);
        printf("Nouvelle ville: \n");
        scanf("%s", cli->ville);
    }

    printf("Update ville ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
        tmp = getchar();
        printf("Nouvelle ville: \n");
        scanf("%s", cli->ville);
    }
}

void newSouscription(Client **tCli, int nb, int ind) //RAJOUT D'UN AN D'ABONNEMENT A UN CLIENT
{
    tCli[ind]->dIns.an+=2;
    if (tCli[ind]->paye==0)
        tCli[ind]->paye=1;
}

Client **delClient(Client **tCli, int *nb) //SUPPRESSION D'UN CLIENT (BACKEND)
{
    bool t;
    int wh;
    Client **tmp, cli;


    wh = inputFindCli(tCli, *nb);
    if (wh == -1)
    {
        printf("Opération annulée");
        return tCli;
    }

    leftShift(tCli, *nb, wh); //on décale le tableau a gauche

    (*nb)--; //on actualise le nombre d'éléments du tableau

    tmp = (Client **)realloc(tCli, (*nb)*sizeof(Client *)); //on réalloue le tableau avec une place de moins
    if (tmp == NULL)
    {
        printf("malloc tmpDel\n");
        exit(1);
    }

    tCli = tmp;
    return tCli;
}

void leftShift(Client **tCli, int nb, int n) //DÉCALAGE A GAUCHE D'UN TABLEAU
{
    int i;
    for (i = n; i < nb; i++)
        tCli[i] = tCli[i+1];
}

void saveClient(Client **tClient, int nb) //ECRITURE DU TABLEAU DANS LE FICHIER
{
    FILE *fe;
    int i;
    fe=fopen("client.don", "w");
    if(fe == NULL){
        printf("Erreur ouverture fichier\n");
        exit(1);
    }
    fprintf(fe, "%d\n", nb);                         
    for(i=0; i < nb; i++)
    {
        fprintf(fe,"%s\n%s\n%s\n%s\n%s\n%d/%d/%d\n", tClient[i]->nom, tClient[i]->prenom, tClient[i]->adresse, tClient[i]->ville, tClient[i]->codeP, tClient[i]->dIns.jour, tClient[i]->dIns.mois, tClient[i]->dIns.an);
    }
    fclose(fe);
}

int cmpNomPrenom(Client c1, Client c2) //STRCMP AVEC DEUX CHAINE DE CHARACTERES
{
    int i, j, cpt=0, cpt2=0;
    char sub1[20], sub2[20], sub3[20], sub4[20], ans;
    strcpy(sub1, c1.nom);
    strcpy(sub2, c1.prenom);
    strcpy(sub3, c2.nom);
    strcpy(sub4, c2.prenom);

    for (j = 0 ; j<21 ; j++){
        sub1[j]=toupper(sub1[j]);
        sub2[j]=toupper(sub2[j]);
        sub3[j]=toupper(sub3[j]);
        sub4[j]=toupper(sub4[j]);
    }

    for (i=0; i<20; i++)
    {
        if (sub1[i] == '\0' || sub3[i] == '\0')
            break;
        else if (sub1[i] == sub3[i])
                cpt++;
        if (sub2[i] == '\0' || sub4[i] == '\0')
            break;
        else if (sub2[i] == sub4[i])
                cpt++;
    }

    if (strcmp(sub1, sub3) == 0 && strcmp(sub2, sub4) == 0)
        return 0;

    if (cpt >= 6)
    {
        printf("Client introuvable, voulez-vous dire : %s %s ? (o/n)\n", sub3, sub4);
        scanf("%c%*c", &ans);
        if (ans == 'o' || ans == 'O')
            return 0;
    }
        

    else if (strcmp(sub1, sub3) > 0)
        return 1;

    else if (strcmp(sub1, sub3) < 0)
        return -1;

    else if (strcmp(sub2, sub4) < 0) //if family name are equal
        return -1;
    else if (strcmp(sub2, sub4) > 0)
        return 1;

    return 0;
}


void printLateCli(Client **tCli, int nb) //AFFICHAGE DES CLIENT EN RETARD
{
    int i;

    printf("Les emprenteurs ayant actuellement un retard sont: \n");
    for (i = 0; i < nb; i++){
        if (tCli[i]->retard == 1)
            printf("-%s %s\n", tCli[i]->nom, tCli[i]->prenom);
    }

}



void loadEmprunt(Client **tCli, int nb, Jeu **tJeu, int nbj) //ON CHARGE LES EMPRUNTS
{
    FILE *fe;
    Emprunt empr;
    Date d;
    char nom[20], prenom[20];
    char game[100];
    int whJ, whC, nbemp, i;
    bool t, ret;
    fe=fopen("emprunts.don", "r"); //on ouvre le fichier
    if (fe ==NULL)
    {
        printf("Issue during file oppening\n");
        exit(1);
    }

    //LECTURE DES INFOS
    fgets(nom, 20, fe);
    nom[strlen(nom)-1] = '\0';

    fgets(prenom, 20, fe);
    prenom[strlen(prenom)-1] = '\0';

    fscanf(fe, "%d/%d/%d\n", &(d.jour), &(d.mois), &(d.an));
    
    fgets(game, 100, fe);
    game[strlen(game)-1] = '\0';
    
    fscanf(fe, "%d\n", &ret);

    //FIN DE LA LECTURE    

    while (!feof(fe))
    {   

        whC = findCli(tCli, nb, nom, prenom, &t); //vérification de l'existence du client

        if (t == false)
        {
            printf("user not found\n");
            return;
        }

        whJ = findJeu(tJeu, nbj, game, &t); //vérification de l'existence du jeu

        if (t == false)
        {
            printf("game not found\n");
            return;
        }

        //Création de l'emprunt
        strcpy(empr.jeu.nom, game);
        empr.jeu.nbdisp = tJeu[whJ]->nbdisp;
        empr.jeu.nbtot= tJeu[whJ]->nbtot;
        empr.date = d;
        empr.retard = ret;

        tCli[whC]->retard = tCli[whC]->retard || ret; //on actualise la variable globale de retard du client
        tCli[whC]->lEmpr = insEmpr(*tCli[whC], empr); //on insert l'emprunt dans le client
        tJeu[whJ]->nbdisp--; //on diminue le nb dispo de ce jeu

        
        //LECTURE DES INFOS
        fgets(nom, 20, fe);
        nom[strlen(nom)-1] = '\0';

        fgets(prenom, 20, fe);
        prenom[strlen(prenom)-1] = '\0';

        fscanf(fe, "%d/%d/%d\n", &(d.jour), &(d.mois), &(d.an));
        
        fgets(game, 100, fe);
        game[strlen(game)-1] = '\0';

        fscanf(fe, "%d\n", &ret);
        //FIN DE LA LECTURE    


    }
}

void newEmprunt(Jeu **tJeu, int nbj, Client **tCli, int nbc) //CRÉATION D'UN EMPRUNT
{
    Emprunt empr;
    bool t;
    int whC, whJ;

    whC = inputFindCli(tCli, nbc); //input du client
    whJ = inputFindJeu(tJeu, nbj); //input du jeu
    if (whC == -1 || whJ == -1)
    {
        printf("Opération annulée");
        return;
    }


    if (tJeu[whJ]->nbdisp == 0) //on regarde si le jeu est disponible
    {
        printf("Ce jeu n'est plus disponible\n");
        return;
    }
    //on créé l'emprunt
    strcpy(empr.jeu.nom, tJeu[whJ]->nom);
    
    empr.date = getDate();
    empr.retard = 0;
    if (nbEmpr(*tCli[whC]) == 3) //on verifie si le client a moins de 3 emprunts en cours
    {
        printf("Vous ne pouvez plus emprunter\n");
        return;
    }
    if (tCli[whC]->paye == 0)
    {
        printf("Votre inscription a expirée\n");
        return;
    }
    tCli[whC]->lEmpr = insEmpr(*tCli[whC], empr); //on insere l'emprunt
    tJeu[whJ]->nbdisp -= 1; //ou enleve un exemplaire disponible du jeu

    printf("%s %s: %d emprunts\n", tCli[whC]->nom, tCli[whC]->prenom, nbEmpr(*tCli[whC]));
}

lEmprunt insEmpr(Client cli, Emprunt emprunt) //INSERTION EN TETE D'UN EMPRUNT DANS UNE LISTE
{
    MaillonE *m;
    m = (MaillonE *)malloc(sizeof(MaillonE)); //création du futur 1er maillon
    if (m == NULL)
    {
        printf("error malloc maillon emprunt\n");
        exit(1);
    }

    m->empr = emprunt; //on insere l'emprunt dans le maillon
    m->nxt = cli.lEmpr; //on met le maillon en tete
    return m;
}

lEmprunt supEmprtete(lEmprunt l) //SUPPRESSION DE L'EMPRUNT EN TETE
{
    MaillonE *tmp;
    tmp = l->nxt;
    free(l); //on free le 1er maillon a
    return tmp; //on return le suivant
}


lEmprunt supEmpr(lEmprunt l, char *nom, bool *t) //SUPPRESSION D'UN EMPRUNT EN RÉCURSIF (BACKEND)
{ 
    char tmp[100];
    int i;
    for (i=0; i < strlen(l->empr.jeu.nom); i++)
        tmp[i] = tolower(l->empr.jeu.nom[i]);
    tmp[i] = '\0';
    
    if (l == NULL)
        return l;
    if (strcmp(nom, tmp) == 0)
    {   
        *t = true;
        return supEmprtete(l);
    }
    return supEmpr(l->nxt, nom, t);
}

void delEmpr(Client **tCli, int nbc, Jeu **tJeu, int nbj) //SUPPRESSION D'UN EMPRUNT (FRONTEND)
{
    char tmpGame[100];
    int whJ, whC, i;
    bool t;
    lEmprunt tmp;

    whC = inputFindCli(tCli, nbc);
    whJ = inputFindJeu(tJeu, nbj);
    if (whC == -1 || whJ == -1)
    {
        printf("Opération annulée");
        return;
    }
    t = false;

    for (i=0; i < strlen(tJeu[whJ]->nom); i++)
        tmpGame[i] = tolower(tJeu[whJ]->nom[i]);
    tmpGame[i] = '\0';

    tCli[whC]->lEmpr = supEmpr(tCli[whC]->lEmpr, tmpGame, &t);
    tJeu[whJ]->nbdisp++;
    if (t == true)
    {   
        tJeu[whJ]->nbdisp++;
        tCli[whC]->retard = isLate(*tCli[whC]); //update retard global du client en fonction de ses autres emprunts
        return;
    }
    
    printf("You didn't rent this game\n");
}

void saveEmprunt(Client **tCli, int nb) //ECRITURE DU FICHIER D'EMPRUNT
{
    int i;
    FILE *fe;

    fe=fopen("emprunts.don", "w");
    if(fe == NULL){
        printf("Erreur ouverture fichier\n");
        exit(1);
    }                          

    for (i = 0; i < nb; i++)
    {
        if (tCli[i]->lEmpr != NULL) //if user has emprunts
        {
            while (tCli[i]->lEmpr != NULL)
            {
                fprintf(fe, "%s\n%s\n%d/%d/%d\n%s\n%d\n", 
                        tCli[i]->nom, tCli[i]->prenom, 
                        tCli[i]->lEmpr->empr.date.jour, tCli[i]->lEmpr->empr.date.mois, tCli[i]->lEmpr->empr.date.an,
                        tCli[i]->lEmpr->empr.jeu.nom, 
                        tCli[i]->lEmpr->empr.retard);
                        tCli[i]->lEmpr = tCli[i]->lEmpr->nxt;
            }
        }
    }
    fprintf(fe, "\nend");
    fclose(fe);
}

int nbEmpr(Client cli) //GET NOMBRE D'EMPRUNT D'UN CLIENT
{
    int nb = 0;
    while (cli.lEmpr != NULL)
    {
        cli.lEmpr = cli.lEmpr->nxt;
        nb++;
    }
    return nb;
}

bool isLate(Client cli) //RENVOIE 1 SI UN DES EMPRUNTS DU CLIENT A DU RETARD
{
    while (cli.lEmpr != NULL)
    {
        if (cli.lEmpr->empr.retard == 1)
            return true;
        cli.lEmpr = cli.lEmpr->nxt;
    }
    return false;
}




int inputFindCli(Client **tCli, int nb)
{
    char nom[20], prenom[20];
    bool t = false;
    int wh = 0;
    char c;

    while (t == false)
    {
        printf("Nom: \n");
        fgets(nom, 20, stdin);
        nom[strlen(nom)-1] = '\0';

        printf("Prenom: \n");
        fgets(prenom, 20, stdin);
        prenom[strlen(prenom)-1] = '\0';
        wh = findCli(tCli, nb, nom, prenom, &t);

        if (t == true)
            return wh;

        printf("Client non-trouvé, voulez-vous réessayer ? (o/n)\n");
        scanf("%c", &c);
        if (c == 'n')
            return -1;
    }
    return wh;

}

int inputFindJeu(Jeu **tJeu, int nb)
{
    char nom[100];
    bool t = false;
    int wh = 0;
    char c;

    while (t == false)
    {
        printf("Nom du jeu: \n");
        fgets(nom, 100, stdin);
        nom[strlen(nom)-1] = '\0';

        wh = findJeu(tJeu, nb, nom, &t);
        if (t == true)
            return wh;

        printf("Jeu non-trouvé, voulez-vous réessayer ? (o/n)\n");
        scanf("%*c%c", &c);
        if (c == 'n')
            return -1;
    }
    return wh;
}


int subDate(Date d1, Date d2)
{
    return -(365*(d1.an - d2.an) + 30*(d1.mois - d2.mois) +  d1.jour - d2.jour);
}


Date getDate()
{
    FILE *fe;
    Date d;
    system("date +%d-%m-%Y > date.don");

    fe = fopen("date.don", "r");
    if (fe == NULL)
        exit(1);
    fscanf(fe, "%d-%d-%d", &(d.jour), &(d.mois), &(d.an));
    return d;
}

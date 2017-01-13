#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>
#include "client.h"




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
    fscanf(file, "%d/%d/%d%*c", &(cli.dIns.jour), &(cli.dIns.mois), &(cli.dIns.an));

	cli.paye = true;
    cli.retard = false;
    cli.lEmpr = NULL;
	return cli;
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

Client ** newClient(Client **tCli, int *nb) 
{
    int wh;
    bool t;
    Client cli;
    char rep;
    Client **tmp;

    //InputNewCliAndRetry(cli, *nb);

    wh = findCli(tCli, *nb, cli.nom, cli.prenom, &t);

    if (t == true)
    {
        printf("User found, update data ? (o/n)\n");
        scanf("%c%*c", &rep);
        while (rep != 'o'|| rep != 'O'|| rep != 'n'|| rep != 'N')
        {
            printf("Mauvaise saisie, update data ? (o/n)\n");
            scanf("%c%*c", &rep);
        }
        if (rep == 'y' || rep == 'Y')
            updateCli(tCli[wh]);

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


void rightShift(Client **tCli, int nbmax, int n)
{
    int i;
    for (i=nbmax; i > n; i--)
    {
        tCli[i] = tCli[i-1];
    }
}

void UpdateGlobale (Client **tCli, int nb)
{
    char nom[20], prenom[20], rep;
    int ind;
    bool t;
    printf("Nom : \n");
    scanf("%s%*c", nom);
    printf("Prenom : \n");
    scanf("%s%*c", prenom);

    ind = findCli(tCli, nb, nom, prenom, &t);

    printf("Voulez vous resouscrire à notre offre ? (o/n)\n");
    scanf("%c%*c", &rep);
    while (rep != 'o'|| rep != 'O'|| rep != 'n'|| rep != 'N'){
        printf("Mauvaise saisie, voulez vous resouscrire à notre offre ? (o/n)\n");
        scanf("%c%*c", &rep);
    }

    if (rep == 'O'|| rep == 'o')
    {
        newSouscription(tCli, nb, ind);
        printf("Done! Merci de votre fidélité!\n");
    }
    
    printf("Voulez vous modifier vos données personelles ? (o/n)\n");
    scanf("%c%*c", &rep);
    while (rep != 'o' || rep != 'O'|| rep != 'n'|| rep != 'N'){
        printf("Mauvaise saisie, voulez vous resouscrire à notre offre ? (o/n)\n");
        scanf("%c%*c", &rep);
    }

    if (rep == 'O' || rep == 'o')
        updateCli(tCli[ind]);
}

void updateCli(Client *cli)
{
    char ans;
    
    printf("Update nom ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
        printf("Nouveau nom: \n");
        fgets(cli->nom, 20, stdin);
        cli->nom[strlen(cli->nom)-1] = '\0'; //nom
    }

    printf("Update prenom ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
        printf("Nouveau prenom: \n");
        fgets(cli->prenom, 20, stdin);
        cli->prenom[strlen(cli->prenom)-1] = '\0'; //nom
    }

    printf("Update adresse ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
        printf("Nouvelle adresse: \n");
        fgets(cli->adresse, 50, stdin);
        cli->adresse[strlen(cli->adresse)-1] = '\0'; //nom
    }

    printf("Update code postal ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O') //if we change postal code we also change city
    {
        printf("Nouveau code postal: \n");
        scanf("%s", cli->nom);
        printf("Nouvelle ville: \n");
        scanf("%s", cli->ville);
    }

    printf("Update ville ? (o/n)\n");
    scanf("%*c%c", &ans);
    if (ans == 'o' || ans == 'O')
    {
       printf("Nouvelle ville: \n");
       scanf("%s", cli->ville);
    }
}

void newSouscription(Client **tCli, int nb, int ind)
{
    tCli[ind]->dIns.an+=1;
    if (tCli[ind]->paye==0)
        tCli[ind]->paye=1;
}

void delClient(Client **tCli, int *nb)
{
    bool t;
    int wh;
    Client **tmp, cli;


    wh = inputFindCli(tCli, *nb);
    if (wh == -1)
    {
        printf("Opération annulée");
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

void leftShift(Client **tCli, int nb, int n) 
{
    int i;
    for (i = n; i < nb; i++)
        tCli[i] = tCli[i+1];
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
    fprintf(fe, "%d\n", nb);                         
    for(i=0; i < nb; i++)
    {
        fprintf(fe,"%s\n%s\n%s\n%s\n%d\n%d/%d/%d\n", tClient[i]->nom, tClient[i]->prenom, tClient[i]->adresse, tClient[i]->ville, tClient[i]->codeP, tClient[i]->dIns.jour, tClient[i]->dIns.mois, tClient[i]->dIns.an);
    }
    fclose(fe);
}

int cmpNomPrenom(Client c1, Client c2)
{
    int j;
    char sub1[20], sub2[20], sub3[20], sub4[20];
    strcpy(sub1, c1.nom);
    strcpy(sub2, c1.prenom);
    strcpy(sub3, c2.nom);
    strcpy(sub4, c2.prenom);

    for (j = 0 ; j<21 ; j++){
        sub1[j]=tolower(sub1[j]);
        sub2[j]=tolower(sub2[j]);
        sub3[j]=tolower(sub3[j]);
        sub4[j]=tolower(sub4[j]);
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

/*void mailToClient(Client **tCli, int nb) //TODO add email au client
{  
    int i;

    for (i=0; i<nb; i++){
        if (tCli[i]->paye == false)
            system("mailx -s \'Suscribe\' \'FROM: Gabin.salabert@laposte.net\'" + tCli[i]->email  + " < echo \'Votre inscription a expiré, vous devez payer à nouveau. Cordialement.\'");
    } 
}*/
















void loadEmprunt(Client **tCli, int nb, Jeu **tJeu, int nbj) //TODO fix game not found maybe
{
    FILE *fe;
    Emprunt empr;
    Date d;
    char nom[20], prenom[20];
    char game[100];
    int whJ, whC, nbemp, i;
    bool t, ret;
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
    fscanf(fe, "%d/%d/%d\n", &(d.jour), &(d.mois), &(d.an));
    
    fgets(game, 100, fe);
    game[strlen(game)-1] = '\0';
    fscanf(fe, "%d\n", &ret);
    

    while (!feof(fe))
    {   

        whC = findCli(tCli, nb, nom, prenom, &t);

        if (t == false)
        {
            printf("user not found\n");
            return;
        }

        whJ = findJeu(tJeu, nbj, game, &t);

        if (t == false)
        {
            printf("game not found lol\n");
            return;
        }

        strcpy(empr.jeu.nom, game);
        empr.jeu.nbdisp = tJeu[whJ]->nbdisp;
        empr.jeu.nbtot= tJeu[whJ]->nbtot;
        empr.date = d;
        empr.retard = ret;
        tCli[whC]->lEmpr = insEmpr(*tCli[whC], empr);
        printf("%s %s: %d emprunts\n",  nom, prenom, nbEmpr(*tCli[whC]));

        fgets(nom, 20, fe);
        nom[strlen(nom)-1] = '\0';
        fgets(prenom, 20, fe);
        prenom[strlen(prenom)-1] = '\0';
        fscanf(fe, "%d/%d/%d\n", &(d.jour), &(d.mois), &(d.an));
        
        fgets(game, 100, fe);
        game[strlen(game)-1] = '\0';

        fscanf(fe, "%d\n", &ret);

    }
}

void newEmprunt(Jeu **tJeu, int nbj, Client **tCli, int nbc) 
{
    Emprunt empr;
    bool t;
    int whC, whJ;

    whC = inputFindCli(tCli, nbc);
    whJ = inputFindJeu(tJeu, nbj);
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

    tCli[whC]->lEmpr = insEmpr(*tCli[whC], empr); //on insere l'emprunt
    tJeu[whJ]->nbdisp -= 1; //ou enleve un exemplaire disponible du jeu

    printf("%s %s: %d emprunts\n", tCli[whC]->nom, tCli[whC]->prenom, nbEmpr(*tCli[whC]));
}

lEmprunt insEmpr(Client cli, Emprunt emprunt)
{
    MaillonE *m;
    m = (MaillonE *)malloc(sizeof(MaillonE));
    if (m == NULL)
    {
        printf("error malloc maillon emprunt\n");
        exit(1);
    }

    m->empr = emprunt;
    m->nxt = cli.lEmpr;
    return m;
}

lEmprunt supEmprtete(lEmprunt l)
{
    MaillonE *tmp;
    tmp = l->nxt;
    free(l);
    return tmp;
}


lEmprunt supEmpr(lEmprunt l, char *nom, bool *t)
{
    if (l == NULL)
        return l;
    if (strcmp(nom, l->empr.jeu.nom) == 0)
        {
            *t = true;
            return supEmprtete(l);
        }
    return supEmpr(l->nxt, nom, t);
}

void delEmpr(Client **tCli, int nbc, Jeu **tJeu, int nbj)
{
    char *nom, *prenom, *game;
    int whJ, whC;
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
    tCli[whC]->lEmpr = supEmpr(tCli[whC]->lEmpr, game, &t);
    if (t == true)
        return;
    
    printf("You didn't rent this game\n");
}

void saveEmprunt(Client **tCli, int nb)
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
        scanf("%*c%c", &c);
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


/*Client InputNewCliAndRetry (Client cli, int nb)
{
    regex_t expr;
    int error, ind;
    bool good = false, t;
    const char *str_regex = "[:alpha:]";
    const char *str_regex2 = "![:alnum:]";
    const char *str_regex3 = "![:digit:]";
    char nom[20], prenom[20];

    printf("Nom : \n");
    fgets(cli.nom, 20, stdin);
    while (good == false)
    {
        error = regcomp (&expr, str_regex, REG_NOSUB | REG_EXTENDED); //Check (compile) si l'exp reg est valide.
        if (error == 0) // Si valide on crée variable pour analyser notre chaîne.
            int check;
        check = regexec(&expr, cli.nom, 0, NULL, 0); //Analyse.
        if (check == NO_NOMATCH) //Critères ne correspondent pas.
        { 
            printf("Mauvaise saisie, ceci n'est pas une chaîne de caractère, veuillez réessayer.\n");
            printf("Nom : \n");
            fgets(cli.nom, 20, stdin);
        }
        else{
            regfree(&expr); //libération de la mémoire.
            good = true;
        }
    }
    cli.nom[strlen(cli.nom)-1] = '\0'; 
    good = false;
    printf("Prenom : \n");
    fgets(cli.prenom, 20, stdin);
    while (good == false)
    {
        error = regcomp (&expr, str_regex, REG_NOSUB | REG_EXTENDED); //Check (compile) si l'exp reg est valide.
        if (error == 0) // Si valide on crée variable pour analyser notre chaîne.
            int check;
        check = regexec(&expr, cli.prenom, 0, NULL, 0); //Analyse.
        if (check == NO_NOMATCH){ //Critères ne correspondent pas.
            printf("Mauvaise saisie, ceci n'est pas une chaîne de caractère, veuillez réessayer.\n");
            printf("Prenom : \n");
            fgets(cli.prenom, 20, stdin);
        }
        else{
            regfree(&expr); //libération de la mémoire.
            good = true;
        }
    }
    cli.prenom[strlen(cli.prenom)-1] = '\0'; 
    good = false;

    printf("Adresse: ");
    fgets(cli.adresse, 50, stdin);
    while (good == false)
    {
        error = regcomp (&expr, str_regex2, REG_NOSUB | REG_EXTENDED); //Check (compile) si l'exp reg est valide.
        if (error == 0) // Si valide on crée variable pour analyser notre chaîne.
            int check;
        check = regexec(&expr, prenom, 0, NULL, 0); //Analyse.
        if (check == NO_NOMATCH)
        { //Critères ne correspondent pas.
            printf("Mauvaise saisie, certains caractères ne sont pas cohérents, veuillez réessayer.\n");
            printf("Adresse : \n");
            fgets(cli.adresse, 50, stdin);
        }
        else
        {
            regfree(&expr); //libération de la mémoire.
            good = true;
        }
    }
    cli.adresse[strlen(cli.adresse)-1] = '\0'; //adresse
    good = false;

    printf("Ville: ");
    fgets(cli.ville, 20, stdin);
    while (good == false){
        error = regcomp (&expr, str_regex, REG_NOSUB | REG_EXTENDED); //Check (compile) si l'exp reg est valide.
        if (error == 0) // Si valide on crée variable pour analyser notre chaîne.
            int check;
        check = regexec(&expr, prenom, 0, NULL, 0); //Analyse.
        if (check == NO_NOMATCH){ //Critères ne correspondent pas.
            printf("Mauvaise saisie, ceci n'est pas une chaîne de caractère, veuillez réessayer.\n");
            printf("Ville : \n");
            fgets(cli.ville, 20, stdin);
        }
        else{
            regfree(&expr); //libération de la mémoire.
            good = true;
        }
    }
    cli.ville[strlen(cli.ville)-1] = '\0'; //ville
    good = false;

    printf("Code postal: ");
    scanf("%d%*c", &(cli.codeP)); //code postal
    while (good = false)
    {
        if (cli.codeP < 0 || cli.codeP > 97999)
        {
            printf("Code postal inexistant, veuillez réessayer\n");
            printf("Code postal: ");
            scanf("%d%*c", &(cli.codeP));
        }
        else
            good = true;
    }
    cli.paye = false;
    cli.lEmpr = NULL;
    cli.dIns = {system("date +%d"), system("date +%m"), system("date +%Y")};
    return cli;
}*/
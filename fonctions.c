#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonctions.h"



void printMenu (int *choix)
{
	printf("\n");
	printf("*********                |Menu|                *********\n");
	printf("\n");
	printf("||||||||| 1 : Register a new member            |||||||||\n");
	printf("||||||||| 2 : Delete a member                  |||||||||\n");
	printf("||||||||| 3 : Register a loan                  |||||||||\n");
	printf("||||||||| 4 : Register a new theme afternoon   |||||||||\n");
	printf("||||||||| 5 : Register member to a theme aft.  |||||||||\n");
	printf("||||||||| 6 : Edit the game list               |||||||||\n");
	printf("||||||||| 7 : Edit list of afternoon's members |||||||||\n");
	printf("||||||||| 8 : Edit borrowers list              |||||||||\n");
	printf("||||||||| 9 : Exit                             |||||||||\n");
	printf("\n");
	printf("Please, make your choice :");
	scanf("%d", choix);
}

void Menu()
{
	int choix;

	while(1)
	{
        Menu(&choix);
        while(choix>9)
        {
            printf("Wrong choice, it's not a posibility.. Try again.\n");
            printMenu(&choix);
        }

		switch(choix)
    	{
            case 1:
                printf("\nYou've chosen to register a new member.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;
            case 2:
             	printf("\nYou've chosen to delete a member.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;
            case 3:
                printf("\nYou've chosen to register a loan.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;   
            case 4:
                printf("\nYou've chosen to register a new theme afternoon.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;
            case 5:
                printf("\nYou've chosen to register member to a theme aft.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;
            case 6:
                printf("\nYou've chosen to edit the game list.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;
            case 7:
                printf("\nYou've chosen to edit list of afternoon's members.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break; 
            case 8:
                printf("\nYou've chosen to edit borrowers list.\n");
                printf("\n");
                printf("Do you want to realize another task?\n");
                break;
            case 9:
                printf("\nYou've chosen to exit. \t");
                printf("Glad you came, see you soon!\n");
                printf("\n");
                return;  
        }
    }
}




int subDate(Date d1, Date d2)
{
    return 365*(d1.an - d2.an) + 30*(d1.mois - d2.mois) + d1.jour - d2.jour;
}


Jeu readJeu(FILE *fe)
{
    Jeu game;
    fscanf(fe, "%s\n%d %d\n", game.nom, &(game.nbdisp), &(game.nbtot));
    return game;
}

int loadGameList (Jeu **tJeu)
{
     FILE *fe;
     int i=0, nb;

    fe=fopen("gamelist.don", "r");
    if (fe ==NULL){
        printf("Issue during file oppening\n");
        exit(1);
    }

    fscanf(fe, "%d\n", &nb);
    tJeu=(Jeu **)malloc(nb*sizeof(Jeu *));
    
    if (tJeu==NULL){
        printf("Issue during allocation\n");
        exit(1);
    }

    for (i=0; i < nb; i++)
    {
        tJeu[i] = (Jeu *)malloc(sizeof(Jeu));
        if (tJeu[i] == NULL)
        {
            printf("error malloc tJeu[i]\n");
            exit(1);
        }
        *tJeu[i] = readJeu(fe);
    }

    fclose(fe);
    return nb;
}

int findJeu(Jeu **tJeu, int nb, char *nom, bool *t) //DICHOTOMIQUE VOIR COURS
{
    int inf = 0, sup = nb-1, m;
    while (inf <= sup)
    {
        m = (inf+sup)/2;
        if (strcmp(nom, tJeu[m]->nom) < 0)
            sup = m - 1;
        else
            inf = m;
    }
    if (strcmp(nom, tJeu[m]->nom) == 0)
        *t = true;
    else
        *t = false;
    return inf;
}

void newEmprunt(char *nom, char *prenom, char *game, Jeu **tJeu, int nbj, Client **tCli, int nbc)
{
    Emprunt empr;
    bool t;
    int iCli, iJeu;

    iCli = findCli(tCli, nbc, nom, prenom, &t); //on cherche le client qui veut emprunter
    if (t == false)
    {
        printf("user not found\n");
        return;
    }
    iJeu = findJeu(tJeu, nbj, game, &t); //on cherche le jeu a emprunter
    if (t == false)
    {
        printf("user not found\n");
        return;
    }
    if (tJeu[iJeu]->nbdisp == 0) //on regarde si le jeu est disponible
    {
        printf("Ce jeu n'est plus disponible\n");
        return;
    }
    //on créé l'emprunt
    empr.jeu = *tJeu[iJeu];
    empr.date.an = system("date +%Y");
    empr.date.mois = system("date +%m");
    empr.date.jour = system("date +%d");

    empr.retard = false;

    if (nbEmpr(*tCli[iCli]) == 3) //on verifie si le client a moins de 3 emprunts en cours
    {
        printf("Vous ne pouvez plus emprunter\n");
        return;
    }

    tCli[iCli]->lEmpr = insEmpr(*tCli[iCli], empr); //on insere l'emprunt
    tJeu[iJeu]->nbdisp -= 1; //ou enleve un exemplaire disponible du jeu

}

/*Afternoon * newAfternoon(Jeu jeu, Date date, Jeu tJeu[])
{

    afternoon aft;
    afternoon af[];
    int k;


    printf("Choose your game's name: \n");
    fgets(aft.jeu.nom, 40, stdin);
    aft.jeu.nom[strlen(aft.jeu.nom)-1]='\0';

    for(k=0; k<= strlen(tJeu); k++)
    if (strcmp(aft.jeu.nom, tJeu[i]->nom) == 0){
        aft.jeu.nbtot=tJeu->nbtot;
        aft.jeu.nbdisp=tJeu->nbdisp;

    printf("Choose the day :\n");
    scanf("%d", &(aft.date.jour));
    printf("choose the month :\n");
    scanf("%d", &(aft.date.mois));
    printf("Choose the year :\n");
    scanf("%d", &(aft.date.an));

    printf("Choose how many people could join this afternoon :\n");
    scanf("%d", &(aft.nbPtot));
    aft.nbPdisp=aft.nbPtot;

    af=aft;
}*/




































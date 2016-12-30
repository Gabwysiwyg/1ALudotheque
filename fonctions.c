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

Jeu * putListInTab (Jeu tJeu[])
{
     FILE *fe;
     int i=0;
     Jeu j;

    fe=fopen("gamelist.don", "r");
    if (fe ==NULL){
        printf("Issue during file oppening\n");
        exit(1);
    }

    tJeu=(Jeu *)malloc(8015*sizeof(Jeu));
    if (tJeu==NULL){
        printf("Issue during allocation\n");
        exit(1);
    }

    fgets(j.nom, 40, fe);
    j.nom[strlen(j.nom)-1] = '\0';
    scanf("%d %d", &(j.nbdisp), &(j.nbtot));

    while (!feof(fe)){
        if (i >= 8015){
            printf("Error, index exceeded\n");
            exit(1); 
        }
        tJeu[i]=j;
        i++;
        fgets(j.nom, 40, fe);
        j.nom[strlen(j.nom)-1] = '\0';
        scanf("%d %d", &(j.nbdisp), &(j.nbtot));
    }

    fclose(fe);
    return tJeu;
}

Emprunt * newEmprunt(Client client, Jeu jeu, Jeu tJeu[])
{
    Emprunt emp;
    Emprunt empr[];
    FILE *fs;
    int j;

    fs=fopen("gamelist.don", "r");
    if (fs ==NULL){
        printf("Issue during file oppening\n");
        exit(1);
    }

    printf("Nom: ");
    fgets(emp.client.nom, 30, stdin);
    emp.client.nom[strlen(emp.client.nom)-1] = '\0'; //nom

    printf("Prenom: ");
    fgets(emp.client.prenom, 20, stdin);
    emp.client.prenom[strlen(emp.client.prenom)-1] = '\0'; //prenom

    printf("Adresse: ");
    fgets(emp.client.adresse, 50, stdin);
    emp.client.adresse[strlen(emp.client.adresse)-1] = '\0'; //adresse

    printf("Ville: ");
    fgets(emp.client.ville, 20, stdin);
    emp.client.ville[strlen(emp.client.ville)-1] = '\0'; //ville

    printf("Code postal: ");
    scanf("%d", &(emp.client.codeP)); //code postal

    emp.client.paye = false;
    emp.client.nbEmp = 0;

    printf("Nom du jeu :");
    fgets(emp.jeu.nom, 40, stdin);
    emp.jeu.nom[strlen(emp.jeu.nom)-1] = '\0'; //game's name

    for(j=0; j<= 8015; j++){
        if (strcmp(emp.jeu.nom, tJeu[j]->nom) == 0){
            emp.jeu.nbtot=tJeu[j]->nbtot;
            emp.jeu.nbdisp=tJeu[j]->nbdisp;
        }
    }   
    emp.retard=0;
    empr=emp;
}

Afternoon * newAfternoon(Jeu jeu, Date date, Jeu tJeu[])
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
}




































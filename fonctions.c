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


Client readClient(FILE *file)
{
	Client cli;

	cli.nom[strlen(cli.nom)-1] = '\0'; //nom
	fgets(cli.nom, 30, file);

	cli.prenom[strlen(cli.prenom)-1] = '\0'; //prenom
	fgets(cli.prenom, 20, file);

	cli.adresse[strlen(cli.adresse)-1] = '\0'; //adresse
	fgets(cli.adresse, 50, file);

	cli.ville[strlen(cli.ville)-1] = '\0'; //ville
	fgets(cli.ville, 20, file);

	fscanf(file, "%d", &(cli.codeP)); //code postal

	cli.paye = 0;
	cli.nbEmp = 0;

	return cli;
}


void initLiCli(liClient *li)
{
    li->start = NULL;
    li->end = NULL;
    li->size = 0;
}



/*void insEndLiCli(liClient *li, Client cli)
{
    elemCli *elem;

    elem = (elemCli *)malloc(sizeof(elemCli));
    if (elem = NULL)
    {
        printf("Malloc elemCli failed\n");
        exit(1);
    }

    li->end->nxt = elem; //change pnt of last element
    li->end = elem; //change end of list
    li->size++;
}*/


int cmpNomPrenom(Client c1, Client c2)
{
    if (strcmp(c1.nom, c2.nom) < 0)
        return -1;
    else if(strcmp(c1.nom, c2.nom) > 0)
        return 1;

    //IF NAME ARE THE SAME
    else if (strcmp(c1.prenom, c2.prenom) < 0)
        return -1;
    else if(strcmp(c1.prenom, c2.prenom) > 0)
        return 1;
    else //if name & surname are equal
        return 0;

}


void insTriLiCLi(liClient *li, Client cli)
{
    int i, cmp, cmpNxt;

    elemCli *pnt; //current pos in the list
    elemCli *elem; //elem to insert

    elem = (elemCli *)malloc(sizeof(elemCli));
    if (elem = NULL)
    {
        printf("Malloc elemCli failed\n");
        exit(1);
    }

    elem->client = cli;

    if (li->size == 0) //if list is empty
    {
        li->start = elem; //set start
        li->size++;
        return;
    }



    pnt = li->start; //set pnt to beginning of the list

    while(pnt->nxt != NULL)
    {
        cmp = cmpNomPrenom(pnt->client, elem->client); //cmp name & surname with curr pos
        cmpNxt = cmpNomPrenom(pnt->nxt->client, elem->client); //cmp name & surname with next pos
        if (pnt == li->start && cmp == -1) //if we have to insert it in 1st position
        {
            elem->nxt = li->start;
            li->start = elem;
            li->size++;
            return;
        }

        if (cmp == 1 & cmpNxt == -1)
        {
            elem->nxt = pnt->nxt;
            pnt = elem;
            li->size++;
            return;
        }


        pnt = pnt->nxt;
    }

    //if we have to insert at the end
    li->end->nxt = elem; //change pnt of last element
    li->end = elem; //change end of list
    li->size++;

}



void loadLiClient(liClient *li)
{
	FILE fe;
    int nbmax, i;

	elemCli *elem;
 
	fe = fopen("client.don", "r");
	if (fe == NULL)
	{
		printf("Can't open file (clients.don)\n");
		exit(1);
	}

    fscanf(fe, "%d", &nbmax);


    for (int i=0; i < nbmax; i++)
        insTriLiCLi(&li, readClient(fe));

    return;
}
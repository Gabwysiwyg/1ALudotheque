#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main (void)
{
    //Menu();
    Client **tCli;
    int nb=0, i;
    tCli = loadClient(&nb);
    newClient(tCli, &nb);

    //newClient(tCli, &nb);

    printf("nb: %d\n", nb);
    for(i=0; i < nb; i++)
        printf("%s, %s, %s, %s, %d\n", tCli[i]->nom, tCli[i]->prenom, tCli[i]->adresse, tCli[i]->ville, tCli[i]->codeP);


    free(*tCli);
	return 0;
}
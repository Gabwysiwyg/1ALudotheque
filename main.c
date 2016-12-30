#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "client.h"

int main (void)
{
    //Menu();
    liClient li;
    elemCli *pnt;

    initLiCli(&li);
    loadLiClient(&li);
    pnt = li.start;

    while (pnt != NULL)
    {
    	printf("%s\n", pnt->client.nom);
    	pnt = pnt->nxt;
    }
    printf("\n");
    newClient(&li);
    pnt = li.start;

    while (pnt != NULL)
    {
        printf("%s  %s\n", pnt->client.nom, pnt->client.prenom);
        pnt = pnt->nxt;
    }

	return 0;
}
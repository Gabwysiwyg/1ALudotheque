#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

int main (void)
{
    //Menu();
    liClient  li;
    elemClient *pnt;

    loadLiClient(&li);
    pnt = li->start;

    while (pnt->nxt != NULL)
    {
    	printf("%s\n", pnt->client->nom);
    	pnt = pnt->nxt;
    }
	return 0;
}
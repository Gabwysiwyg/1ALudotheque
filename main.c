#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "client.h"

int main (void)
{
    //Menu();
    Client **tCli;
    int nb=0, i;

    nb = loadClient(tCli);

    newClient(tCli, nb);

    for(i=0; i < nb; i++)
        printf("%s, %s\n",tCli[i]->nom, tCli[i]->prenom);





	return 0;
}
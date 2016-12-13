#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu (char *choix)
{
	printf("\n");
	printf("\t\t\t\t\t*********               |Menu|                *********\n");
	printf("\n");
	printf("\t\t\t\t\t||||||||| 1 : Register a new member           |||||||||\n");
	printf("\t\t\t\t\t||||||||| 2 : Delete a member                 |||||||||\n");
	printf("\t\t\t\t\t||||||||| 3 : Register a loan                 |||||||||\n");
	printf("\t\t\t\t\t||||||||| 4 : Register a new theme afternoon  |||||||||\n");
	printf("\t\t\t\t\t||||||||| 5 : Register member to a theme aft. |||||||||\n");
	printf("\t\t\t\t\t||||||||| 6 : Je hais l'humanité              |||||||||\n");
	printf("\t\t\t\t\t||||||||| 7 : Je hais l'humanité              |||||||||\n");
	printf("\t\t\t\t\t||||||||| 8 : Je hais l'humanité              |||||||||\n");
	printf("\t\t\t\t\t||||||||| 9 : Exit            |||||||||\n");
	printf("\n");
	printf("Veuillez faire votre choix\n");
	scanf("%c%*c", choix);
}
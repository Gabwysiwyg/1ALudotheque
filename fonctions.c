#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu (int *choix)
{
	printf("\n");
	printf("\t\t\t\t\t*********               |Menu|                *********\n");
	printf("\n");
	printf("\t\t\t\t\t||||||||| 1 : Register a new member            |||||||||\n");
	printf("\t\t\t\t\t||||||||| 2 : Delete a member                  |||||||||\n");
	printf("\t\t\t\t\t||||||||| 3 : Register a loan                  |||||||||\n");
	printf("\t\t\t\t\t||||||||| 4 : Register a new theme afternoon   |||||||||\n");
	printf("\t\t\t\t\t||||||||| 5 : Register member to a theme aft.  |||||||||\n");
	printf("\t\t\t\t\t||||||||| 6 : Edit the game list               |||||||||\n");
	printf("\t\t\t\t\t||||||||| 7 : Edit list of afternoon's members |||||||||\n");
	printf("\t\t\t\t\t||||||||| 8 : Edit borrowers list              |||||||||\n");
	printf("\t\t\t\t\t||||||||| 9 : Exit                             |||||||||\n");
	printf("\n");
	printf("Please, make your choice :");
	scanf("%d", choix);
}
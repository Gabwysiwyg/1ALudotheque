#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <printf.h>
#include <math.h>
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>*/
#include "fonctions.h"



void printMenu (int *choix)
{
	printf("\n");
	printf("*********                |Menu|                *********\n");
	printf("\n");
	printf("||||||||| 1 : Enregistrer un nouveau membre    |||||||||\n");
	printf("||||||||| 2 : Supprimer un membre              |||||||||\n");
	printf("||||||||| 3 : Enregistrer un emprunt           |||||||||\n");
	printf("||||||||| 4 : Créer une après-midi thématique  |||||||||\n");
	printf("||||||||| 5 : Enregistrer un membre à une a.p  |||||||||\n");
	printf("||||||||| 6 : Afficher liste des jeux          |||||||||\n");
	printf("||||||||| 7 : Afficher liste des participants  |||||||||\n");
	printf("||||||||| 8 : Afficher liste des emprunts      |||||||||\n");
	printf("||||||||| 9 : Quitter                          |||||||||\n");
	printf("\n");
	printf("Veuillez faire votre choix :\t");
	scanf("%d", choix);
}

void Menu(Client **tCli, int nbc, Jeu **tJeu, int nbj, Afternoon *tAft, int nba)
{
	int choix;
    char tmp;
	while(1)
	{  
        //system("clear");
        printMenu(&choix);
        while(choix>9 || choix<1)
        {
            printf("Mauvaise saisie, veuille réessayer s'il vous plait.\n");
            printMenu(&choix);
        }

		switch(choix)
    	{
            case 1:
                printf("\nVous avez choisi d'enregister un nouveau membre.\n");
                tmp = getchar();
                printf("\n");
                tCli = newClient(tCli, &nbc);
                printf("\n");
                printf("C'est fait, merci!\n");
                break;
            case 2:
             	printf("\nVous avez choisi de supprimer un membre.\n");
                tmp = getchar();
                printf("\n");
                delClient(tCli, &nbc);
                printf("\n");
                printf("C'est fait, merci!\n");
                break;
            case 3:
                printf("\nVous avez choisi de faire un nouvel emprunt.\n");
                tmp = getchar();
                printf("\n");
                newEmprunt(tJeu, nbj, tCli, nbc);
                printf("\n");
                printf("C'est fait, merci!\n");
                break;   
            case 4:
                printf("\nVous avez choisi de créer un après midi thématique.\n");
                tmp = getchar();
                printf("\n");
                tAft=newAfternoon(tAft, &nba, tJeu, nbj);
                printf("\n");
                printf("C'est fait, merci!\n");
                break;
            case 5:
                printf("\nVous avez choisi d'inscrire un client à un après midi thématique.\n");
                tmp = getchar();
                printf("\n");
                regForAfternoon(tAft, nba, tCli, nbc);
                printf("\n");
                printf("C'est fait, merci!\n");
                break;
            case 6:
                printf("\nYou chose to edit the game list.\n");
                tmp = getchar();
                printf("\n");

                printf("\n");
                printf("Et voila le travail : \n");
                break;
            case 7:
                printf("\nYou chose to edit the list of afternoons' members.\n");
                tmp = getchar();
                printf("\n");

                printf("\n");
                printf("Et voila le travail : \n");
                break; 
            case 8:
                printf("\nYou chose to edit borrowers list.\n");
                tmp = getchar();
                printf("\n");

                printf("\n");
                printf("Et voila le travail : \n");
                break;
            case 9:
                printf("\nVous avez choisi de quitter.\n");
                printf("Au revoir!\n");
                printf("\n");
                return; 
            default:
                printf("Mauvaise saisie, veuille réessayer s'il vous plait.\n");
                break; 
        }
        
        choix = 0;
        printf("\nDo you want to realize another task ? (y/n)\n");
        scanf("%c%*c", &tmp);
        if (tmp == 'n' || tmp =='N')
        {
            printf("Okay, quitting\n");
            return;
        }
        else
            Menu(tCli, nbc, tJeu, nbj, tAft, nba);
    }
}




int subDate(Date d1, Date d2)
{
    return abs(365*(d1.an - d2.an) + 30*(d1.mois - d2.mois) + d1.jour - d2.jour);
}


Jeu readJeu(FILE *fe)
{
    Jeu game;
    fgets(game.nom, 100, fe);
    game.nom[strlen(game.nom)-1] = '\0';
    fscanf(fe, "%d %d\n", &(game.nbdisp), &(game.nbtot));
    return game;
}

Jeu **loadGameList (int *nb)
{
    FILE *fe;
    int i=0;
    Jeu **tJeu;

    fe=fopen("gamelist.don", "r");
    if (fe ==NULL){
        printf("Issue during file oppening\n");
        exit(1);
    }
    fscanf(fe, "%d\n", nb);
    tJeu=(Jeu **)malloc(*nb*sizeof(Jeu *));
    
    if (tJeu==NULL){
        printf("Issue during allocation\n");
        exit(1);
    }

    for (i=0; i < *nb-1; i++)
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
    return tJeu;
}

int findJeu(Jeu **tJeu, int nb, char *nom, bool *t) //DICHOTOMIQUE VOIR COURS //TODO PROBLEME DANS LA FONCTION!
{

    int inf = 0, sup = nb-1, m, i;

    
    while (inf <= sup)
    {
        m = (sup+inf)/2;


        if (strcmp(nom, tJeu[m]->nom) == 0)
        {
            *t = true;
            return m;
        }
        if (strcmp(nom, tJeu[m]->nom) < 0)
            sup = m-1;
        else
            inf = m+1;

    }
    *t=false;
    return inf;
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


Afternoon *loadAfternoon(int *nb, Client **tCli, int nbc)
{
    Afternoon *tAft;
    FILE *fe;
    int i, j, nbCli, wh, nba;
    char nom[20], prenom[20];
    bool t;


    fe=fopen("afternoon.don", "r");
    if (fe ==NULL){
        printf("Issue during file oppening\n");
        exit(1);
    }


    fscanf(fe, "%d\n", nb); //Get number of afternoons

    tAft = (Afternoon *)malloc(*nb * sizeof(Afternoon));
    if (tAft == NULL)
    {
        printf("problem tAft malloc\n");
        exit(1);
    }

    for (i=0; i < *nb; i++)
    {
        fgets(tAft[i].jeu.nom, 100, fe);
        tAft[i].jeu.nom[strlen(tAft[i].jeu.nom)-1] = '\0';

        fscanf(fe, "%d/%d/%d\n", &(tAft[i].date.jour), &(tAft[i].date.mois), &(tAft[i].date.an));
        fscanf(fe, "%d %d\n", &(tAft[i].nbPtot), &nbCli); //get nbPtot & nbCli
        tAft[i].nbPdisp = tAft[i].nbPtot - nbCli;

        for (j=0; j < nbCli; j++) //insert registered client 
        {
            fgets(nom, 20, fe);
            nom[strlen(nom)-1] = '\0';
            fgets(prenom, 20, fe);
            prenom[strlen(prenom)-1] = '\0';

            wh = findCli(tCli, nbc, nom, prenom, &t);

            tAft[i].lCli = insCliAft(*tCli[wh], tAft[i]);
        
        }
    }
    fclose(fe);
    return tAft;
}






Afternoon *newAfternoon(Afternoon *otAft, int *nba, Jeu **tJeu, int nb) //TODO Faire la fonction avec tab pointeurs
{

    Afternoon aft, *tAft;

    bool t = false;

    while (t == false)
    {
        printf("Enter the game's name: \n");
        fgets(aft.jeu.nom, 40, stdin);
        aft.jeu.nom[strlen(aft.jeu.nom)-1]='\0';
    
        findJeu(tJeu, nb, aft.jeu.nom, &t);
        if (t == true)
            break;
        printf("Game not found.\n");
     
    }

    printf("Choose the day :\n");
    scanf("%d", &(aft.date.jour));
    printf("choose the month :\n");
    scanf("%d", &(aft.date.mois));
    printf("Choose the year :\n");
    scanf("%d", &(aft.date.an));

    printf("Choose how many people can join this afternoon :\n");
    scanf("%d", &(aft.nbPtot));
    aft.nbPdisp=aft.nbPtot;

    tAft =(Afternoon *)realloc(otAft, (*nba+1)*sizeof(Afternoon));
    if (tAft == NULL)
    {
        printf("problem tAFt malloc\n");
        exit(1);
    }

    tAft[*nba] = aft;
    (*nba)++;
    return tAft;
}



void regForAfternoon(Afternoon tAft[], int nba, Client **tCli, int nbc)
{
    char *jeu, *nom, *prenom;
    bool t = false;
    int whC, i;  




    whC = inputFindCli(tCli, nbc);
    if (whC == -1)
    {
        printf("Opération annulée");
        return;
    }
    
    printf("Nom du jeu: \n");
    fgets(jeu, 20, stdin); //retry
    jeu[strlen(jeu)-1] = '\0';

    for (i=0; i < nba; i++)
        if (strcmp(tAft[i].jeu.nom, jeu) == 0)
        {
            t = true;
            break;
        }

    if (t == false)
    {
        printf("Il n'y a pas d'apres midi programmé pour ce jeu\n");
        return;
    }

    if (tAft[i].nbPdisp == 0)
    {
        printf("Booking is full\n");
        return;
    }

    tAft[i].lCli = insCliAft(*tCli[whC], tAft[i]);
    tAft[i].nbPdisp -= 1;
}


liCli insCliAft(Client cli, Afternoon aft)
{
    MaillonC *m;

    m = (MaillonC *)malloc(sizeof(MaillonC));

    if (m == NULL)
    {
        printf("error malloc maillon emprunt\n");
        exit(1);
    }

    m->cli = cli;

    m->nxt = aft.lCli;

    return m;
}



void saveAft(Afternoon tAft[], int nb)
{
    int i;
    FILE *fe;

    fe=fopen("afternoon.don", "w");
    if(fe == NULL){
        printf("Erreur ouverture fichier\n");
        exit(1);
    }                          
    
    fprintf(fe, "%d\n", nb);

    for (i = 0; i < nb; i++)
    {
        fprintf(fe, "%s\n%d/%d/%d\n%d %d\n", tAft[i].jeu.nom, //header for the afternoon
                tAft[i].date.jour, tAft[i].date.mois, tAft[i].date.an,
                tAft[i].nbPtot, (tAft[i].nbPtot - tAft[i].nbPdisp));

        if (tAft[i].lCli != NULL)
        {
            while (tAft[i].lCli != NULL)
            {
                fprintf(fe, "%s\n%s\n", tAft[i].lCli->cli.nom, tAft[i].lCli->cli.prenom);
                tAft[i].lCli = tAft[i].lCli->nxt;
            }
        }
    }

    fclose(fe);
}


void checkTime(Client **tCli, int nb)
{
    lEmprunt tmp;
    int i;

    Date d = getDate();

    for (i=0; i < nb; i++) //for each client
    {
        if (tCli[i]->lEmpr != NULL) //if he has emprunts
        {
            tmp = tCli[i]->lEmpr;
            while (tmp != NULL) //for each emprunt
            {
                if (subDate(d, tmp->empr.date) > 21) //if late
                {
                    tmp->empr.retard = true;
                    tCli[i]->retard = true;
                }
                tmp = tmp->nxt; //next emprunt
            }
        }

        if (subDate(d, tCli[i]->dIns) > 365) //if client outdated
            tCli[i]->paye = false; //he needs to pay again
    }
}

Date getDate()
{
    FILE *fe;
    Date d;
    system("date +%d-%m-%Y > date.don");

    fe = fopen("date.don", "r");
    if (fe == NULL)
        exit(1);
    fscanf(fe, "%d-%d-%d", &(d.jour), &(d.mois), &(d.an));
    return d;
}

char * CreatePrompt (void)
{
    char *invite = NULL;
    char const *user = getenv("USERNAME"); 

    if (user == NULL)
    {
      user = getenv("USER");
        if (user == NULL)
         user = "";
    }

    char const *host = getenv("HOSTNAME");  //Get donnée pour PATH
    if (host == NULL)
            host = "";

    char const *aux = getenv("PWD");
    if (aux == NULL)
            aux = "";
    
    char const *rep = aux + strlen(aux);
    while (rep >= aux && *rep != '/')
    {
        rep--;
    }            
    rep++;

    invite = malloc(strlen(user) + strlen(host) + strlen(rep) + 6);

    if (invite != NULL)
    {
        strcpy(invite, "[");
        strcat(invite, user);
        strcat(invite, "@");
        strcat(invite, host);
        strcat(invite, " ");        //Insert data in tab for PATH
        strcat(invite, rep);
        strcat(invite, "]");
        strcat(invite, "$");
        strcat(invite, " ");
    }
    return invite; //Return complete string
}


void Prompt (int end)
{
    while (!end)
    {
        char *s = CreatePrompt();
        if (s != NULL)
        {
            printf ("%s", s);
            fflush (stdout);
            free(s), s = NULL;
        }

        printf("\n\n\t\tBonjour et bienvenu sur le gestionnaire de Ludothèque, tapez ENTER pour continuer.\n");
        char line[128]="";
        fgets(line, sizeof line, stdin);
        end = strcmp(line, "q") == 0;
    }
}

/*int InterfGraphique(void)
{
    //Created by Gabin  Salabert on 11/01/2017.
    //Copyright © 2017 Gabin  Salabert. All rights reserved.
    //brew update && brew install sdl2

        //initialisation de la sdl
        if (SDL_Init (SDL_INIT_VIDEO) < 0)
        {   printf("erreur SDL_Init: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        atexit(SDL_Quit);
        //initialisation de la sdl_image
        if (IMG_Init(IMG_INIT_PNG) < 0)
        {   printf("erreur IMG_Init: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        atexit(IMG_Quit);
        //Initialisation de la sdl_ttf
        if( TTF_Init() == -1 )
        {
            return false;    
        }
        
        //Contexte d'affichage
        SDL_Window *screen;
        //Tampon de rendu
        SDL_Renderer *renderer;
        //Position de l'écran, de rayman et des différents sprites de rayman
        SDL_Rect pecran, prayman, pban, pbar;
        SDL_Rect raymantiles[16];
        
        unsigned int temps, tempsbride = 0, tempsanim = 0, index, anim = 0;
        bool droite = true, end = false;
        int cpt = 0;
        
        
        //initialisation des positions
        pecran.x = 0;
        pecran.y = 0;

        prayman.w = 180;
        prayman.h = 180;
        prayman.y = 250;

        pban.x = 15;
        pban.y = 15;
        pban.w = 610;
        pban.h = 80;

        pbar.w = 580;
        pbar.y = 150;
        pbar.x = 30;
        pbar.h = 80;


        for(index = 0 ; index < 6 ; index++)
        {
            raymantiles[index].x = index*60;
            raymantiles[index].y = 1100;
            raymantiles[index].w = 60;
            raymantiles[index].h = 68;
        }
        for(index = 0 ; index < 6 ; index++)
        {
            raymantiles[index+6].x = index*60;
            raymantiles[index+6].y = 68+1100;
            raymantiles[index+6].w = 60;
            raymantiles[index+6].h = 68;
        }
        for(index = 0 ; index < 4 ; index++)
        {
            raymantiles[index+12].x = index*60;
            raymantiles[index+12].y = 136+1100;
            raymantiles[index+12].w = 60;
            raymantiles[index+12].h = 68;
        }
        
        //suppression du curseur de souris
        SDL_ShowCursor(SDL_DISABLE);
        //création de la fenêtre
        screen = SDL_CreateWindow("Gestionnaire de Ludothèque", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
        //création du tampon de rendu
        renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
        //récupération de la taille de l'écran
        SDL_GetWindowSize(screen , &pecran.w , &pecran.h);

        SDL_Texture *fond2 = IMG_LoadTexture(renderer, "frame-06.gif");
        SDL_Texture *fond3 = IMG_LoadTexture(renderer, "frame-20.gif");
        SDL_Texture *fond4 = IMG_LoadTexture(renderer, "frame-28.gif");
        SDL_Texture *ban = IMG_LoadTexture(renderer, "ban.png");
        SDL_Texture *rayman = IMG_LoadTexture(renderer, "rayman.png");
        SDL_Texture *fond1 = IMG_LoadTexture(renderer, "image2.jpg");
        
        //Si erreur dans la création de la fenêtre, du tampon de rendu et des images. (fonction critiques (erreurs))
        if (screen == NULL || renderer == NULL || rayman == NULL || fond2 == NULL || fond3 == NULL || fond4 == NULL || ban == NULL || fond1 == NULL)
        {
            printf("erreur: %s\n", SDL_GetError());
            return EXIT_FAILURE;
        }
        
        //entrée en boucle principale
        while(1)
        {
            //récupération du temps
            temps = SDL_GetTicks();
            
            //si le programme tourne depuis "x" ms, on quitte;
            if (temps >= 5000) { break; }
            
            
            //test pour changer le sprite d'animation si "x" ms sont écoulées
            if (temps - tempsanim >= 60)
            {
                //sauvegarde du temps actuel pour la prochaine itération
                tempsanim = temps;
                //sprite suivant
                anim++;
                //si le dernier sprite est atteint, on reviens au premier
                if(anim == 16){anim = 0;}
            }
            
            //bride pour sinchro ecran ~60fps
            if (temps - tempsbride >= 16)
            {
                //assignation du temps actuel pour la prochaine itération
                tempsbride = temps;
                
                //si rayman touche la bordure d'écran a droite, il fait demi tour !
                if (prayman.x + prayman.w >= pecran.w){ droite = false; }

                //si il touche la bordure gauche, il fait de même.
                if (prayman.x <= 0) 
                {
                    cpt++;
                    droite = true;
                    if (cpt == 2)
                        end = true;
                }
                
                
                //vidage du tampon de rendu
                SDL_RenderClear(renderer);
                
                //copie de la banniere 
                
                //si rayman vas à gauche
                if (!droite)
                {
                    //décrémentation horizontale de la position de rayman.
                    prayman.x -= 5;
                    //copie de rayman (en inversant le sens de l'image) sur le tampon
                    SDL_RenderCopy(renderer, fond1, NULL, &pecran);
                    SDL_RenderCopy(renderer, fond3, NULL, &pbar);
                    SDL_RenderCopy(renderer, ban, NULL, &pban);
                    SDL_RenderCopyEx(renderer, rayman, &raymantiles[anim], &prayman, 0,NULL, SDL_FLIP_HORIZONTAL);  
                }
                //sinon
                else
                {
                    //incrémentation horizontale de la position de rayman.
                    prayman.x += 5;
                    //copie de rayman sur le tampon
                    SDL_RenderCopy(renderer, fond1, NULL, &pecran);
                    SDL_RenderCopy(renderer, fond2, NULL, &pbar);
                    SDL_RenderCopy(renderer, ban, NULL, &pban);
                    SDL_RenderCopy(renderer, rayman, &raymantiles[anim], &prayman);
                }

                //affichage du tampon de rendu sur l'écran.
                if (end == true){
                    SDL_RenderCopy(renderer, fond1, NULL, &pecran);
                    SDL_RenderCopy(renderer, fond4, NULL, &pbar);
                    SDL_RenderCopy(renderer, ban, NULL, &pban);
                    SDL_RenderCopy(renderer, rayman, &raymantiles[anim], &prayman);
                }
                SDL_RenderPresent(renderer);

            }
            else
            {
                // si l'écran ne suis pas, ont fait une pause.
                // cela permet de grandement libérer le CPU.
                SDL_Delay(5);
            }

        }
        SDL_Quit();
        return EXIT_SUCCESS;
    }*/

















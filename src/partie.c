/***********************************************************************************************
 * @file partie.c
 * @author MATTHEY-VINTAR Alexis (28605054 - DM Meca/EEA), PETARD Adrien (3809346 - DM Meca/EEA)
 * @brief 
 * @version 0.1
 * @date 22 - 12 - 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 ************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "safeinput.h"
#include "partie.h"
#include "SaveAndSettings.h"


// Fonctions grille

puiss4 initialisation(puiss4 *a)
{
    a -> quitPartie = 0;
    a -> resetPartie = 0;
  	
  	for(int i=0; i<nbLignes; i++){
        for(int j=0; j<nbCol; j++)
        {
        a->grille[i][j] = 0;
        }
    }
    for(int j = 0; j < nbCol; j++) a->dernier_pion[j]=0;// a.dernier_pion a autant de cases qu'il y a de colonnes 
    return *a;
}


void affiche_jeu (puiss4 jeu)
{
    printf("\n");
	for( int l = nbLignes - 1 ; l >= 0 ; l--) //on decremente, parce que dans le terminal ça s'affiche du haut vers le bas
    {
        printf( "%d - |", l + 1 ); //On affiche les numeros des lignes - 5 caracteres
      	for( int c = 0 ; c < nbCol ; c++ )
        {
          	if( jeu.grille[l][c] == PIONJ2 ) //s'il y a un pion de joueur 2, on met un x et on printf la demarcation de la colonne
            {
				printf("\033[%sm",ROUGE);
    			printf(" x");  // - 4 caracteres
				printf("\033[%sm",RESET);
				printf(" |");
            }
            else if( jeu.grille[l][c] == PIONJ1 ) //Pareil avec les pions de joueur 1
            {
				printf("\033[%sm",JAUNE);
                printf(" o");// - 4 caracteres
				printf("\033[%sm",RESET);
				printf(" |");
            }
          	else printf("   |"); //Si c'est un espace vide (ex: 0), on met juste un espace - 4 caracteres
            if( c == nbCol - 1 ) printf("\n");
        }
    }
    printf("     "); //petit espace sur la ligne d'en-dessous pour bien caler les delimitations - 5 caracteres

    for( int c = 0 ; c < nbCol ; c++ ) printf(" -  ");// - 4 caracteres

    printf("\n     "); //pareil pour les numeros des colonnes - 5 caracteres

    for ( int c = 0 ; c < nbCol ; c++ ) printf(" %d  ", c+1);// - 4 caracteres

    printf("\n");
}



int check_row(puiss4 game, int initY, int initX, int stepY, int stepX, int pionJoueur)
{
    int count = 0;
    while ( initY < nbLignes && initX < nbCol && initY >= 0 && initX >= 0 ) // Tant qu'on ne depasse pas la grille
    {
        if ( game.grille [ initY ] [ initX ] == pionJoueur ) ++count;
        else count = 0;

        if ( count >= nbPionsGagnant ) return 1;

        // Incrementation
        initY += stepY;
        initX += stepX;
    }
    return 0;
}


int gagne( puiss4 jeu, int joueur )
{ 	
  	switch( (joueur) )
    {  
        
        case 0:

            for( int i = 0; i < nbLignes; i++ ) //Iteration par lignes
            {
                if ( check_row( jeu, i, 0, 0, 1, PIONJ1 ) ) // verifie les lignes
                {
                    printf("\nVictoire par ligne.");
                    return 1;
                }
                
                if ( check_row( jeu, i, nbCol-1, 1, -1, PIONJ1 ) ) // sens backslash : moitie haute-droite de la grille
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }
                
                if ( check_row( jeu, i, 0, 1, 1, PIONJ1 ) ) // sens slash : moitie haute-gauche de la grille
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }

            }
            
            for ( int j = 0; j < nbCol; j++ ) 
            {   
                
                if ( check_row( jeu, 0, j, 1, 0, PIONJ1 ) ) // verifie les colonnes
                {
                    printf("\nVictoire par colonne.");
                    return 1;
                }

                if ( check_row( jeu, 0, j, 1, -1, PIONJ1 ) ) // sens backslash : moitie basse-gauche
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }

                if ( check_row( jeu, 0, j, 1, 1, PIONJ1 ) )// sens slash : moitie basse-droite
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }
            }
            break;
        
        case 1:
            
            for( int i = 0; i < nbLignes; i++ ) //Iteration par lignes
            {
                if ( check_row( jeu, i, 0, 0, 1, PIONJ2 ) ) // verifie les lignes
                {
                    printf("\nVictoire par ligne.");
                    return 1;
                }
                
                if ( check_row( jeu, i, nbCol-1, 1, -1, PIONJ2 ) ) // sens backslash : moitie haute-droite de la grille
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }
                
                if ( check_row( jeu, i, 0, 1, 1, PIONJ2 ) ) // sens slash : moitie haute-gauche de la grille
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }

            }
            
            for ( int j = 0; j < nbCol; j++ )
            {       
                if ( check_row( jeu, 0, j, 1, 0, PIONJ2 ) ) // verifie les colonnes
                {
                    printf("\nVictoire par colonne.");
                    return 1;
                }

                if ( check_row( jeu, 0, j, 1, -1, PIONJ2 ) ) // sens backslash : moitie basse-gauche
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }

                if ( check_row( jeu, 0, j, 1, 1, PIONJ2 ) )// sens slash : moitie basse-droite
                {
                    printf("\nVictoire par diagonale.");
                    return 1;
                }
            }
            break;
        
        default:
            exit(EXIT_FAILURE);
    }
  	return 0;
}  


puiss4 ajoute_pion(puiss4 *partiePuiss4, int joueur) 
{

  char temp1[3]; //string temporaire pour stocker l'input
  int choice;
  int pauseChoice;

    printf("\nTour n°%d\n", tour);
    if( joueur == 0 ) 
    {
        printf( "\nAu tour de %s.\n", nomJoueurUn );
    }
    else
    {
        printf("\nAu tour de %s.\n", nomJoueurDeux);
    }
    printf("\033[%sm", VERT);
    printf("Pour mettre pause, entrez la lettre p.\n\n");
    printf("\033[%sm", RESET);
    printf( "Veuillez entrer le numero de la colonne ou inserer le pion : ");

    reads ( temp1, 3 );

    //tant que: temp1 n'est pas un chiffre || temp1 est plus petit que 1 || temp1 est plus grand que le nb de colonnes || la colonne choisie est pleine
    while(  !strisnumber( temp1 ) || ( strtol ( temp1, NULL, 10 ) < 1 || strtol ( temp1, NULL, 10 ) > nbCol) || partiePuiss4->dernier_pion[ strtol ( temp1, NULL, 10 ) - 1] >= nbLignes)
    {
        if ( !strcmp( temp1, "p") )
        {
            pauseChoice = menu_pause();

            while(pauseChoice != 4)
            {
                pause(partiePuiss4, pauseChoice);
                if ( (partiePuiss4 -> quitPartie) || (partiePuiss4 -> resetPartie) ) return *partiePuiss4; 
                pauseChoice = menu_pause(); 
            }

            clear_screen();
            affiche_jeu(*partiePuiss4);
            printf("\nTour n°%d\n", tour);
            if ( joueur ) printf("\nTour de %s\n", nomJoueurDeux);
            else printf( "\nTour de %s\n", nomJoueurUn );
            printf("\033[%sm",VERT);
            printf("Pour mettre pause, entrez la lettre p.\n");
            printf("\033[%sm",RESET);
            printf( "\nVeuillez entrer le numero de la colonne ou inserer le pion : ");
        }
        else
        {
            clear_screen();
            affiche_jeu( *partiePuiss4 );
            printf("\nTour n°%d\n", tour);
            if ( joueur ) printf("\nTour de %s\n", nomJoueurUn);
            else printf("\nTour de %s\n", nomJoueurDeux);
            printf("\033[%sm",VERT);
            printf("Pour mettre pause, entrez la lettre p.\n");
            printf("\033[%sm",RESET);

            //Affichages d'erreur pour l'utilisateur
            if( strisnumber ( temp1 ) == 0 ) printf("\nCe n'est pas un chiffre ou le bouton de pause!\n"\
                                        "Veuillez entrer un chiffre correspondant a une colonne : ");//strisnumber-> Determine si une chaîne/caractere est numerique

            else if( temp1[0] == '\0' ) printf("\nIl semblerait que vous n'avez rien entre du tout\n"\
                                        "Veuillez entrer un chiffre correspondant a une colonne : ");

            else if ( strtol ( temp1 , NULL, 10 ) < 1 || strtol( temp1, NULL, 10 ) > nbCol ) printf("\nLe chiffre doit etre compris entre 1 et %d.\n"\
                                                                                        "Veuillez choisir un chiffre correspondant a une colonne : ", nbCol);

            else if ( partiePuiss4->dernier_pion[ strtol ( temp1, NULL, 10 ) - 1 ] >= nbLignes ) printf("\nLa colonne choisie est pleine.\n"\
                                                                                            "Veuillez choisir une autre colonne : ");
            
        }

        reads ( temp1, 3 );
    }

        choice = strtol ( temp1, NULL, 10 );

        if ( joueur == 0 )
        {
            partiePuiss4->grille [ partiePuiss4->dernier_pion [ choice - 1 ] ] [ choice - 1 ] = PIONJ1;
        }
        else
        {
            partiePuiss4->grille [ partiePuiss4->dernier_pion [ choice - 1 ] ] [ choice - 1 ] = PIONJ2;
        }
        
        partiePuiss4->dernier_pion [ choice - 1 ] += 1;

    return *partiePuiss4;
}

void print_main_menu_choices()
{
    puts("------------------------------------------------------------");
    puts("                    PUISSANCE 4");
    puts("------------------------------------------------------------");
	printf("\033[%sm",ROUGE);
    puts("0 - Quitter le jeu");
	printf("\033[%sm",VERT);
	puts("1 - Regles du jeu");
	puts("2 - Jouer a 2");
	puts("3 - Mode libre et paramètres du jeu"); 
    puts("4 - Charger une sauvegarde");
    puts("5 - Supprimer une sauvegarde");
    printf("\033[%sm",RESET);
}

int menu_principal(void)
{
	char choix[2];

    print_main_menu_choices();

    reads(choix, 2);
    while( strtol(choix, NULL, 10) > 5 || strtol(choix, NULL, 10) < 0 || !strisnumber(choix) || choix[0] == '\0' )
    {
        clear_screen();

        print_main_menu_choices();
        if( choix[0] == '\0' ) printf("\nIl semblerait que vous n'avez rien entre du tout\n"\
                                        "Veuillez entrer un chiffre correspondant a une colonne : ");
        else if( !strisnumber(choix) ) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
        else if( strtol(choix, NULL, 10) > 5 || strtol(choix, NULL, 10) < 0) printf("\nLe numero doit etre compris entre 0 et 6.\nVeuillez entrer un autre numero : ");
        
        reads(choix, 2);
    }
	return (int) strtol(choix, NULL, 10);
}

void print_pause_menu_choices()
{
    puts("--------------------------------");
    puts("             PAUSE              ");
    puts("--------------------------------");

    printf("\033[%sm",ROUGE);
    puts("0 - Quitter la partie");
    printf("\033[%sm",VERT);
    puts("1 - Sauvegarder");
    puts("2 - Charger une partie");
    puts("3 - Recommencer la partie");
    puts("4 - Continuer la partie");
    printf("\033[%sm",RESET);
}

int menu_pause(void)
{
	char choix[2];
    int numChoix;
    int confirmation = 0;

    while (!confirmation)
    {   
        clear_screen();
        
        print_pause_menu_choices();

        reads(choix, 2);
        while( strtol(choix, NULL, 10) > 4 || strtol(choix, NULL, 10) < 0 || !strisnumber(choix) || choix[0] == '\0')
        {   
            clear_screen();

            print_pause_menu_choices();

            if( choix[0] == '\0' ) printf("\nIl semblerait que vous n'avez rien entre du tout\n"\
                                        "Veuillez entrer un chiffre correspondant a une colonne : ");
            else if( !strisnumber(choix) ) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
            else if( strtol(choix, NULL, 10) > 6 || strtol(choix, NULL, 10) < 0) printf("\nLe numero doit etre compris entre 0 et 6.\nVeuillez entrer un autre numero : ");
            reads(choix, 2);
        }

        numChoix = strtol( choix, NULL, 10);
        if( numChoix == 0 || numChoix == 3 )
        {
            printf("\nSi vous n'avez pas sauvegarde, la partie en cours sera perdue.\n");
            confirmation = confirm_answer();
        }
        else confirmation = 1;
    }
	return numChoix;
}

void pause( puiss4 *grilleDeJeu, int userInput )
{
    int saveChoice = -1;
    int loadChoice = -1;
    switch( userInput )
    {
        case 0: // Quitter la partie
            grilleDeJeu -> quitPartie = 1;
            break;

        case 1: // Sauvegarder
            while( 1 )
            {
                saveChoice = savefile_menu("Sauvegarder :");
                if ( !saveChoice ) goto end_save_menu;
                save(*grilleDeJeu, saveChoice);
            }
            end_save_menu:
            break;
        
        case 2: // Charger une partie
            while( 1 )
            {
                loadChoice = savefile_menu("Chargement de sauvegarde:");
                if ( !loadChoice ) goto end_load_menu;
                if ( load_save( grilleDeJeu, loadChoice) ) 
                {   
                    printf("\nLa partie a ete chargee sans problemes.\nAppuyer sur 'Entree' pour continuer...");
                    flushbuff(); 
                    goto end_load_menu;
                }
            }
            end_load_menu:
            break;
        
        case 3: // Recommencer la partie
            tour = 0;
            initialisation( grilleDeJeu );
            grilleDeJeu -> resetPartie = 1;
            break;
        
        case 4: // Continuer la partie
            // Il ne se passe Rien du tout
            break;
        
        default:
            printf("\nErreur : Valeur invalide. Termination du programme...\n");
            exit(EXIT_FAILURE);
    }
}

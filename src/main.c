/***********************************************************************************************
 * @file main.c
 * @author MATTHEY-VINTAR Alexis (28605054 - DM Meca/EEA), PETARD Adrien (3809346 - DM Meca/EEA)
 * @brief 
 * @version 1.0
 * @date 14-12-2020;
 * 
 * @copyright Copyright (c) 2020;
 * 
*************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "safeinput.h"
#include "partie.h"
#include "SaveAndSettings.h"

int main()
{
	int settingsChoice = -1;
	int deleteChoice;
	int loadChoice;
    puiss4 partie ;
	while( 1 )
	{
        clear_screen();

        int choix_menu = menu_principal();
		partie.quitPartie = 0;
		settingsChoice = -1; // On initialise cett variable a une valeur qui permet d'entrer dans la boucle du case 5.

		switch( choix_menu )
        {
			case 0:
				puts("Merci et au revoir !");
				return EXIT_SUCCESS;

			case 1: // Regles de jeu
                clear_screen(); 

				couleur( ROUGE );
				printf( "Regles du jeu: \n\n" );
				couleur( RESET );
				printf("Le but du jeu est d'aligner une suite de 4 pions de meme couleur sur une grille\n"\
						"comptant 6 rangees et 7 colonnes ( reglables dans le mode libre ). Chaque joueur dispose de 21 pions, soit des croix soit des ronds.\n"\
						"Tour a tour, les deux joueurs placent un pion dans la colonne de leur choix, le pion coulisse alors\n"\
						"jusqu'a la position la plus basse possible dans la dite colonne à la suite de quoi c'est à l'adversaire de jouer.\n"\
						"Le vainqueur est le joueur qui realise le premier un alignement (horizontal, vertical ou diagonal) consecutif d'au moins quatre pions.\n"\
						"Si, alors que toutes les cases de la grille de jeu sont remplies, aucun des deux joueurs n'a realise un tel alignement, la partie est declaree nulle.\n\n"\
                        "Appuyer sur la touche 'entrer' pour continuer...");
                flushbuff();
				break;
				
			case 2: // Partie Normale		
				clear_screen();

				set_default_settings();

				player_name_change();

                clear_screen();

    			initialisation( &partie );
				tour = 0;
				
				affiche_jeu( partie );

    			for( tour += 0; tour < (nbCol*nbLignes); tour++ )
    			{        

        			ajoute_pion( &partie, ( (tour) % 2 ) );

					if( partie.resetPartie ) // Si la partie est recommencee, le joueur 1 (puisque tour est remis à zero) joue tout de suite
					{	
						clear_screen();
						affiche_jeu( partie );
						ajoute_pion( &partie, tour%2 );
						partie.resetPartie = 0;
					}

					if ( partie.quitPartie ) break; // Check si l'option 'quitter' du menu pause a ete choisi
                    
                    clear_screen();
        			affiche_jeu( partie );

                    if ( gagne( partie, tour % 2) )
					{	
						if ( tour % 2 ) printf("\n%s a gagne !", nomJoueurDeux);
						else printf ("\n%s a gagne !", nomJoueurUn);
						printf("\n\nAppuyer sur entree pour continuer...");
						flushbuff();
						break;
					}
    			}

				if ( tour == (nbCol*nbLignes) )
				{
					printf("\nMatch Nul !\n\nAppuyer sur 'Entree' pour continuer...");
					flushbuff();
				}

    			break;
				
			case 3: // Partie Libre

				while( settingsChoice != 3)
				{	
					clear_screen();
					settingsChoice = settings_menu();
					settings( settingsChoice );
				}

				clear_screen();

    			initialisation( &partie );
				tour = 0;

				affiche_jeu( partie );

    			for( tour += 0; tour < (nbCol*nbLignes); tour++ )
    			{        
                    
        			ajoute_pion( &partie, ( (tour) % 2 ) );

					if( partie.resetPartie )
					{
						clear_screen();
						affiche_jeu( partie );
						ajoute_pion( &partie, tour%2 );
						partie.resetPartie = 0;
					}

					if ( partie.quitPartie ) break;
                    
                    clear_screen();
        			affiche_jeu( partie );

                    if ( gagne( partie, tour % 2) )
					{	
						if ( tour % 2 ) printf("\n%s a gagne !", nomJoueurDeux);
						else printf ("\n%s a gagne !", nomJoueurUn);
						printf("\n\nAppuyer sur entree pour continuer...");
						flushbuff();
						break;
					}
    			}

				if ( tour == (nbCol*nbLignes) )
				{
					printf("\nMatch Nul !\n\nAppuyer sur 'Entree' pour continuer...");
					flushbuff();
				}

                break;

				case 4: // Charger une sauvegarde

					while ( 1 )
					{
						loadChoice = savefile_menu("Charger une sauvegarde :");

						if ( !loadChoice ) goto end_main_case_4;

						if ( load_save( &partie, loadChoice ) )
						{
							printf("\nLa partie a ete chargee sans problemes.\nAppuyer sur 'Entree' pour continuer...");
							flushbuff();
							break;
						}
					}
					
					clear_screen();
					affiche_jeu( partie );

		 			for( tour += 0; tour < (nbCol*nbLignes); tour++ )
					{        

						ajoute_pion( &partie, ( (tour) % 2 ) );

						if( partie.resetPartie )
						{	
							clear_screen();
							affiche_jeu( partie );
							ajoute_pion( &partie, tour%2 );
							partie.resetPartie = 0;
						}

						if ( partie.quitPartie ) break; // Check si l'option 'quitter' du menu pause a ete choisi
						
						clear_screen();
						affiche_jeu( partie );

						if ( gagne( partie, tour % 2) )
						{	
							if ( tour % 2 ) printf("\n%s a gagne !", nomJoueurDeux);
							else printf ("\n%s a gagne !", nomJoueurUn);
							printf("\n\nAppuyer sur 'Entree' pour continuer...");
							flushbuff();
							break;
						}
					}

					if ( tour == (nbCol*nbLignes) )
					{
						printf("\nMatch Nul !\n\nAppuyer sur 'Entree' pour conitnuer...");
						flushbuff();
					}

					end_main_case_4:
					break;

				case 5: // Supprimer une sauvegarde
					while( 1 )
					{
						deleteChoice = savefile_menu("Supprimer une Sauvegarde :");
						if ( !deleteChoice ) goto end_main_case_5;

						if ( del_save( deleteChoice ) )
						{
							printf("\nSauvegarde supprimee\nAppuyer sur 'Entree' pour continuer...");
							flushbuff();
						}
					}
					end_main_case_5:
					break;

				
         	default:
				printf("\nErreur : Valeur invalide. Termination du programme...\n");
            	exit( EXIT_FAILURE );
		}
	}
	return EXIT_SUCCESS;
}

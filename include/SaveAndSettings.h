/***********************************************************************************************
 * @file SaveAndSettings.h
 * @author MATTHEY-VINTAR Alexis (28605054 - DM Meca/EEA), PETARD Adrien (3809346 - DM Meca/EEA)
 * @brief 
 * @version 0.1
 * @date 22 - 12 - 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 ************************************************************************************************/

#ifndef SAVEANDSETTINGS_H
#define SAVEANDSETTINGS_H

#include "partie.h"


#define NB_LIGNE_MAX 20
#define NB_COL_MAX 20
#define NB_LIGNE_MIN 3
#define NB_COL_MIN 3

#define NB_PIONS_WIN_MIN 3

#define NOM_J1_DEFAUT "Joueur1"
#define NOM_J2_DEFAUT "Joueur2"

#define NB_LIGNE_DEFAUT 6
#define NB_COL_DEFAUT 7
#define NB_PIONS_WIN_DEFAULT 4

#define PLAYER_NAME_SIZE 15

#define SAVE_SLOT_ONE "savefiles/save1.SAV"
#define SAVE_SLOT_TWO "savefiles/save2.SAV"
#define SAVE_SLOT_THREE "savefiles/save3.SAV"

#include "puiss4struct.h"

// Definition variables globales

extern int nbCol;
extern int nbLignes;
extern int nbPionsGagnant;
extern int tour;
extern char nomJoueurUn[PLAYER_NAME_SIZE], nomJoueurDeux[PLAYER_NAME_SIZE];

// Definition fonctions

/**
 * @brief Fonction qui s'adapte à l'OS (Uniquement Windows et Linux) pour appeler une commande de terminal qui enleve tout ce qu'il y a sur l'ecran du terminal
 * 
 */
void clear_screen();

/**
 * @brief permet a l'utilisateur de confirmer sa reponse. 
 * Renvoie 1 si l'utilisateur a bien confirme, 0 sinon.
 * 
 * @return int 
 */
int confirm_answer();

/**
 * @brief Renvoie un struct tm (venant de time.h) contenant la date et l'heure au moment de l'appel de la fonction
 * 
 * @return struct tm
*/
struct tm get_date();

/**
 * @brief Renvoie le plus petit nombre entre a et b.
 * 
 * @param a un entier quelconque
 * @param b un entier quelconque
 * @return int 
 */
int min(int a, int b);

/**
 * @brief Permet aux utilisateurs d'entrer leurs prenoms dans les variables globales nomJoueurUn et nomJoueurDeux.
 * 
 */
void player_name_change();

/**
 * @brief Affiche les choix disponibles dans la fonction settings_menu();
 * 
 */
void print_settings_choices();

/**
 * @brief Affiche de menu des reglages d'une partie libre
 * Renvoie le nombre correspondant a ce que l'utilisateur a choisi 
 * 
 * @return int 
 */
int settings_menu();

/**
 * @brief effectue l'action demandee par l'utilisateur dans le menu des reglages de partie libre
 * * note : Modifie les variables globales
 * 
 * @param settingsChoice is the value that the user chose in settings_menu()
 */
void settings( int settingsChoice);

/**
 * @brief Set the default settings for the game
 * * note : Modifies the global variables
 * 
 */
void set_default_settings();

/**
 * @brief Display the details of the chosen savefile
 * 
 * @param saveNumber selects the savefile number (from 1 to 3)
 */
void savefile_display(int saveNumber);

/**
 * @brief affiche les choix dans la fonction savefile_menu
 * 
 */
void print_savefiles_choices();

/**
 * @brief Affiche les liste des sauvegardes et renvoie le choix de l'utilisateur
 * Si savefile_menu renvoie 0, cela veut dire que l'utilisateur veut retourner a l'ecran precedent
 * si ce que savefile_menu envoie est compris entre 1 et 3, ca veut dire que l'utilisateur a choisi un fichier de sauvegarde
 * 
 * @param menuType est une chaine de caractere qui indique la fonction qui va etre effectue si on choisit un fichier
 * @return int 
 */
int savefile_menu( const char *menuType );

/**
 * @brief ecris dans un fichier de sauvegarde les details de la partie qui se deroule
 * *un fichier de sauvegarde est organise de la maniere suivante :
 * *ligne 1 : Nom du joueur 1 actuel
 * *ligne 2 : Nom du joueur 2 actuel
 * *lignes 3-5 : respectivement, jour du mois/mois/annee/heure de la journee/minute
 * *ligne 6 : nombre du tour de jeu actuel
 * *ligne 7 : nbLignes (parametre de nombre de lignes)
 * *ligne 8 : nbCol (parametre de nombre de colonnes)
 * *ligne 9 : nbPionsGagnant (parametre de nombres de pions a aligner)
 * *lignes 10 - (nbLignes*nbCol) : valeurs des cases de la grille de jeu
 * *lignes (nbLignes*nbCol + 1) - (nbLignes*nbCol+1 + nbCol) : variables dernierpion du struct puiss4
 * 
 * @param destFile pointeur sur le fichier de sauvegarde choisi
 * @param savedGame struct puiss4 de la partie se deroulant 
 * @return int 
 */
int write_savefile(const char *fileName, puiss4 savedGame);

/**
 * @brief verifie que le fichier de sauvegarde choisi est plein, 
 * et permet a l'utilisateur de confirmer l'ecrasement de la sauvegarde si c'est le cas
 * 
 * @param fileName chemin relatif du fichier de sauvegarde
 * @param currentGame struct puiss4 de la partie se deroulant 
 * @return int 
 */
int overwrite_file(const char *fileName, puiss4 currentGame);

/**
 * @brief selectionne la sauvegarde que l'utilisateur a choisi pour pour pouvoir sauvegarder ou non. 
 * Renvoie 1 si une sauvegarde a ete effectuee, renvoie 0 sinon.
 * 
 * @param game 
 * @param saveSlot
 * @return int 
 */
int save(puiss4 game, int saveSlot);

/**
 * @brief supprime le contenu du fichier de sauvegarde choisi. L'utilisateur doit confirmer.
 * Renvoie 1 si le contenu a ete supprime, 0 sinon
 * 
 * @param saveSlot numero du fichier de sauvegarde choisi
 * @return int 
 */
int del_save( int saveSlot );

/**
 * @brief charge de le contenu de la sauvegarde sur le struct puiss4 et les variables globales
 * Renvoie 1 si la charge s'est effectuee correctement, 0 sinon
 * 
 * @param saveSlot numero de la sauvegarde choisie
 * @param destGrid
 * @return int 
 */
int load_save( puiss4 *destGrid, int saveSlot );

#endif

/***********************************************************************************************
 * @file partie.h
 * @author MATTHEY-VINTAR Alexis (28605054 - DM Meca/EEA), PETARD Adrien (3809346 - DM Meca/EEA)
 * @brief 
 * @version 0.1
 * @date 22 - 12 - 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 ************************************************************************************************/

#ifndef PARTIE_H
#define PARTIE_H

#include "SaveAndSettings.h"
#include "puiss4struct.h"

#define PIONJ1 1
#define PIONJ2 -1

#ifndef COULEURS
#define COULEURS
#define NOIR "30"
#define ROUGE "31"
#define VERT "32"
#define JAUNE "33"
#define BLEU "34"
#define MAGENTA "35"
#define CYAN "36"
#define BLANC "37"
#define RESET "0"
#define couleur(param) printf("\033[%sm",param)
#endif




// Signatures fonctions

/**
 * @brief cree un puiss4 avec grille1, grille2 et dernier_pion remplis de 0
 * 
 * @return puiss4 
 */
puiss4 initialisation(puiss4 *a);

/**
 * @brief affiche la grille de jeu dans le terminal
 * 
 * @param jeu est la variable de type puiss4
 */
void affiche_jeu (puiss4 jeu);

/**
 * @brief Ajout d'une case remplie dans la grille du joueur correspondant
 *
 * @param jeu (puiss4)
 * @param joueur (int) -> 0 correspond au tour premier joueur, 1 correspond tour au deuxieme joueur
 * @return puiss4
 */
puiss4 ajoute_pion(puiss4 *partiePuiss4, int joueur);

/**
 * @brief fait une iteration sur une ligne, colonne ou diagonale (selon les valeurs stepY et stepX) 
 * a partir de la case de depart ( definie par initY et initX)
 * 
 * @param game est la grille de jeu
 * @param initY = la ligne de depart
 * @param initX = la colonne de depart
 * @param stepY = le pas de l'iteration sur les lignes
 * @param stepX = le pas de l'iteration sur les colonnes
 * @param pionJoueur = la valeur du pion à checker
 * @return int 
 */
int check_row(puiss4 game, int initY, int initX, int stepY, int stepX, int pionJoueur);

/**
 * @brief verifie si un joueur a gagne la partie ou non
 * 
 * @param jeu (puiss4)
 * @param joueur (int) -> 0 correspond au tour du premier joueur, 1 correspond au tour du deuxieme joueur
 * @return int 
 */
int gagne( puiss4 jeu, int joueur );

/**
 * @brief Affiche les choix disponibles dans le menu principal
 * 
 */
void print_main_menu_choices();

/**
 * @brief affiche le menu principal et retourne le choix de l'utilisateur
 * 
 * @return int 
 */
int menu_principal(void);

/**
 * @brief Affiche les choix disponibles dans le menu pause
 * 
 */
void print_pause_menu_choices();

/**
 * @brief affiche le menu pause lors d'une partie et retourne le choix de l'utilisateur
 * 
 * @return int 
 */
int menu_pause(void);

/**
 * @brief effectue l'action choisie par l'utilisateur dans le menu pause
 * 
 * @param grilleDeJeu est le struct puiss4 utilise dans le main
 * @param userInput est le choix de l'utilisateur
 */
void pause( puiss4 *grilleDeJeu, int userInput );

#endif
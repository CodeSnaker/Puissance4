/***********************************************************************************************
 * @file SaveAndSettings.c
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
#include <string.h>
#include <time.h>
#include "safeinput.h"
#include "partie.h"
#include "SaveAndSettings.h"

int nbLignes = NB_LIGNE_DEFAUT;
int nbCol = NB_COL_DEFAUT;
int nbPionsGagnant = NB_PIONS_WIN_DEFAULT;
int tour = 0;
char nomJoueurUn[PLAYER_NAME_SIZE] = "Joueur1", nomJoueurDeux[PLAYER_NAME_SIZE] = "Joueur2";



void clear_screen()
{
    #ifdef _WIN32

    system("cls");

    #endif

    #ifdef __linux__

    system("clear");

    #endif
}
int confirm_answer()
{
    char confirm[2];
    int numConfirm = 0;

    printf( "Etes-vous sur de votre choix ?\n0 - Non\n1 - Oui\n");
    reads(confirm, 2);

        while( strtol(confirm, NULL, 10) > 1 || strtol(confirm, NULL, 10) < 0 || !strisnumber( confirm ))
        {   
            couleur(ROUGE);
            printf( "Etes-vous sur de votre choix ?\n0 - Non\n1 - Oui\n");
            couleur(RESET);

            if( !strisnumber(confirm) ) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
            else if( strtol(confirm, NULL, 10) > 1 || strtol(confirm, NULL, 10) < 0) printf("\nLe numero doit etre compris entre 0 et 1.\nVeuillez entrer un autre numero : ");
            reads(confirm, 2);
        }

    numConfirm = strtol(confirm, NULL, 10);

    return numConfirm;
}

struct tm get_date()
{
    time_t rawTime;

    struct tm *brokenDate = NULL;

    time(&rawTime);

    brokenDate = localtime( &rawTime );

    brokenDate -> tm_year += 1900;
    ++(brokenDate -> tm_mon);

    return *brokenDate;
}

int min(int a, int b)
{
    if (a < b) return a;
    else return b;
}

void player_name_change()
{   

    int confirmation = 0;

    while (!confirmation)
    {   
        clear_screen();
        printf("\nEntrez le nom du Joueur 1: ");
        reads(nomJoueurUn, PLAYER_NAME_SIZE);
        printf("\nEntrez le nom du Joueur 2: ");
        reads(nomJoueurDeux, PLAYER_NAME_SIZE);

        printf("\n\n");
        confirmation = confirm_answer();  
    }

}

int settings_menu()
{
    char choix[2];
    int numChoix;
    int confirmation = 0;

    while(!confirmation)
    {

        puts("--------------------------------");
        puts("            SETTINGS            ");
        puts("--------------------------------");

        couleur(ROUGE);
        printf("0 - Retour\n");
        couleur(VERT);
        printf("1 - Changer le nombre de lignes (Nombre de lignes actuel : %d)\n", nbLignes);
        printf("2 - Changer le nombre de colonnes (Nombre de colonnes actuel : %d)\n", nbCol);
        printf("3 - Changer le nombre de pions a aligner pour gagner (Nombre actuel : %d)\n", nbPionsGagnant);

        printf("4 - Changer le nom des joueurs ( ");
        couleur(JAUNE);
        printf("Joueur 1 actuel : %s ", nomJoueurUn);
        couleur(VERT);
        printf(";");
        couleur(ROUGE);
        printf(" Joueur 2 actuel : %s", nomJoueurDeux);
        couleur(VERT);
        printf(" )\n");
        
        printf("5 - Mettre les reglages par defaut\n");
        printf("6 - Lancer la partie\n");
        couleur(RESET);

        reads(choix, 2);
        while( strtol(choix, NULL, 10) > 6 || strtol(choix, NULL, 10) < 0 || !isdigit(choix[0]))
        {   
            clear_screen();

            puts("--------------------------------");
            puts("            SETTINGS            ");
            puts("--------------------------------");


            couleur(ROUGE);
            printf("0 - Retour\n");
            couleur(VERT);
            printf("1 - Changer le nombre de lignes (Nombre de lignes actuel : %d)\n", nbLignes);
            printf("2 - Changer le nombre de colonnes (Nombre de colonnes actuel : %d)\n", nbCol);
            printf("3 - Changer le nombre de pions a aligner pour gagner (Nombre actuel : %d)\n", nbPionsGagnant);

            printf("4 - Changer le nom des joueurs ( ");
            couleur(JAUNE);
            printf("Joueur 1 actuel : %s ", nomJoueurUn);
            couleur(VERT);
            printf(";");
            couleur(ROUGE);
            printf(" Joueur 2 actuel : %s", nomJoueurDeux);
            couleur(VERT);
            printf(" )\n");

            printf("5 - Mettre les reglages par defaut\n");
            printf("6 - Lancer la partie\n");
            couleur(RESET);

            if( !strisnumber(choix) ) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
            else if( strtol(choix, NULL, 10) > 6 || strtol(choix, NULL, 10) < 0) printf("\nLe numero doit etre compris entre 0 et 5.\nVeuillez entrer un autre numero : ");
            reads(choix, 2);
            }

            numChoix = strtol( choix, NULL, 10);

        if( numChoix == 5 || numChoix == 6 )
        {
            confirmation = confirm_answer();
        }
        else confirmation= 1;
    }

    return numChoix;
}

void settings( int settingsChoice)
{   
    char tempBuffer[3];

    switch (settingsChoice)
    {
        case 1: // Modifier le nombre de lignes
            
            printf("\n\nVeuillez entrer un nombre compris entre %d et %d : ", NB_LIGNE_MIN, NB_LIGNE_MAX);

            reads(tempBuffer, 3);
            while( strtol(tempBuffer, NULL, 10) > NB_LIGNE_MAX || strtol(tempBuffer, NULL, 10) < NB_LIGNE_MIN || !strisnumber(tempBuffer))
            {
                if( !strisnumber( tempBuffer )) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
                else if( strtol(tempBuffer, NULL, 10) > NB_LIGNE_MAX || strtol(tempBuffer, NULL, 10) < NB_LIGNE_MIN) printf("\nLe numero doit etre compris entre %d et %d.\nVeuillez entrer un autre numero : ", NB_LIGNE_MIN, NB_LIGNE_MAX);
                
                reads( tempBuffer, 3);
            }

            nbLignes = strtol(tempBuffer, NULL, 10);

            if ( nbPionsGagnant > min (nbLignes, nbCol))
            {
                nbPionsGagnant = min (nbLignes, nbCol);
                printf("\n Le nombre de pions a aligner a ete change en consequence.\nAppuyer sur entree pour continuer...");
                flushbuff();
            }

            break;
        
        case 2: // Modifier le nombre de colonnes

            printf("\n\nVeuillez entrer un nombre compris entre %d et %d : ", NB_COL_MIN, NB_COL_MAX);

            reads(tempBuffer, 3);
            while( strtol(tempBuffer, NULL, 10) > NB_COL_MAX || strtol(tempBuffer, NULL, 10) < NB_COL_MIN || !strisnumber(tempBuffer))
            {   
                if( !strisnumber( tempBuffer )) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
                else if( strtol(tempBuffer, NULL, 10) > NB_COL_MAX || strtol(tempBuffer, NULL, 10) < NB_COL_MIN ) printf("\nLe numero doit etre compris entre %d et %d.\nVeuillez entrer un autre numero : ", NB_COL_MIN, NB_COL_MAX );
                
                reads( tempBuffer, 3);
            }

            nbCol = strtol(tempBuffer, NULL, 10);

            if ( nbPionsGagnant > min (nbLignes, nbCol))
            {
                nbPionsGagnant = min (nbLignes, nbCol);
                printf("\n Le nombre de pions a aligner a ete change en consequence.\nAppuyer sur entree pour continuer...");
                flushbuff();
            }

            break;

        case 3: // modifier le nombre de pions a aligner

            printf("Veuillez entrer un nombre compris entre %d et %d ( max delimite par les nombres de colonnes et de lignes) : ", NB_PIONS_WIN_MIN, min( nbLignes, nbCol ));

            reads(tempBuffer, 3);
            while( strtol(tempBuffer, NULL, 10) > min(nbLignes, nbCol)  || strtol(tempBuffer, NULL, 10) < NB_PIONS_WIN_MIN|| !strisnumber(tempBuffer))
            {   
                if( !strisnumber( tempBuffer )) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
                else if( strtol(tempBuffer, NULL, 10) > min(nbLignes, nbCol) || strtol(tempBuffer, NULL, 10) < NB_PIONS_WIN_MIN ) printf("\nLe numero doit etre compris entre %d et %d.\nVeuillez entrer un autre numero : ", NB_PIONS_WIN_MIN, min( nbLignes, nbCol ) );
                
                reads( tempBuffer, 3);
            }

            nbPionsGagnant = strtol(tempBuffer, NULL, 10);

            break;
        
        case 4: // modifier le nom des joueurs
            player_name_change();
            break;

        case 5: // mettre les reglages par defaut
            set_default_settings();
            break;

        default:
            break;
    }
}

void set_default_settings()
{
    nbLignes = NB_LIGNE_DEFAUT;
    nbCol = NB_COL_DEFAUT;
    nbPionsGagnant = NB_PIONS_WIN_DEFAULT;  

    strcpy(nomJoueurUn, NOM_J1_DEFAUT);
    strcpy(nomJoueurDeux, NOM_J2_DEFAUT);
}

void savefile_display(int saveNumber)
{   
    char tempBuffer[25];
    char filePath[25];

    FILE *fileToRead = NULL;

    snprintf( filePath, 25, "savefiles/save%d.SAV", saveNumber );

    fileToRead = fopen ( filePath, "a+"); // on utilise le mode a+ pour ne pas ecraser le file, que ça puisse en creer un s'il n'existe pas, et qu'on puisse lire et ecrire dans le file 

    if ( fileToRead == NULL ) 
    {
        printf("Erreur : ouverture du fichier impossible.\nLa sauvegarde n'a pas pu etre affichee.\n");
        fclose (fileToRead);
        return;
    }

    else if ( fseek( fileToRead, 0, SEEK_END) ) // en soit, ce n'est pas obliger de mettre cette commande parce qu'on est en mode a+ (donc le curseur est deja a la fin), mais c'est juste pour etre sur
    {
        printf( "\nErreur : le curseur n'a pas pu etre place a la fin du fichier.\nLa sauvegarde n'a pas pu etre affichee.\n" );
        fclose(fileToRead);
        return;
    }

    if ( ftell( fileToRead ) == 0 ) 
    {
        printf ("Empty Save.\n");
    }
    else
    {
        if ( fseek( fileToRead, 0, SEEK_SET ) ) 
        {
            printf( "\nErreur : le curseur n'a pas pu etre place au debut du fichier.\nLa sauvegarde n'a pas pu etre affichee.\n" );
            fclose(fileToRead);
            return;
        }

        //Affichage des joueurs
        readfile(tempBuffer, 25, fileToRead);
        printf("%s vs ", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("%s\n", tempBuffer);

        //Affichage de la date
        readfile(tempBuffer, 25, fileToRead);
        printf("    Date = %s/", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("%s/", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("%s  ", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("Heure = %s:", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("%s\n", tempBuffer);

        readfile(tempBuffer, 25, fileToRead);
        printf("    Tour = %s\n", tempBuffer);        

        // Affichage des parametres de jeu
        readfile(tempBuffer, 25, fileToRead);
        printf("    Nombre de lignes = %s\n", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("    Nombre de colonnes = %s\n", tempBuffer);
        readfile(tempBuffer, 25, fileToRead);
        printf("    Nombre de pions a aligner = %s\n\n", tempBuffer);
    }

    fclose(fileToRead);

}


int savefile_menu(const char *menuType)
{
    clear_screen();

    char choix[2];
    int numChoix;

    printf("%s\n", menuType);
    puts("-----------------------------------------------");
    puts("            FICHIERS DE SAUVEGARDES            ");
    puts("-----------------------------------------------");

    couleur(ROUGE);
    printf("0 - Retour\n");
    couleur(VERT);

    printf("1 - ");
    couleur(JAUNE);
    savefile_display(1);
    couleur(VERT);

    printf("2 - ");
    couleur(JAUNE);
    savefile_display(2);
    couleur(VERT);

    printf("3 - ");
    couleur(JAUNE);
    savefile_display(3);
    couleur(RESET);

    reads(choix, 2);
    while( strtol(choix, NULL, 10) > 5 || strtol(choix, NULL, 10) < 0 || !isdigit(choix[0]))
    {   
        clear_screen();
        printf("%s\n", menuType);
        puts("-----------------------------------------------");
        puts("            FICHIERS DE SAUVEGARDES            ");
        puts("-----------------------------------------------");

        couleur(ROUGE);
        printf("0 - Retour\n");
        couleur(VERT);

        printf("1 - ");
        couleur(JAUNE);
        savefile_display(1);
        couleur(VERT);

        printf("2 - ");
        couleur(JAUNE);
        savefile_display(2);
        couleur(VERT);

        printf("3 - ");
        couleur(JAUNE);
        savefile_display(3);
        couleur(RESET);

        if( !strisnumber(choix) ) printf("\nCe que vous avez entre n'est pas un numero !\nVeuillez entrer un numero : ");
        else if( strtol(choix, NULL, 10) > 3 || strtol(choix, NULL, 10) < 0) printf("\nLe numero doit etre compris entre 0 et 3.\nVeuillez entrer un autre numero : ");
        reads(choix, 2);
        }

    numChoix = strtol( choix, NULL, 10);

    return numChoix;
}


int write_savefile(FILE *destFile, puiss4 savedGame)
{
    struct tm date;

    date = get_date();

    if( fseek(destFile, 0, SEEK_SET) )
    {
        printf("\nFailed to get at beginning of save file.\n");
        return 0;
    }

    fprintf(destFile, "%s\n", nomJoueurUn);
    fprintf(destFile, "%s\n", nomJoueurDeux);
    fprintf(destFile, "%d\n", date.tm_mday );
    fprintf(destFile, "%d\n", date.tm_mon );
    fprintf(destFile, "%d\n", date.tm_year );
    fprintf(destFile, "%d\n", date.tm_hour );
    fprintf(destFile, "%d\n", date.tm_min );
    fprintf(destFile, "%d\n", tour);
    fprintf(destFile, "%d\n", nbLignes);
    fprintf(destFile, "%d\n", nbCol);
    fprintf(destFile, "%d\n", nbPionsGagnant);

    for( int i = 0; i < nbLignes; i++ )
    {
        for (int j = 0; j < nbCol; j++ )
        {
            fprintf(destFile, "%d\n", savedGame.grille[i][j]);
        }
    }

    for( int h = 0; h < nbCol; h++)
    {
        fprintf(destFile, "%d\n", savedGame.dernier_pion[h]);
    }

    return 1;
}

int overwrite_file(const char *fileName, puiss4 currentGame)
{   
    FILE *saveFile = NULL;


    int confirmation = 0;
    saveFile = fopen(fileName, "a+");

    if ( saveFile == NULL )
    {
        printf( "\nError couldn't open save slot.\n" );
        return 0;
    }

    if (fseek(saveFile, 0, SEEK_END))
    {
        printf("\nErreur : le curseur n'a pas pu etre place a la fin du fichier de sauvegarde.\n");
        fclose(saveFile);
        return 0;
    }

    if ( ftell( saveFile ) == 0 )
    {
        write_savefile(saveFile, currentGame);
        fclose( saveFile );
        return 1;
    }
    else
    {   
        printf("\nLa sauvegarde choisie est pleine. Si vous confirmez, la sauvegarde sera ecrasee.\n");
        confirmation = confirm_answer();
        if ( confirmation )
        {
            fclose( saveFile ); // en mode a+, toutes les fonctions qui ecrivent dans le fichier remettent le curseur a la fin, donc on passe en mode w pour ecraser le fichier
            saveFile = fopen ( fileName, "w");
            if ( !write_savefile(saveFile, currentGame) ) 
            {
                printf("Erreur : l'ecriture de la sauvegarde n'a pas pu etre effectuee.\n");
                fclose(saveFile);
                return 0;
            }
            fclose( saveFile );
            return 1;
        }
    }
    
    fclose(saveFile);

    return 0;
}

int save( puiss4 game, int saveSlot )
{   
    char slotPath[25];

    snprintf( slotPath, 25, "savefiles/save%d.SAV", saveSlot);

    if ( overwrite_file(slotPath, game) == 0 ) 
    {
        printf( "\nPartie Non Sauvegardee.\nAppuyer sur 'Entree' pour continuer...");
        flushbuff();
        return 0;
    }
    else printf("\nPartie Sauvegardee.\nAppuyer sur 'Entree' pour continuer...");
    flushbuff(); 

    return 1;
}

int del_save( int saveSlot)
{
    char slotPath[25];
    int confirmation = 0;

    FILE *deletedSave;

    printf("\nLa sauvegarde ne pourra pas etre recuperee.\n");
    confirmation = confirm_answer();

    if ( confirmation )
    {
        snprintf( slotPath, 25, "savefiles/save%d.SAV", saveSlot);

        deletedSave = fopen( slotPath, "w");

        if ( deletedSave == NULL )
        {
            printf( "\nErreur : le fichier de sauvegarde n'a pas pu etre ouvert.\nAppuyer sur 'Entree' pour continuer...");
            flushbuff();
            return 0;
        }

        fclose( deletedSave );

        return 1;
    }

    return 0;

}

int load_save( puiss4 *destGrid, int saveSlot )
{
    char slotPath[25], tempBuffer[25];
    int confirmation;

    FILE *loadedFile = NULL;

    snprintf( slotPath, 25, "savefiles/save%d.SAV", saveSlot);

    loadedFile = fopen( slotPath, "r" );

    if ( loadedFile == NULL )
    {
        printf( "\nErreur : le programme n'a pas pu acceder au fichier de sauvegarde.\n" );
    }

    if( fseek(loadedFile, 0, SEEK_END) )
    {
        printf("\nErreur : le curseur n'a pas pu etre place a la fin du fichier.\n");

        fclose(loadedFile);
        return 0;
    }

    if( ftell( loadedFile ) == 0 )
    {
        printf("\nLe fichier choisi est vide.\n");
        fclose( loadedFile );
        return 0;
    }
    else
    {
        confirmation = confirm_answer();
        if ( !confirmation )
        {
            fclose ( loadedFile );
            return 0;
        }

        if( fseek( loadedFile, 0, SEEK_SET ) )
        {
            printf("\nErreur : le curseur n'a pas pu etre place au debut du fichier.\n");
            fclose(loadedFile);
            return 0;
        }

        // Chargement des noms de joueur
        readfile( tempBuffer, 25, loadedFile );
        strcpy( nomJoueurUn, tempBuffer );

        readfile( tempBuffer, 25, loadedFile );
        strcpy( nomJoueurDeux, tempBuffer );

        //On passe les lignes de date
        for ( int i = 0; i < 5; i++ )
        {
            readfile( tempBuffer, 25, loadedFile );
        }
        
        // Chargement du numero de tour
        readfile( tempBuffer, 25, loadedFile );
        tour = strtol( tempBuffer, NULL, 10);

        // Chargement des parametres de jeu
        readfile( tempBuffer, 25, loadedFile );
        nbLignes = strtol( tempBuffer, NULL, 10);

        readfile( tempBuffer, 25, loadedFile );
        nbCol = strtol( tempBuffer, NULL, 10);

        readfile( tempBuffer, 25, loadedFile );
        nbPionsGagnant = strtol( tempBuffer, NULL, 10);

        // Chargements du struct puiss4
        for ( int ligne = 0; ligne < nbLignes; ligne++ )
        {
            for ( int colonne = 0; colonne < nbCol; colonne++ )
            {
                readfile( tempBuffer, 25, loadedFile );
                destGrid->grille [ ligne ] [ colonne ] = strtol( tempBuffer, NULL, 10);
            }
        }

        for ( int h = 0; h < nbCol; h++ )
        {
            readfile( tempBuffer, 25, loadedFile);
            destGrid->dernier_pion [ h ] = strtol( tempBuffer, NULL, 10);
        }

        fclose( loadedFile );
        return 1;
    }
    
    fclose( loadedFile );
    return 0;
}

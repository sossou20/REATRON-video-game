#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "fonctions.h"
#include "affichage.h"

int main(void) {
    srand(time(NULL));
    char elt[5] = {'R', 'B', 'G', 'Y', 'V'};
    int choix;

    // Menu d'accueil unique au lancement du jeu

        printf("BIENVENUE SUR ");
        titre();
        text_color(15);
        printf("Appuyez sur une touche pour commencer...");
        getch();


    clrscr();

    // Variables de progression des niveaux
    int niveauActuel = 1;
    int maxNiveaux = 3;
    int continuerCampagne = 1; // 1 = continue, 0 = arrêt (défaite ou fin du jeu)

    int cont;

    int surcharge=0;

    // BOUCLE DE PROGRESSION DES NIVEAUX
    while (niveauActuel <= maxNiveaux && continuerCampagne && surcharge<=5) {

        // Réinitialisation des variables de jeu pour le nouveau niveau
        int l = 0, c = 0;
        int lignes = 12;
        int colonnes = 20;
        int tmpl, tmpc;
        int a;
        int c1, l1;

        int r = 0, g = 0, b = 0, y = 0, v = 0;
        int sco = 0;
        char ch;
        char tmp;
        char touche1 = 0, touche2 = 0;

        int reqR, reqB, reqG, reqY, reqV;
        int maxManips, tempsLim;
        int manipsEffectuees = 0;

        clock_t temps_debut;
        double temps_ecoule = 0;
        int finPartie = 0; // 1 = Gagné, 2 = Échec, 3 = Abandon

        // Chargement des objectifs propres au niveau en cours
        chargerObjectifsNiveau(niveauActuel, &reqR, &reqB, &reqG, &reqY, &reqV, &maxManips, &tempsLim);

        // Allocation dynamique de la matrice
        char **mat = malloc(lignes * sizeof(char*));
        if (mat == NULL) {
            printf("Erreur d'allocation principale.\n");
            return 1;
        }
        for (int i = 0; i < lignes; i++) {
            mat[i] = malloc(colonnes * sizeof(char));
            if (mat[i] == NULL) {
                printf("Erreur d'allocation ligne %d.\n", i);
                return 1;
            }
        }

        matrice(mat, elt);
        temps_debut = clock();

        // Écran de transition pour annoncer le niveau
        text_color(14);
        printf("\n=========================================\n");
        printf("        PREPARATION DU NIVEAU %d\n", niveauActuel);
        printf("=========================================\n");
        text_color(15);
        printf("Appuyez sur une touche pour commencer...");
        getch();
        clrscr();

        // Boucle du gameplay pour le niveau en cours
        do {
            temps_ecoule = (double)(clock() - temps_debut) / CLOCKS_PER_SEC;

            a = verifierAlignement(mat, &c1, &l1, &ch);
            if (a > 0) {
                detect(a, l1, c1, mat, ch);
                sco = score(mat);
                augscore(ch, sco, &v, &r, &g, &b, &y);
                suppr(mat);
                grav(mat);
                gnr(mat, elt);
            }

            gotoxy(0, 0);
            for (int i = 0; i < lignes; i++) {
                for (int j = 0; j < colonnes; j++) {
                    afficher_reacteur(mat[i][j]);
                }
                printf("\n");
            }

            affscore(r, g, b, y, v,surcharge);
            text_color(15);
            printf("\n================ NIVEAU %d ================\n", niveauActuel);
            printf("Manipulations : %d / %d\n", manipsEffectuees, maxManips);
            printf("Temps restant : %.1f s / %d s\n", (tempsLim - temps_ecoule) > 0 ? (tempsLim - temps_ecoule) : 0.0, tempsLim);
            printf("Objectifs requis : R=%d, B=%d, G=%d, Y=%d, V=%d\n", reqR, reqB, reqG, reqY, reqV);
            printf("===========================================\n");

            afficherObjet(mat[l][c], c, l, couleurelt(mat[l][c]));

            if (verifierVictoire(r, b, g, y, v, reqR, reqB, reqG, reqY, reqV, manipsEffectuees, maxManips, temps_ecoule, tempsLim)) {
                finPartie = 1;
                break;
            }
            if (verifierEchec(r, b, g, y, v, reqR, reqB, reqG, reqY, reqV, manipsEffectuees, maxManips, temps_ecoule, tempsLim,surcharge)) {
                finPartie = 2;
                break;
            }

            if (kbhit() != 0) {
                touche1 = getch();
                deplacerChasseur(touche1, &c, &l);

                if (touche1 == 32) {
                    tmp = mat[l][c / 4];
                    tmpl = l;
                    tmpc = c / 4;

                    gotoxy(c, l);
                    text_color(15);
                    printf("X");

                    touche2 = getch();

                    if (touche1 == 32 && touche2 == 'f') {
                        if (getch() == 'f') {
                            finPartie = 3;
                            break;
                        }
                    }

                    int permute = 0;
                    switch (touche2) {
                        case 'z':
                            if (l > 0) {
                                mat[l][c / 4] = mat[l - 1][c / 4];
                                mat[l - 1][c / 4] = tmp;
                                permute = 1;
                            }
                            break;
                        case 'q':
                            if ((c / 4) > 0) {
                                mat[l][c / 4] = mat[l][(c - 4) / 4];
                                mat[l][(c - 4) / 4] = tmp;
                                permute = 1;
                            }
                            break;
                        case 's':
                            if ((c / 4) < colonnes - 1) {
                                mat[l][c / 4] = mat[l][(c + 4) / 4];
                                mat[l][(c + 4) / 4] = tmp;
                                permute = 1;
                            }
                            break;
                        case 'w':
                            if (l < lignes - 1) {
                                mat[l][c / 4] = mat[l + 1][c / 4];
                                mat[l + 1][c / 4] = tmp;
                                permute = 1;
                            }
                            break;
                        default:
                            break;
                    }

                    if (permute) {
                        manipsEffectuees++;
                    }
                }
            }

            #ifdef _WIN32
            _sleep(50);
            #else
            struct timespec ts = {0, 50000000};
            nanosleep(&ts, NULL);
            #endif

        } while (finPartie == 0);

        // Analyse du résultat du niveau
        clrscr();
        if (finPartie == 1) {
            text_color(10); // Vert
            printf("\n=========================================\n");
            printf("   BRAVO ! NIVEAU %d REUSSI !\n", niveauActuel);
            text_color(15);
            printf("Preparation du passage au niveau suivant...\n\n");

            niveauActuel++; // On passe au niveau supérieur

            printf("Appuyez sur une touche pour continuer...");
            getch();
            clrscr();
        }
        else {
            text_color(4); // Rouge

            printf("   GAME OVER\n");
            if (finPartie == 2) {
                if (manipsEffectuees >= maxManips) printf(" Cause : Plus de manipulations disponibles au niveau %d.\n", niveauActuel);
                if (temps_ecoule > tempsLim) printf(" Cause : Temps limite depasse au niveau %d.\n", niveauActuel);
                do{
                printf("Recommencer (1) ou abandonner(2)\n");
                scanf("%d",&cont);
                }while(cont!=1 && cont!=2);
                if(cont==2){
                    continuerCampagne = 0;
                }
                else {
                        surcharge++;
                    }


            } else {
                printf(" Cause : Abandon de la partie.\n");
                continuerCampagne = 0;
            }
            printf("=========================================\n");

             // Met fin à la boucle des niveaux (défaite ou abandon)
        }

        // Libération de la mémoire de la grille actuelle avant de passer à la suite
        for (int i = 0; i < lignes; i++) {
            free(mat[i]);
        }
        free(mat);
    }

    // Message final de fin de jeu (Victoire totale)
    if (niveauActuel > maxNiveaux && continuerCampagne) {
        text_color(11); // Cyan brillant
        printf(" FELICITATIONS ! TOUS LES NIVEAUX ONT ETE BATTUS !\n");
        printf("          TU AS SAUVE LE REACTEUR !!!\n");

    }

    text_color(15);
    if(surcharge>5){
        printf("DOMMAGE, SURCHARGE DU REACTEUR\n");
    }
    printf("Merci d'avoir joue ! Fin du programme.\n");
    return 0;
}

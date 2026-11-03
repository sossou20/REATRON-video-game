#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "affichage.h"
#include "fonctions.h"


//Afficher le menu
int menu() {
    int choix;
    text_color(15);
    printf("\n1. Jouer");
    printf("\n2. Regles du jeu");
    printf("\n3. Quitter\n");
    scanf("%d",&choix);
    return choix;
}


// Afficher des règles du jeu



// Afficher le cadre de la zone de jeu



// Afficher un caractère à une position dans la console avec une couleur
void afficherObjet(char c, int x, int y, int couleur) {


    gotoxy(x,y); // deplace le curseur sur l'objet
    text_color(couleur); // applique la couleur
    //printf("%c",c); // affiche l'objet

}


// Déplacer le chasseur selon la touche appuyée
void deplacerChasseur(char touche, int *x, int *y) {
    /* A COMPLETER */
    /*Selon le caractère appuie, la position du chasseur change*/

    if(touche=='z'){
        if(*y>0){
            (*y)--;
        }
    }
    else if(touche=='w'){
        if(*y<HAUTEUR){
        (*y)++;
        }
    }
    else if(touche=='q'){
        if(*x>0){
        (*x)-=4;
        }
    }
    else if(touche=='s'){
        if(*x<LARGEUR){
        (*x)+=4;
        }
    }
}


// Génèrer des coordonnées aléatoires pour le trésor
/*void genererTresor(int *x, int *y) {
    /* A COMPLETER */
    /*La position change tel qu'il reste dans le cadre*/
    /**x=rand()%(LARGEUR+1);
    *y=rand()%(HAUTEUR+1);
}*/


//Vérifier si le chasseur a attrapé un tresor//



//Jouer une partie


int couleurelt (char c){
 switch(c){
case 'R':
    return 4;
case 'B':
    return 1;
case 'G':
    return 2;
case 'Y':
    return 14;
case 'V':
    return 5;
default:
    return 15;


 }

 }





 void titre(){
 text_color(1);
  printf("R");

  text_color(2);
   printf("E");

   text_color(4);
    printf("A");

    text_color(5);
     printf("C");

     text_color(6);
      printf("T");

       text_color(10);
        printf("R");

        text_color(14);
         printf("O");

         text_color(9);
          printf("N\n");
          }




void afficher_reacteur(char c){

text_color(couleurelt (c));
 printf("%c   ", c);

}



int verifierAlignement(char **board, int *c1, int *l1,char *color) {

    // --- HORIZONTAL ---
    // On s'arrête à 18 (colonnes-2) pour ne jamais dépasser c+2
    // --- HORIZONTAL ---
for (int l = 0; l < 12; l++) {
    for (int c = 0; c < 20; c++) {
       *(color) = board[l][c];

        // On ignore les cases vides ou marquées
        if (*(color) == ' ' || *(color) == 'X') continue;

        // 1. Vérification alignement de 5
        if (c + 4 < 20 && board[l][c+1] == *(color) && board[l][c+2] == *(color) &&
            board[l][c+3] == *(color) && board[l][c+4] == *(color)) {
                *l1 = l; *c1 = c;

            for(int i = 0; i < 12; i++) {
                for(int j = 0; j < 20; j++) {
                    if (board[i][j] == *(color)) board[i][j] = 'X';
                }
            }
            return 5;
        }
        // 2. Vérification alignement de 3 (et 4)
        else if (c + 2 < 20 && board[l][c+1] == *(color) && board[l][c+2] == *(color)) {
            *l1 = l; *c1 = c;

            // Si c'est un 4 (l'élément suivant est la même couleur)
            if (c + 3 < 20 && board[l][c+3] ==*(color)) return 1; // Retourne 3 pour 4 alignés
            else return 2; // Retourne 4 pour 3 alignés
        }
    }
}

    // --- VERTICAL ---
    // On s'arrête à 10 (lignes-2) pour ne jamais dépasser l+2
   for (int c = 0; c < 20; c++) {
        for (int l = 0; l < 12; l++) {
            *(color) = board[l][c];
            if (*(color) == ' ' || *(color) == 'X') continue;

            // 1. Vérification alignement de 5
            if (l + 4 < 12 && board[l+1][c] == *(color) && board[l+2][c] == *(color) &&
                board[l+3][c] == *(color) && board[l+4][c] == *(color)) {
                    *l1 = l; *c1 = c;

                for(int i = 0; i < 12; i++) {
                    for(int j = 0; j < 20; j++) {
                        if (board[i][j] == *(color)) board[i][j] = 'X';
                    }
                }
                return 10;
            }
            // 2. Vérification alignement de 3
            else if (l + 2 < 12 && board[l+1][c] == *(color) && board[l+2][c] == *(color)) {
                *l1 = l; *c1 = c;
                if (l + 3 < 12 && board[l+3][c] ==*(color)) return 3;
                else return 4;
            }
        }
    }
    return 0;
}


void suppr(char **board){
    int c;
    char temp;
for(c=0;c<20;c++){
if (board[0][c]=='X'){
            board[0][c]=' ';
        }
}

for( int l=1;l<12;l++){
    for( c=0;c<20;c++){
        if (board[l][c]=='X'){

            board[l][c]=' ';

        }

    }
}
}


void grav(char **board) {
    // 1. On parcourt chaque colonne
    for (int c = 0; c < 20; c++) {
        // 2. On remonte du bas vers le haut (lignes 11 à 0)
        for (int l = 11; l >= 0; l--) {
            // Si la case est vide
            if (board[l][c] == ' ') {
                // On cherche un élément au-dessus
                for (int t = l - 1; t >= 0; t--) {
                    if (board[t][c] != ' ' && board[t][c] != 'X') {
                        // On déplace l'élément trouvé vers la case vide
                        board[l][c] = board[t][c];
                        board[t][c] = ' '; // L'ancienne position est maintenant vide
                        break; // On arrête la recherche pour cette case vide
                    }
                }
            }
        }
    }
}




void detect(int a,int l1,int c1,char **board,char ch){
    if(a==1){
        board[l1][c1]='X';
        board[l1][(c1) +1]='X';
        board[l1][(c1) +2]='X';
        board[l1][(c1) +3]='X';
    }

    else if(a==2){
         board[l1][c1]='X';
        board[l1][(c1) +1]='X';
        board[l1][(c1) +2]='X';
    }

    else if(a==3){
        board[l1][c1]='X';
        board[(l1) +1][c1]='X';
        board[(l1) +2][c1]='X';
        board[(l1) +3][c1]='X';
    }
    else if(a==4){
         board[(l1)][c1]='X';
        board[(l1) +1][c1]='X';
        board[(l1) +2][c1]='X';
    }
    else if(a==5 || a==10){
        for (int i=0;i<12;i++){
            for(int j=0;j<20;j++){
                if(board[i][j]=='X'){
                    board[i][j]='X';
                }
            }
        }
    }




}

void gnr(char **mat, char elt[5]) {
    int lignes = 12;
    int colonnes = 20;

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {

            // On ne change que si la case est vide
            if (mat[i][j] == ' ') {
                int valide;
                do {
                    valide = 1;
                    mat[i][j] = elt[rand() % 5];

                    // Vérifier le voisin de gauche
                    if (j > 0 && mat[i][j] == mat[i][j - 1]) {
                        valide = 0;
                    }
                    // Vérifier le voisin du dessus
                    if (i > 0 && mat[i][j] == mat[i - 1][j]) {
                        valide = 0;
                    }
                    // Vérifier le voisin de droite (s'il est déjà rempli)
                    if (j < colonnes - 1 && mat[i][j + 1] != ' ' && mat[i][j] == mat[i][j + 1]) {
                        valide = 0;
                    }
                    // Vérifier le voisin du dessous (s'il est déjà rempli)
                    if (i < lignes - 1 && mat[i + 1][j] != ' ' && mat[i][j] == mat[i + 1][j]) {
                        valide = 0;
                    }

                } while (!valide);
            }
        }
    }
}


void matrice(char **mat,char elt[5]){
    int lignes,colonnes;
    lignes=12;
    colonnes=20;
for (int i = 0; i < 2/*lignes*/; i++){
    for (int j = 0; j < 2/*colonnes*/; j++){
         mat[i][j] =elt[rand()%5];
     }
    for (int j = 2; j < colonnes; j++){
            do{
             mat[i][j] =elt[rand()%5];
             }while(mat[i][j]==mat[i][j-1] && mat[i][j]==mat[i][j-2]);
         }
 }

 for (int i = 2; i < lignes; i++){
     for (int j = 0; j < 2/*colonnes*/; j++){
          do{
          mat[i][j] =elt[rand()%5];
          }while(mat[i][j]==mat[i-1][j] && mat[i][j]==mat[i-2][j]);
      }


     for (int j = 2; j < colonnes; j++){
             do{
              mat[i][j] =elt[rand()%5];
              }while((mat[i][j]==mat[i][j-1] && mat[i][j]==mat[i][j-2])|| (mat[i][j]==mat[i-1][j] && mat[i][j]==mat[i-2][j]));
          }
    }
  }



int score (char **board){
int a=0;
for( int l=0;l<12;l++){
    for( int c=0;c<20;c++){
        if (board[l][c]=='X'){
            a++;
            }
        }
    }
    return a;
  }


  int augscore(char elt,int a,int *v,int *r,int *g,int *b,int *y){
        if(elt=='R'){
            (*r)+=a;
        }

        else if(elt=='G'){
            (*g)+=a;
        }
        else if(elt=='B'){
            (*b)+=a;
        }
        else if(elt=='Y'){
            (*y)+=a;
        }
        else if(elt=='V'){
            (*v)+=a;
        }
  }


  void affscore(int r, int g,int b,int y,int v,int s){
text_color(15);
printf("Niveau de surcharge: %d\n",s);
  text_color(4);
printf("\nR=%d\n",r);

text_color(2);
printf("G=%d\n",g);

text_color(1);
printf("B=%d\n",b);

text_color(14);
printf("Y=%d\n",y);

text_color(5);
printf("V=%d\n",v);

  }


//CHARGEMENT DES OBJECTIFS DE NIVEAU (Mis à jour)

void chargerObjectifsNiveau(int numeroNiveau, int *reqR, int *reqB, int *reqG, int *reqY, int *reqV, int *maxManips, int *tempsLim) {
    switch(numeroNiveau) {
        case 1:
            *reqR = 10;  *reqB = 10;  *reqG = 0;   *reqY = 0;   *reqV = 0;
            *maxManips = 15;
            *tempsLim = 120; // 120 secondes (2min)
            break;
        case 2:
            *reqR = 20;  *reqB = 20;  *reqG = 20;  *reqY = 0;   *reqV = 0;
            *maxManips = 12;
            *tempsLim = 75; // 75 secondes (1min15s)
            break;
        case 3:
            *reqR = 25;  *reqB = 25;  *reqG = 25;  *reqY = 25;  *reqV = 25;
            *maxManips = 30;
            *tempsLim = 60; // 60 secondes (1min)
            break;
        default:
            // Sécurité si un bug demande un niveau inexistant
            *reqR = 999; *reqB = 999; *reqG = 999; *reqY = 999; *reqV = 999;
            *maxManips = 1;
            *tempsLim = 10;
            break;
    }
}


// SECTION 3.6 : VERIFICATION DES CONDITIONS DE VICTOIRE

int verifierVictoire(int r, int b, int g, int y, int v,
                     int reqR, int reqB, int reqG, int reqY, int reqV,
                     int manips, int maxManips, double tempsEcoule, int tempsLim) {

    int energiesOk = (r >= reqR) && (b >= reqB) && (g >= reqG) && (y >= reqY) && (v >= reqV);
    int coupsOk = (manips <= maxManips);
    int tempsOk = (tempsEcoule <= tempsLim);

    if (energiesOk && coupsOk && tempsOk) {
        return 1;
    }
    return 0;
}


// SECTION 3.7 : VERIFICATION DES CONDITIONS DE ECHEC

int verifierEchec(int r, int b, int g, int y, int v,
                   int reqR, int reqB, int reqG, int reqY, int reqV,
                   int manips, int maxManips, double tempsEcoule, int tempsLim,int s) {

    if (verifierVictoire(r, b, g, y, v, reqR, reqB, reqG, reqY, reqV, manips, maxManips, tempsEcoule, tempsLim)) {
        return 0;
    }

    if ((manips >= maxManips) || (tempsEcoule > tempsLim)||(s>5)) {
        return 1;
    }

    return 0;
}

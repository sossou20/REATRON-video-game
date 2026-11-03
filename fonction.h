#ifndef FONCTIONS_H
#define FONCTIONS_H

#define LARGEUR 76
#define HAUTEUR 11
#define TDJ 180.0 // temps de jeu de 3 minutes

int menu(); // affiche le menu
void titre();//affiche le titre
void afficher_reacteur(char c);//affiche la matrice
void afficherRegles();// affiche les regles du jeu
void afficherObjet(char c, int x, int y, int couleur);// affiche l'objet en fonction de sa position et sa couleur
void deplacerChasseur(char touche, int *x, int *y);// deplace le curseur
int couleurelt (char c);//colorie l'»l»ment du r»acteur
int verifierAlignement(char **board, int *c1, int *l1,char *color);//d»tecte les alignements
void suppr(char **board);//remplace les »l»ments align»s par ' '
void grav(char **board);//applque la gravit»
void detect(int a,int l1,int c1,char **board,char ch);//remplace les »l»ments align»s par des 'X'
void gnr(char **mat,char elt[5]);//r»g»nÀre la matrice
void matrice(char **mat,char elt[5]);//g»n»ration initiale de la matrice
int score (char **board);//le nombre avec lequel on augmante le score
int augscore(char elt,int a,int *v,int *r,int *g,int *b,int *y);//augmente le score correspondant á l'»l»ment du r»acteur
void affscore(int r, int g,int b,int y,int v,int s);//affiche le score actuel

// =========================================================================
// Moteur de rËgles (Sections 3.5 ‡ 3.7)
// =========================================================================
void chargerObjectifsNiveau(int numeroNiveau, int *reqR, int *reqB, int *reqG, int *reqY, int *reqV, int *maxManips, int *tempsLim);
int verifierVictoire(int r, int b, int g, int y, int v, int reqR, int reqB, int reqG, int reqY, int reqV, int manips, int maxManips, double tempsEcoule, int tempsLim);
int verifierEchec(int r, int b, int g, int y, int v, int reqR, int reqB, int reqG, int reqY, int reqV, int manips, int maxManips, double tempsEcoule, int tempsLim,int s);

#endif // !FONCTIONS_H

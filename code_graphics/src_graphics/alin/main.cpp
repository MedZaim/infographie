
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "./../../includs/graphics_utils.h"
using namespace std;

#define Pi 3.1415926535897932384

// Matrice de projection
double M_Cabinet[4][4] = {
        {1,           0,           0, 0},
        {0,           1,           0, 0},
        {sqrt(2) / 3, sqrt(2) / 3, 0, 0},
        {0,           0,           0, 1}
};
double M_Cavalie[4][4] = {
        {1,           0,           0, 0},
        {0,           1,           0, 0},
        {sqrt(2) / 2, sqrt(2) / 2, 0, 0},
        {0,           0,           0, 1}
};


// Initialisation du mode graphique
void initgraph_custom() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *) "");
    if (gm == DETECT) {
        printf("Graphics mode not detected.\n");
        exit(1);
    }
}


/*// Fonction utilitaire pour placer un pixel dans le syst�me de coordonn�es centr�
void pixel(int x, int y, int color) {
    x = x + 320;
    y = 240 - y;
    putpixel(x, y, color);
}*/


// Algorithme de trac� de ligne de Bresenham
void Ligne_Bresenham(int xd, int yd, int xf, int yf, int color) {
    int dx = abs(xf - xd), dy = abs(yf - yd);
    int sx = (xd < xf) ? 1 : -1, sy = (yd < yf) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        pixel(xd, yd, color);
        if (xd == xf && yd == yf) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            xd += sx;
        }
        if (e2 < dx) {
            err += dx;
            yd += sy;
        }
    }
}


void repere() {
    cleardevice();
    setcolor(WHITE);
    Ligne_Bresenham(0, 0, 320, 0, 11);  // Axe X
    Ligne_Bresenham(0, 0, 0, 240, 11);  // Axe Y
    Ligne_Bresenham(0, 0, -240, -240, 11); // Axe Z
}


// Multiplication de matrices
void Produit_Matrice(double A[8][4], double B[4][4], double C[8][4]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


// Trac� des ar�tes d'un cube
void Cube(double points[8][4]) {
    // Base (face inf�rieure)
    line_bresenham(points[0][0], points[0][1], points[1][0], points[1][1], YELLOW, 5);
    line_bresenham(points[1][0], points[1][1], points[2][0], points[2][1], YELLOW, 5);
    line_bresenham(points[2][0], points[2][1], points[3][0], points[3][1], YELLOW, 5);
    line_bresenham(points[3][0], points[3][1], points[0][0], points[0][1], YELLOW, 5);

    // Haut (face sup�rieure)
    line_bresenham(points[4][0], points[4][1], points[5][0], points[5][1], YELLOW, 5);
    line_bresenham(points[5][0], points[5][1], points[6][0], points[6][1], YELLOW, 5);
    line_bresenham(points[6][0], points[6][1], points[7][0], points[7][1], YELLOW, 5);
    line_bresenham(points[7][0], points[7][1], points[4][0], points[4][1], YELLOW, 5);

    // Ar�tes verticales (connectant base et haut)
    line_bresenham(points[0][0], points[0][1], points[4][0], points[4][1], YELLOW, 5);
    line_bresenham(points[1][0], points[1][1], points[5][0], points[5][1], YELLOW, 5);
    line_bresenham(points[2][0], points[2][1], points[6][0], points[6][1], YELLOW, 5);
    line_bresenham(points[3][0], points[3][1], points[7][0], points[7][1], YELLOW, 5);
}


void tracer_plan(double points[8][4]) {
    double transformed_points[8][4];
    // Appliquer la matrice de transformation
    Produit_Matrice(points, M_Cabinet, transformed_points);

    int x1 = (int) transformed_points[2][0];
    int y1 = (int) transformed_points[2][1]; // Point P2
    int x2 = (int) transformed_points[3][0];
    int y2 = (int) transformed_points[3][1]; // Point P3
    Ligne_Bresenham(x1, y1, x2, y2, RED); // Tracer la ligne entre P2 et P3

    int x3 = (int) transformed_points[4][0];
    int y3 = (int) transformed_points[4][1]; // Point P4
    int x4 = (int) transformed_points[5][0];
    int y4 = (int) transformed_points[5][1]; // Point P5
    Ligne_Bresenham(x3, y3, x4, y4, RED); // Tracer la ligne entre P4 et P5

    Ligne_Bresenham(x1, y1, x4, y4, RED);
    Ligne_Bresenham(x3, y3, x2, y2, RED);

}


// Trac� avec perspective cavali�re
void tracer_cube(double points[8][4]) {
    // double transformed_points[8][4];
    //Produit_Matrice(points, M_Cabinet, transformed_points);
    //Cube(transformed_points);
    Cube(points);
}


void tracer_cubecavalier(double points[8][4]) {
    double transformed_points[8][4];
    Produit_Matrice(points, M_Cavalie, transformed_points);
    Cube(transformed_points);
}


/// tracer cube avec perspective
void ajusterMatrice(double matrice[8][4]) {
    for (int i = 0; i < 8; i++) {
        // V�rifier si la quatri�me colonne est diff�rente de 1
        if (matrice[i][3] != 1) {
            double w = matrice[i][3]; // Stocker la valeur de la quatri�me colonne

            // Ajouter w � la premi�re et la deuxi�me colonne
            matrice[i][0] /= w; // Ajouter w au premier �l�ment (x)
            matrice[i][1] /= w; // Ajouter w au deuxi�me �l�ment (y)

            // Mettre la quatri�me colonne � 1
            matrice[i][3] = 1;
        }
    }
}


void afficherMatrice(double matrice[8][4]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2f ", matrice[i][j]);
        }
        printf("\n");
    }
}

void afficherMatrice4(double matrice[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%.2f ", matrice[i][j]);
        }
        printf("\n");
    }
}


// Function to apply perspective transformation
void tracer_cube_perpective(double points[8][4],
                            double a = 200, double b = 0.2, double c = 1, // Centre de projection
                            double x0 = 1, double y0 = 1, double z0 = 200, // Point sur le plan de projection
                            double n1 = 100, double n2 = 1, double n3 = 100) { // Vecteur normal
    double d0 = n1 * x0 + n2 * y0 + n3 * z0;
    double d1 = n1 * a + n2 * b + n3 * c;
    double d = d0 - d1;

    // Validate inputs
    if (d0 == 0 || d == 0) {
        cout<<"d0: "<<d0<<"     d1:"<<d1<<"    d:"<<d<<endl;
        printf("Error: Division by zero. Check inputs for d0 and d.\n");
        return;
    }

    double transformed_points[8][4];
    double ProjectionPerspective[4][4] = {
            {1 + a * n1 / d, b * n1 / d,     c * n1 / d,     n1 / d},
            {a * n2 / d,     1 + b * n2 / d, c * n2 / d,     n2 / d},
            {a * n3 / d,     b * n3 / d,     1 + c * n3 / d, n3 / d},
            {a / d,          b / d,          c / d,          1}  // Corrected fourth row
    };

    // Debugging: Display the projection matrix
    printf("ProjectionPerspective matrix:\n");
    afficherMatrice4(ProjectionPerspective);

    // Apply the transformation
    Produit_Matrice(points, ProjectionPerspective, transformed_points);

    // Debugging: Display the transformed points before adjustment
    printf("Transformed points before adjustment:\n");
    afficherMatrice(transformed_points);

    // Adjust homogeneous coordinates
    ajusterMatrice(transformed_points);

    // Debugging: Display the transformed points after adjustment
    printf("Transformed points after adjustment:\n");
    afficherMatrice(transformed_points);

    // Draw the cube
    tracer_cube(transformed_points);
}

void tracer_cubeperpectiveZ(double points[8][4], double r) {
    double transformed_points[8][4];
    double ProjectionPerspectiveZ[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, -1 / r},
            {0, 0, 0, 1}
    };
    Produit_Matrice(points, ProjectionPerspectiveZ, transformed_points);
    afficherMatrice(transformed_points);
    ajusterMatrice(transformed_points);
    tracer_cube(transformed_points);
    printf("//////////////////////////:");
    afficherMatrice(transformed_points);
}

void tracer_cubeperpectiveX(double points[8][4], double r) {
    double transformed_points[8][4];
    double ProjectionPerspectiveX[4][4] = {
            {1, 0, 0, -1 / r},
            {0, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 1}
    };
    Produit_Matrice(points, ProjectionPerspectiveX, transformed_points);
    afficherMatrice(transformed_points);
    ajusterMatrice(transformed_points);
    tracer_cube(transformed_points);
    printf("//////////////////////////:");
    afficherMatrice(transformed_points);
}

void tracer_cubeperpectiveY(double points[8][4], double r) {
    double transformed_points[8][4];
    double ProjectionPerspectiveY[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, -1 / r},
            {0, 0, 0, 0},
            {0, 0, 0, 1}
    };
    Produit_Matrice(points, ProjectionPerspectiveY, transformed_points);
    afficherMatrice(transformed_points);
    ajusterMatrice(transformed_points);
    tracer_cube(transformed_points);
    printf("//////////////////////////:");
    afficherMatrice(transformed_points);
}

// Translation
void Translation(double points[8][4], double tx, double ty, double tz, double resultat[8][4]) {
    double TranslationMatrix[4][4] = {
            {1,  0,  0,  0},
            {0,  1,  0,  0},
            {0,  0,  1,  0},
            {tx, ty, tz, 1}
    };
    Produit_Matrice(points, TranslationMatrix, resultat);
}

// Rotation sur les axes principaux
void Rotation_axe_principale(double points[8][4], float anglex, float angley, float anglez, double resultat[8][4]) {
    double Rx[4][4] = {
            {1, 0,            0,           0},
            {0, cos(anglex),  sin(anglex), 0},
            {0, -sin(anglex), cos(anglex), 0},
            {0, 0,            0,           1}
    };

    double Ry[4][4] = {
            {cos(angley), 0, -sin(angley), 0},
            {0,           1, 0,            0},
            {sin(angley), 0, cos(angley),  0},
            {0,           0, 0,            1}
    };

    double Rz[4][4] = {
            {cos(anglez),  sin(anglez), 0, 0},
            {-sin(anglez), cos(anglez), 0, 0},
            {0,            0,           1, 0},
            {0,            0,           0, 1}
    };
    double temp1[8][4], temp2[8][4];
    Produit_Matrice(points, Rx, temp1);
    Produit_Matrice(temp1, Ry, temp2);
    Produit_Matrice(temp2, Rz, resultat);
}


void multiplierMatrice1x4_4x4(double A[1][4], double B[4][4], double C[1][4]) {
    // Calcul du produit de A (1x4) et B (4x4) pour donner C (1x4)
    for (int i = 0; i < 4; i++) {
        C[0][i] = 0;  // Initialiser l'�l�ment C[0][i]
        for (int j = 0; j < 4; j++) {
            C[0][i] += A[0][j] * B[j][i];
        }
    }
}

double calculer_norme(double vecteur[1][4]) {
    return sqrt(vecteur[0][0] * vecteur[0][0] +
                vecteur[0][1] * vecteur[0][1] +
                vecteur[0][2] * vecteur[0][2]);
}

void normaliser_vecteur(double vecteur[1][4]) {
    double norme = calculer_norme(vecteur);
    if (norme == 0) {
        printf("Erreur : le vecteur est nul, impossible de normaliser.\n");
        return;
    }
    vecteur[0][0] /= norme;
    vecteur[0][1] /= norme;
    vecteur[0][2] /= norme;
}


void rotation_axe(double points[8][4], double vecteur[1][4], int angle, double resultat[8][4]) {
    normaliser_vecteur(vecteur);

    // Trac� de la ligne entre les points d'origine et de fin apr�s transformation
    Ligne_Bresenham(0, 0, vecteur[0][0], vecteur[0][1], 10);

    // Calcul des cosinus des angles
    double n1 = vecteur[0][0];
    double n2 = vecteur[0][1];
    double n3 = vecteur[0][2];

    // Calcul de la matrice de rotation
    double theta = angle * (Pi / 180.0);
    double matrice_rotation[4][4] = {
            {n1 * n1 + (1 - n1 * n1) * cos(theta),         n1 * n2 * (1 - cos(theta)) + n3 * sin(theta),
                                                                                                         n1 * n3 * (1 -
                                                                                                                    cos(theta)) -
                                                                                                         n2 *
                                                                                                         sin(theta), 0},
            {n2 * n1 * (1 - cos(theta)) - n3 * sin(theta), n2 * n2 + (1 - n2 * n2) * cos(theta),         n2 * n3 * (1 -
                                                                                                                    cos(theta)) +
                                                                                                         n1 *
                                                                                                         sin(theta), 0},
            {n3 * n1 * (1 - cos(theta)) + n2 * sin(theta), n3 * n2 * (1 - cos(theta)) - n1 * sin(theta), n3 * n3 +
                                                                                                         (1 - n3 * n3) *
                                                                                                         cos(theta), 0},
            {0,                                            0,                                            0,          1}
    };

    // Appliquer la matrice de rotation sur tous les points du cube
    Produit_Matrice(points, matrice_rotation, resultat);

    // Tracer le cube apr�s rotation
    tracer_cube(resultat);

}

void tracer_vecteur(double V[1][4], int color, int wl = 1) {
    line_bresenham(0, 0, V[0][0], V[0][1], color, wl);

}

void multiplierVecteurParMatrice(double v[1][4], double R[4][4], double resultat[1][4]) {
    // Initialiser le r�sultat � z�ro
    for (int i = 0; i < 4; i++) {
        resultat[0][i] = 0; // On initialise la ligne du r�sultat
    }

    // Effectuer la multiplication
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            resultat[0][i] += R[i][j] * v[0][j]; // Acc�der aux �l�ments du vecteur et de la matrice
        }
    }
}


void aligne_vecteur(double V[1][4], double W[1][4]) {
    // Calcul des normes des vecteurs
    double normeV = calculer_norme(V);
    double normeW = calculer_norme(W);

    // Normalisation des vecteurs
    double V_norm[3] = {V[0][0] / normeV, V[0][1] / normeV, V[0][2] / normeV};
    double W_norm[3] = {W[0][0] / normeW, W[0][1] / normeW, W[0][2] / normeW};

    // Calcul de l'angle entre les deux vecteurs
    double cosTheta = V_norm[0] * W_norm[0] + V_norm[1] * W_norm[1] + V_norm[2] * W_norm[2];
    if (cosTheta > 1.0) cosTheta = 1.0;
    if (cosTheta < -1.0) cosTheta = -1.0;

    double angle = acos(cosTheta); // Angle en radians

    // Calcul de l'axe de rotation
    double axis[1][4]; // Utiliser un tableau 2D comme demand�
    axis[0][0] = V_norm[1] * W_norm[2] - V_norm[2] * W_norm[1];
    axis[0][1] = V_norm[2] * W_norm[0] - V_norm[0] * W_norm[2];
    axis[0][2] = V_norm[0] * W_norm[1] - V_norm[1] * W_norm[0];

    // Normaliser l'axe de rotation
    double normeAxis = calculer_norme(axis);
    if (normeAxis != 0) {
        axis[0][0] /= normeAxis;
        axis[0][1] /= normeAxis;
        axis[0][2] /= normeAxis;
    }

    // Matrice de rotation autour de l'axe
    double c = cos(angle);
    double s = sin(angle);

    double R[4][4] = {
            {c + axis[0][0] * axis[0][0] * (1 - c),
                    axis[0][0] * axis[0][1] * (1 - c) - axis[0][2] * s,
                       axis[0][0] * axis[0][2] * (1 - c) + axis[0][1] * s, 0},

            {axis[0][1] * axis[0][0] * (1 - c) + axis[0][2] * s,
                    c + axis[0][1] * axis[0][1] * (1 - c),
                       axis[0][1] * axis[0][2] * (1 - c) - axis[0][0] * s, 0},

            {axis[0][2] * axis[0][0] * (1 - c) - axis[0][1] * s,
                    axis[0][2] * axis[0][1] * (1 - c) + axis[0][0] * s,
                       c + axis[0][2] * axis[0][2] * (1 - c),              0},

            {0,     0, 0,                                                  1}
    };


    tracer_vecteur(V, GREEN, 5);
    tracer_vecteur(W, YELLOW, 5);

    // Attendre que l'utilisateur appuie sur une touche pour appliquer la rotation
    outtextxy(10, 10, " touch keybourd to apply transformation..");
    getch();  // Attendre une touche

    // Appliquer la matrice de rotation au vecteur V
    double resultatFinal[1][4]; // Pour le vecteur r�sultant (ajouter un composant homog�ne)
    multiplierVecteurParMatrice(V, R, resultatFinal);

    // Mettre � jour V avec le r�sultat de la rotation
    V[0][0] = resultatFinal[0][0];
    V[0][1] = resultatFinal[0][1];
    V[0][2] = resultatFinal[0][2];

    // Effacer l'ancien vecteur en redessinant l'�cran
    cleardevice(); // Efface l'�cran

    repere();
    tracer_vecteur(W, GREEN, 5);

    tracer_vecteur(V, YELLOW, 5);


}


void afficher_menu() {
    cleardevice();
    repere();
    setbkcolor(0);
    setcolor(WHITE);
    printf("-----------Menu des Transformations---------------\n");
    printf("1. Transformation Cabinet \n");
    printf("2. Transformation Cavalier \n");
    printf("3. Translation \n");
    printf("4. Rotation  \n");
    printf("5. Perspective \n");
    printf("6. rotation auteur d'un axe  \n");
    printf("7. align�e deux vecteur \n");
    printf("9. Quitter \n");
}

void executer_choix(int choix) {

    double points[8][4] = {
            {0,   0,   0,    1},
            {100, 0,   0,    1},
            {100, 100, 0,    1},
            {0,   100, 0,    1},
            {0,   0,   -100, 1},
            {100, 0,   -100, 1},
            {100, 100, -100, 1},
            {0,   100, -100, 1}
    };

    double resultat[8][4];
    switch (choix) {
        case 1:
            tracer_cube(points);
            break;
        case 2:
            tracer_cubecavalier(points);
            break;
        case 3: {
            int tx, ty, tz;
            printf("Donner les coordonn�es de translation : ");
            scanf("%d %d %d", &tx, &ty, &tz);
            Translation(points, tx, ty, tz, resultat);
            tracer_cube(resultat);
            break;
        }
        case 4: {
            float anglex, angley, anglez;
            printf("Donner les angles de rotation : ");
            scanf("%f %f %f", &anglex, &angley, &anglez);
            Rotation_axe_principale(points, anglex * (Pi / 180), angley * (Pi / 180), anglez * (Pi / 180), resultat);
            tracer_cube(resultat);
            break;
        }
        case 5: {
            double r;


            printf("Donner la distance de vue : ");
            scanf("%lf", &r); // Utiliser %lf pour un double

            tracer_cubeperpectiveZ(points, r); // Appel � la fonction pour perspective Z

            break;
        }
        case 6: {
            double vecteur[1][4] = {{100.0, 150.0, 30.0, 1.0}}; // Point de fin
            int angle;
            printf("Donner l'angle de rotation : ");
            scanf("%d", &angle);
            tracer_vecteur(vecteur, BLUE);
            rotation_axe(points, vecteur, angle, resultat);
            tracer_cube(resultat);
            break;
        }
        case 7: {
            double V[1][4] = {{100, 150, 30, 1}};
            double W[1][4] = {{-100, 200, 30, 1}};
            tracer_vecteur(V, BLUE);
            tracer_vecteur(W, YELLOW);
            aligne_vecteur(V, W);
            break;
        }
        case 8: {
            //tracer_plan(points);
            //projection_plan(points,0,-1,1);
            break;
        }
        case 9:
            exit(0);
        default:
            printf("Choix invalide! Appuyez sur une touche...\n");
            break;
    }
}

int main() {
    initgraph_custom();
    repere();

    double points[8][4] = {
            {0,   0,   0,    1},
            {100, 0,   0,    1},
            {100, 100, 0,    1},
            {0,   100, 0,    1},
            {0,   0,   -100, 1},
            {100, 0,   -100, 1},
            {100, 100, -100, 1},
            {0,   100, -100, 1}
    };

    double V[1][4] = {{-100, 200, 30, 1}};
    double W[1][4] = {{200, 250, 60, 1}};
    tracer_vecteur(V, GREEN, 5);
    tracer_vecteur(W, YELLOW, 5);
    aligne_vecteur(V, W);
    //tracer_cube_perpective(points);
    //tracer_cubeperpectiveZ(points, 300);

    /*
    tracer_cube(points);

    tracer_cubecavalier(points);



       // afficher_menu();
        
        int choix;
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        executer_choix(choix);
        */
    // Attendre que l'utilisateur appuie sur une touche avant de revenir au menu
    //outtextxy(100, 100 + (choix == 5 ? -20 : choix == 0 ? -40 : choix == -1 ? -60 : -80), "Appuyez sur une touche pour continuer...");
    getch();

    closegraph();
    return 0;
}

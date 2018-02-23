#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "union_find.h"
#include "kruskal.h"
#include "pgm_img.h"

/*! \file segmentation.h
 * \brief Implémentation de l'algorithme de segmentation et de coloration.
 *
 * L'algorithme de segmentation fournit les régions dans un fichier, écrites ligne par ligne. 
 * L'algorithme de coloration fournit l'image PGM générée en utilisant la librairie fournie sur CELENE. 
 *
 * \copyright PASD
 * \version 2017
 */

typedef struct pixel * pixel;

struct pixel{
    int position;
    int* tab;
};

arete* lire_matrice(unsigned int** matrice, int largeur, int hauteur, int* nb_arete);

liste segmentation(unsigned int** tab1,arete * tab,int largeur,int hauteur,int nb_aretes,int k);

//int filtre_segmentation(ensemble e1,ensemble e2, arete a);

#endif
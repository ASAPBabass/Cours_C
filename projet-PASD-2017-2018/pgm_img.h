#ifndef PGM_IMG_H
#define PGM_IMG_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*! \file
 * \brief Gestion simple d'images PNG (P5, binaires).
 *
 * Les informations de base de l'image (largeur, hauteur, valeur max et valeur des pixels) 
 * sont stockées dans une structure simple.
 *
 * L'image est conservée sous forme de matrice d'unsigned int. 
 * Programme basé sur la librairie PGMLib : https://github.com/joshimoo/PGMLib/blob/master/src/pgm/
 *
 * \copyright PASD
 * \version 2017
 */

#define P_MAX 65536

 /*!
  * Structure contenant les informations de base de l'image
  */
typedef struct pgm_img* pgm;

/*!
 * Crée une image
 * \param _largeur la largeur de l'image
 * \param _hauteur la hauteur de l'image
 * \param _valeur_max la valeur max des pixels de l'image
 * \return l'image créée
 */
pgm initialiser_image_pgm(const unsigned int _largeur, const unsigned int _hauteur, const unsigned int _valeur_max);

pgm creer_image_pgm(const unsigned int _largeur, const unsigned int _hauteur, const unsigned int valeur_max, unsigned int** image);

/*!
 * Lit une image
 * \param fichier l'image à lire
 * \return l'image créée
 */
pgm lire_image_pgm(const char* fichier);

/*!
 * Ecrit une image
 * \param fichier le fichier où écrire l'image
 * \param p l'image à écrire
 * \param un pointeur vers une fonction de filtre à appliquer (NULL si aucun filtre)
 * \return true si l'écriture s'est déroulée correctement, false sinon
 */
bool ecrire_image_pgm(const char* fichier, const pgm p, void(*filtre)(pgm p));

/*!
 * Getteurs et Accesseurs
 */
unsigned int** image_matrice(pgm p);
unsigned int largeur_image(pgm p);
unsigned int hauteur_image(pgm p);

/*!
 * Détruit une image
 * \param p un pointeur sur l'image à détruire
 */
void detruire_image_pgm(pgm* p);

#endif

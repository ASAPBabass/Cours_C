#ifndef CHAINE_H
#define CHAINE_H

#include <stdbool.h>
#include <stdio.h>

/*! \file
 * \brief Manipulation des chaînes de caractères.
 *
 * La chaîne de caractères est de taille variable et ne nécessite par un caractère de fin de chaîne.
 *
 * Les fonctions usuelles de création, manipulation, concaténation doivent être implémentées.
 *
 * \copyright PASD
 * \version 2017
 */

/*!
 * Cette struture permet de créer une chaîne de caractères comme un simple tableau.
 * La taille fait partie de la structure et permet de la connaître sans calcul 
 * et de se passer d'un caractère de fin de chaîne.
 * cette structure est cachée et ne peut pas être manipulée directement.
 */
typedef struct chaine* chaine;

struct chaine {
  unsigned int taille;
  char* tab;
};

/*!
 * Pour créer une chaine 
 * La chaine vide est de taille 0 et tab pointe sur NULL
 * \return une chaine vide
 */
chaine chaine_creer_vide();

/*!
 * Pour créer une chaine complète à partir d'un char* c
 * \return une chaine de taille length(c) avec tab contenant les caractères utiles de c
 */
chaine chaine_creer_char(char* c);

/*!
 * Pour désallouer correctement la mémoire
 * \param ch la chaine à détruire 
 */
void chaine_detruire(chaine* ch);

/*!
 * Pour afficher la chaîne dans un fichier au sens unix (par exemple stdout)
 * Le retour à la ligne est géré par chaine_afficher. 
 * \param f flux où imprimer.
 * \param ch chaine à afficher
 */
void chaine_afficher(FILE* f,chaine ch);

/*!
 * Renvoie la taille de la chaîne de caractères
 * \param ch chaine dont on demande la taille
 * \return le nombre de caractères de ch
 */
unsigned int chaine_extraire_taille(chaine ch);


/*!  Teste si la chaîne est vide
 * \param ch chaine à tester
 * \return vrai si ch est vide (taille 0)
 */
bool chaine_est_vide(chaine ch);

/*!
 * Teste si deux chaines sont identiques
 * \param ch1 première chaîne
 * \param ch2 deuxième chaîne
 * \return vrai si ch1 et ch2 sont identiques
 */
bool chaine_est_egal(chaine ch1, chaine ch2);

/*! Concatène deux chaînes
 * \param ch1 première chaine
 * \param ch2 deuxième chaine
 * \return ch1 concaténation de ch1 et ch2
 */
void chaine_concatener(chaine ch1, chaine ch2);

/*! 
 * Renvoie le caractère à la position i de la chaîne (on commence à compter à 0)
 * \param ch chaine pour laquelle on recherche le ième caractère
 * \param i le numéro de la position recherchée
 * \return le caractère tab[i] de ch
 */
char chaine_extraire_char_i(chaine ch, const unsigned int i);

/*!
 *  Modifie le ième caractère d'une chaine par un autre caractère
 * \param ch la chaine à modifier
 * \param le numéro de la position à modifier
 * \param c le caractère de modification
 */
void chaine_modifier_char_i(chaine ch, const unsigned int i, const char c);

/*! 
 * Copie 
 * \param ch1 la chaine à copier
 * \return une chaîne contenant une copie de ch1
 */
chaine chaine_copier(chaine ch1);

/*! 
 * Convertit en minuscules
 * \param ch la chaine à convertir
 * \return ch converti
 */
void chaine_en_minuscules(chaine ch);

/*!
 * Convertit en majuscules
 * \param ch la chaine à convertir
 * \return ch converti
 */
void chaine_en_majuscules(chaine ch);

/*! Recherche un caractère
 * \param c le caractère recherché
 * \param ch la chaine testée
 * \return i la position de c dans ch
 * \return vrai si c est contenu dans ch
 */
bool chaine_appartenir(const char c, chaine ch, int* i);

/*!
 * Renvoie une chaîne par lecture de "taille" caractères sur un fichier au sens Unix (par exemple stdin)
 * \param f le flux d'entrée
 * \param taille le nombre de caractères de la chaine à construire 
 * \return la chaine (sans faire de traitement particulier pour les caractères spéciaux).
 */
chaine chaine_lire(FILE* f, unsigned int taille);


#endif

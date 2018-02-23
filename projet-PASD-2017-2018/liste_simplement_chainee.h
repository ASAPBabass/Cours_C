#ifndef LISTE_SIMPLEMENT_CHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_H

#include <stdbool.h>
#include <stdio.h>

/*! \file listes_generiques.h
 * \brief Module liste générique.
 *
 * La structure est très similaire à celle pour les entiers
 * L'objectif est de rajouter des fonctions dans cette structure
 * afin de construire une liste d'éléments de type quelconque
 *
 * \copyright PASD
 * \version 2017
 */

typedef struct maillon_struct * maillon;

typedef struct liste_struct * liste;

struct maillon_struct {
	void* val;
	maillon suivant;
};

/*!
 * la structure définit 3 champs supplémentaires qui sont des pointeurs sur fonction
*/
struct liste_struct {
	maillon tete;
	void ( *copier ) ( void * val , void ** pt );
	void ( *afficher ) ( FILE * f , void * val );
	void ( *detruire ) ( void ** pt);
	int ( *comparer )(void* val1, void* val2);
};


liste liste_creer (void (* _copie)(void* val, void** pt), void (* _afficher)(FILE* f, void * val), void (* _detruire)(void** pt),int ( *comparer )(void* val1, void* val2)) ;

void liste_detruire (liste * l);

void liste_insertion_debut (liste l, void * val);

void liste_insertion_fin (liste l, void * val);

maillon* liste_chercher_maillon(liste l ,void* val);

void liste_copier(maillon * m,liste l);

void liste_concatener(liste l1,liste l2);

void liste_supprimer_maillon(liste l,void * val);

void liste_affichage (FILE * f, liste l);

unsigned int liste_taille (liste l);

void* liste_valeur_tete (liste l);

bool liste_est_tete (liste l);

#endif

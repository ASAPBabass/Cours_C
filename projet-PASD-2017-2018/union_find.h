#ifndef UNION_FIND_H
#define UNION_FIND_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
/*! \file union_find.h
 * \brief Implémentation de la structure de données Union-Find.
 *
 *
 * \copyright PASD
 * \version 2017
 */
#include "liste_simplement_chainee.h"

typedef struct ensemble * ensemble;

struct ensemble{
    liste elements;
    long representant;
    int rang;
};

liste creer_liste_ensemble_int(int taille);

ensemble creer_ensemble(int a, void ( * copier ) ( void * val ,void * * pt ), void ( * detruire ) ( void * * pt ), void ( * afficher ) (void* val));

void union_ensemble(liste* l,ensemble* e1, ensemble* e2);

int trouver_ensemble(liste l,int val);

ensemble copier_int(void* a);

void afficher_int(void* a, FILE* f);

void detruire_int(void** a);

liste union_creation(char* fichier);

#endif
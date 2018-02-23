#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <stdio.h>
#include <stdlib.h>
#include "liste_simplement_chainee.h"
/*! \file union_find.h
 * \brief Implémentation de la structure de données Union-Find.
 *
 *
 * \copyright PASD
 * \version 2017
 */

typedef struct ensemble * ensemble;

struct ensemble{
	liste elements;
	int pere;
	int rang;
	int poidsMax;
};

ensemble creer_ensemble(int a);

void copier_int ( void * val ,void * * pt ) ;

void detruire_int ( void * * pt ) ;

void afficher_int( FILE * f , void * val );

void union_ensemble(liste l,ensemble e1, ensemble e2);

ensemble trouver_ensemble(liste l,int val);
    
#endif
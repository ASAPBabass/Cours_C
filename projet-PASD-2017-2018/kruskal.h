#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "union_find.h"
/*! \file kruskal.h
 * \brief Exécution de l'algorithme de Kruskal.
 *
 * La sortie de l'algorithme doit être fournie dans un fichier respectant le format suivant : 
 * u v w(u,v)
 * avec u < v, où (u,v) est une arête et w(u,v) le poids de cette arête.
 *
 * \copyright PASD
 * \version 2017
 */

typedef struct arete * arete;

struct arete{
	int s1,s2,poids;
};

arete creer_arete(int s1,int s2,int poids);

void echanger(arete *tab, int a, int b);

void trier_arete(arete *tab,int debut,int fin);

liste kruskal(arete * tab,int nb_s,int nb_arete);

void copier_arete ( void * val ,void * * pt );

void detruire_arete ( void * * pt ) ;

void detruire_tab_arete( arete* tab);

void afficher_arete(FILE* f, void* val);

int comparer_arete(void *  val1, void * val2 );

void copier_ensemble ( void * val ,void * * pt );

void detruire_ensemble ( void * * pt );

void ensemble_detruire ( ensemble * e );

void afficher_ensemble(FILE* f, void* val);

int comparer_ensemble(void *  val1, void * val2 );

int comparer_arete(void *  val1, void * val2 );

#endif
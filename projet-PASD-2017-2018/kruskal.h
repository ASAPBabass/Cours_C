#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "union_find.h"

typedef struct arete * arete;

struct arete{
    int s1,s2,poids;
};

arete creer_arete(int s1,int s2,int poids){
    arete a = malloc (sizeof(struct arete));
    a->s1=s1;
    a->s2=s2;
    a->poids=poids;
    return a;
}


liste algo_kruskal(char* nom_fichiers);

void echanger(arete *tab, int a, int b);


//void trier_arete(arete *tab,debut,fin);

//liste kruskal(arete * tab,taille,n);

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

#endif
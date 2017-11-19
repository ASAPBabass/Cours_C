#include "kruskal.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>


liste algo_kruskal(char* nom_fichiers){
    return NULL;
}


void echanger(arete *tab, int a, int b)
{
    arete temp = tab[a];
    tab[a] = tab[b];
    tab[b] = temp;
}


void trier_arete(arete *tab,int debut,int fin){	
    int gauche = debut-1;
    int droite = fin+1;
    const arete pivot = (tab[debut])->poids;

    if(debut >= fin)
       	return;

    
    while(1){
		do droite--; while((tab[droite])->poids > pivot);
		do gauche++; while((tab[gauche])->poids < pivot);

		if(gauche < droite)
		    echanger(tab, gauche, droite);
		else break;
    }

	trier_arete(tab, debut, droite);
    	trier_arete(tab, droite+1, fin);
}

// tab estun tableau contenant toutes les arretes du graphe 
//taille est est le nbre d'arrete dans le graphe 
//n est le nbre de sommmets dans le graphe 

liste kruskal(arete * tab,int nb_arete,int nb_s){

	//trie des arete dans un tableau
	trier_arete(tab,0,nb_arete-1);
	
	//initialisation de la liste des ensembles, chaque sommet à son ensemble
    liste l=creer_liste_ensemble_int(nb_s);
	
	//Union des ensembles
    for(int i=0;i<nb_arete;i++){
		/*if(trouver_ensemble((tab[i])->s1))!=trouver_ensemble((tab[i])->s2)){
            union_ensemble(&l,tab[i]->s1,tab[i]->s2]);
        }*/
	}
}
  /*	Entrée : Un graphe G = (V, E) et une fonction de poids ω : E → N.
	Sortie : Un arbre couvrant de poids minimum de G.
	Trier les arêtes E par ordre croissant de poids;
	Ajouter chaque sommet v ∈ V dans un ensemble lui étant propre;
	S ← ∅;
	pour (u, v) ∈ E faire
		si u et v sont dans différents ensembles alors
			S ← S ∪ {(u, v)};
			Regrouper les ensembles contenant u et v;
	Retourner S ;*/
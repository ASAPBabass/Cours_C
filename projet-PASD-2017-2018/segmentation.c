#include "segmentation.h"
#include <math.h>

#define min(a,b) (a <= b ? a : b)

arete* lire_matrice(unsigned int** matrice,int largeur, int hauteur, int* nb_arete){

    arete* t_arete = (arete*) malloc(sizeof(struct arete)*(largeur*hauteur*4));
    int indice = 0;
    int cpt = 0;

    for(int i=0; i < hauteur; i++){
        
        for(int j=0; j < largeur; j++){

            if(j+1 < largeur){ //arete de droite
                t_arete[cpt] = creer_arete(matrice[i][j],matrice[i][j+1],abs(matrice[i][j]-matrice[i][j+1]));
                cpt++;
            }

            if((i+1) < hauteur){ //arete vers le bas
                t_arete[cpt] = creer_arete(matrice[i][j],matrice[i+1][j],abs(matrice[i][j]-matrice[i+1][j]));
                cpt++;
            }

            if((i+1) < hauteur && j-1>=0 ){ //arete diagonal en bas à gauche
                t_arete[cpt] = creer_arete(matrice[i][j],matrice[i+1][j-1],abs(matrice[i][j]-matrice[i+1][j-1]));
                cpt++; 
            }

            if((i+1) < hauteur && (j+1) < largeur){ //arete diagonal en bas à droite
                t_arete[cpt] = creer_arete(matrice[i][j],matrice[i+1][j+1],abs(matrice[i][j]-matrice[i+1][j+1]));
                cpt++;
            }
	    indice++;

        }
 
    }
    *nb_arete = cpt;
    return t_arete;
}


liste segmentation(unsigned int **tab1,arete * tab,int largeur,int hauteur,int nb_aretes,int k){
	trier_arete(tab,0,nb_aretes-1);
	liste l=liste_creer(&copier_ensemble,&afficher_ensemble,&detruire_ensemble,&comparer_ensemble);
	for(int i=0;i<hauteur;i++){
		for(int j=0;j<largeur;j++){
			ensemble e=creer_ensemble(tab1[i][j]);
			liste_insertion_fin(l,e);
			ensemble_detruire(&e);
		}
	}
	for(int i=0;i<nb_aretes;i++){
		ensemble e1=trouver_ensemble(l,(tab[i])->s1);
		ensemble e2=trouver_ensemble(l,(tab[i])->s2);
		if(e1->pere!=e2->pere && (tab[i])->poids<=min(e1->poidsMax+(k/(e1->rang+1)),e2->poidsMax+(k/(e2->rang+1)))){
            e1->poidsMax=tab[i]->poids;
            e2->poidsMax=tab[i]->poids;
            union_ensemble(l,e1,e2);
		}
	}
	return l;
}

/*

arete* lire_matrice(unsigned int** matrice, unsigned int largeur, unsigned int hauteur, int* nb_arete){

    arete* t_arete = (arete*) malloc(sizeof(struct arete)*(largeur*hauteur*4));
    int indice = 0;
    int cpt = 0;

    for(unsigned int i=0; i < hauteur; i++){
        
        for(unsigned int j=0; j < largeur; j++){
            
            if(j+1 < largeur && matrice[i][j+1] ){ //arete de droite

                t_arete[cpt] = creer_arete(indice,indice+1,abs(matrice[i][j]-matrice[i][j+1]));
                cpt++;
               
            }

            if((i+1) < hauteur && matrice[i+1][j]){ //arete vers le bas
                t_arete[cpt] = creer_arete(indice,indice+largeur,abs(matrice[i][j]-matrice[i+1][j]));
                cpt++;
            }

            if((i+1) < hauteur && j<0 && matrice[i+1][j-1] ){ //arete diagonal en bas à gauche
                t_arete[cpt] = creer_arete(indice,indice+largeur-1,abs(matrice[i][j]-matrice[i+1][j-1]));
                cpt++;
            }

            if((i+1) < hauteur && (j+1) < largeur && matrice[i+1][j+1]){ //arete diagonal en bas à droite
                t_arete[cpt] = creer_arete(indice,indice+largeur+1,abs(matrice[i][j]-matrice[i+1][j+1]));
                cpt++;
            } 
            indice++;
        }

        
                
    }
    *nb_arete = cpt;
    return t_arete;
}

liste segmentation(arete * tab,int nb_s,int nb_arete,int k){
    trier_arete(tab,0,nb_arete-1);
	liste l=liste_creer(&copier_ensemble,&afficher_ensemble,&detruire_ensemble,&comparer_ensemble);
	for(int i=0;i<nb_s;i++){
        ensemble e=creer_ensemble(i);
        e->rang++;
		liste_insertion_fin(l,e);
		ensemble_detruire(&e);
	}
	for(int i=0;i<nb_arete;i++){
        ensemble e1 = trouver_ensemble(l,(tab[i])->s1);
		ensemble e2 = trouver_ensemble(l,(tab[i])->s2);
		if(e1->pere!=e2->pere){
			union_ensemble(l,e1,e2);
		}
	}
	return l;

}

*/
/*int filtre_segmentation(ensemble e1,ensemble e2, arete a){

    int k=50;
    if(a->poids <= min((e1->poidsMax+(k/e1->rang)),(e2->poidsMax+(k/e2->rang)))) return 1;
    else return 0;
}*/



/*
    Int(C) : C est une composante de V, Int(C) représente le poids le plus grand de la composante

    La différence entre 2 composantes C1,C2 comprit dans V est l'arete de poids minimun connectant les deux composantes
        - Dif(C1,C2) = min (w(vi,vj))
*/
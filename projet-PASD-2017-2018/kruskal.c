#include "kruskal.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>



arete creer_arete(int s1,int s2,int poids){
	arete a=malloc(sizeof(struct arete));
	a->s1=s1;
	a->s2=s2;
	a->poids=poids;
	return a;
}

void copier_arete ( void * val ,void * * pt ) {
	assert ( NULL != val ) ;
  	assert ( NULL != pt ) ;
	arete a=(arete)val;
	arete a1 = creer_arete(a->s1,a->s2,a->poids);
	*pt = a1;
}


void detruire_arete ( void * * pt ) {
  	assert ( NULL != pt ) ;
	if ( * pt != NULL ) {
		free((arete *) (*pt));
	}
}

void detruire_tab_arete( arete* tab){
	int i=0;
	while(NULL!=tab[i]){
		free(tab[i]);
		(tab[i])=NULL;
		i++;
	}
	free(tab);
	tab=NULL;

}

int comparer_arete(void *  val1, void * val2 ){
	assert ( NULL != val1 ) ;
	assert ( NULL != val2 ) ;
	arete a1=*(arete*)(val1);
	arete a2=*(arete*)(val2);
	return (a1->s1==a2->s2 && a1->s2==a2->s2 && a1->poids==a2->poids);
	
}
void afficher_arete(FILE* f, void* val){
	assert ( NULL != val ) ;
	arete a=(arete) val;
  	fprintf(f,"%d %d %d",a->s1,a->s2,a->poids);
}

void copier_ensemble ( void * val ,void * * pt ) {
	assert ( NULL != val ) ;
  	assert ( NULL != pt ) ;
	ensemble e=(ensemble)val;
	ensemble e1 = creer_ensemble(*(int*)e->elements->tete->val);
	*pt = e1;
}

void ensemble_detruire ( ensemble * e ) {
	if ( (*e) != NULL ) {
		liste_detruire(&((*e)->elements));
		free(*e);
		*e=NULL;
	}
}

void detruire_ensemble ( void * * pt ) {
  	assert ( NULL != pt ) ;
	if((*pt)!=NULL){
		ensemble_detruire((ensemble*) pt);
	}
}

void afficher_ensemble(FILE* f, void* val){
	assert ( NULL != val ) ;
	ensemble e=(ensemble) val;
  	liste_affichage(f,e->elements);
}

int comparer_ensemble(void *  val1, void * val2 ){
	assert ( NULL != val1 ) ;
	assert ( NULL != val2 ) ;
	ensemble e1=*(ensemble*)(val1);
	ensemble e2=*(ensemble*)(val2);
	if(e1->rang!=e2->rang) return 0;
	else{
		maillon* m1=&(e1->elements->tete);
		maillon* m2=&(e2->elements->tete);
		while(NULL!=(*m1)->val && NULL!=(*m2)->val){
			if((*m1)->val!=(*m2)->val) return 0;
			m1=&((*m1)->suivant);
			m2=&((*m2)->suivant);
		}
		return 1;
	}
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

	const arete pivot = tab[debut];
    if(debut >= fin)
       	return;

    
    while(1){
		do droite--; while((tab[droite])->poids > pivot->poids || ((tab[droite]->poids == pivot->poids) && (tab[droite]->s1 > pivot->s1)) || ((tab[droite]->poids == pivot->poids) && (tab[droite]->s1 == pivot->s1) && (tab[droite]->s2 > pivot->s2)));// || (tab[droite]->poids == pivot->poids && tab[gauche]->s1 > pivot->s1));
		do gauche++; while((tab[gauche])->poids < pivot->poids || ((tab[gauche]->poids == pivot->poids) && (tab[gauche]->s1 < pivot->s1)) || ((tab[gauche]->poids == pivot->poids) && (tab[gauche]->s1 == pivot->s1) && (tab[gauche]->s2 < pivot->s2)));
		//((tab[gauche]->poids) == (pivot->poids) && (tab[gauche])->s1 < pivot->s1);


		if(gauche < droite){ //((tab[droite]->poids == tab[gauche]->poids) && (tab[droite]->s1 < tab[gauche]->s1)))){
		    echanger(tab, gauche, droite);
		}else{
			break;
		}
    }

	trier_arete(tab, debut, droite);
    trier_arete(tab, droite+1, fin);
}


liste kruskal(arete * tab,int nb_s,int nb_arete){
	trier_arete(tab,0,nb_arete-1);

	liste l=liste_creer(&copier_ensemble,&afficher_ensemble,&detruire_ensemble,&comparer_ensemble);
	liste s=liste_creer(&copier_arete,&afficher_arete,&detruire_arete,&comparer_arete);
	for(int i=0;i<nb_s;i++){
		ensemble e=creer_ensemble(i);
		liste_insertion_fin(l,e);
		ensemble_detruire(&e);
	}
	for(int i=0;i<nb_arete;i++){
		ensemble e1 = trouver_ensemble(l,(tab[i])->s1);
		ensemble e2 = trouver_ensemble(l,(tab[i])->s2);

		if(e1->pere!=e2->pere){
			union_ensemble(l,e1,e2);
			liste_insertion_fin(s,tab[i]);
		}
	}
	liste_detruire(&l);
	return s;
	
}

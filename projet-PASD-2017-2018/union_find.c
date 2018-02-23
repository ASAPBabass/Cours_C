#include "union_find.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

//IMPLEMENTATION DE LA LISTE CHAINEE

void copier_int ( void * val ,void * * pt ) {
	assert ( NULL != val ) ;
  	assert ( NULL != pt ) ;
  	* pt = ( int * ) malloc ( sizeof ( int ) ) ;
  	assert ( NULL != * pt ) ;
	memcpy ( * pt , val , sizeof ( int ) ) ;
}


void detruire_int ( void * * pt ) {
  	assert ( NULL != pt ) ;
	if ( * pt != NULL ) {
		free ( * pt ) ;
	    	( * pt ) = NULL ;
	}
}

void afficher_int(FILE* f, void* val){
	assert ( NULL != val ) ;
  	fprintf(f,"%d",*((int*)(val)));
}

int comparer_int(void *  val1, void * val2 ){
	assert ( NULL != val1 ) ;
	assert ( NULL != val2 ) ;
	return *((int*)(val1))=*((int*)(val2));
	
}

ensemble creer_ensemble(int a){
	ensemble e = malloc(sizeof(struct ensemble));
	e->elements = liste_creer(&copier_int, &afficher_int, &detruire_int,&comparer_int);
	liste_insertion_debut(e->elements,&a);
    e->pere=a;
	e->rang=0;
	e->poidsMax=0;
	return e;
}

void union_ensemble(liste l,ensemble e1, ensemble e2){
	assert(e1!=NULL);
	assert(e2!=NULL);
	assert(l!=NULL);
	if(e1->rang>e2->rang || (e1->rang==e2->rang && e1->pere>e2->pere)){
        	liste_concatener(e1->elements,e2->elements);
		e2->pere=e1->pere;
        	liste_supprimer_maillon(l,e2);
		e1->rang+=e2->rang;
    }else{
        	liste_concatener(e2->elements,e1->elements);
		e1->pere=e2->pere;
        	liste_supprimer_maillon(l,e1);
		e2->rang+=e2->rang;
    }
	
}

int cherche_valeur(ensemble e, int val){
	maillon* m=&(e->elements->tete);
	while(NULL!=*m){
		if(*(int*)((*m)->val)==val) return 1;
		m=&((*m)->suivant);
	}
	return 0;
}

ensemble trouver_ensemble(liste l,int val){
    	maillon* m=&(l->tete);
    	while(*m!=NULL){
       		ensemble e=(ensemble) ((*m)->val);
			if(cherche_valeur(e,val)==1) return e;
      		m=&((*m)->suivant);
		}
		return NULL;
}
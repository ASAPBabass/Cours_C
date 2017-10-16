# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

# undef NDEBUG

# include "arbres.h"


typedef struct noeud_struct * noeud ;


struct noeud_struct {
	void * val;
	noeud f_d;
	noeud f_g; 
} ; 


struct arbre_struct {
	noeud racine;
	void ( * copier ) ( void * val ,void * * pt );
	void ( * detruire ) ( void * * pt );
	int ( *comparer) (void* val1, void* val2);
} ; 


static noeud noeud_creer ( void * val ,void ( * copier ) ( void * val ,void * * pt ) ) {  
	noeud n=malloc(sizeof(struct noeud_struct));
	copier(val,&(n->val));
	n->f_d=NULL;
	n->f_g=NULL;
  	return n ;
}


/* Détruit un noeud et tous les noeuds se trouvant en dessous. */
static void noeud_detruire_recursivement ( noeud * n_pt ,void ( * detruire ) ( void * * pt ) ) {
	if(NULL!=n_pt){
		if(NULL!=(*n_pt)->f_d) noeud_detruire_recursivement(&((*n_pt)->f_d),detruire);
		if(NULL!=(*n_pt)->f_g) noeud_detruire_recursivement(&((*n_pt)->f_g),detruire);
		detruire(&((*n_pt)->val));
		free(*n_pt);
		*n_pt=NULL;
	}
}

/* Détruit un noeud sans détruire les noeuds se trouvant en dessous.
 Il faut donc assurer la correcte structure de l'arbre de recherche après suppression.*/

static void noeud_detruire_simple ( noeud * const n_pt ,void ( * detruire ) ( void * * pt ) ) {
	if(NULL!=((*n_pt)->f_d)){
		void * echange=(*n_pt)->val;
		((*n_pt)->val)=((*n_pt)->f_d->val);
		(*n_pt)->f_d->val=echange;
		noeud_detruire_simple(&((*n_pt)->f_d),detruire);

	}
	else if(NULL!=((*n_pt)->f_g)){
		noeud n=*n_pt;
		*n_pt=((*n_pt)->f_g);
		detruire(&(n->val));
		free(n);
		n=NULL;
		
		
	}
	else{
		detruire(&((*n_pt)->val));
		free(*n_pt);
		*n_pt=NULL;
	}
}

static void noeud_afficher_prefixe ( noeud n ,FILE * f ,void ( * afficher ) ( void * val ,FILE * f ) ) {
	if(n!=NULL){
		afficher(n->val,f);
		if(n->f_g!=NULL) noeud_afficher_prefixe(n->f_g,f,afficher);
		if(n->f_d!=NULL) noeud_afficher_prefixe(n->f_d,f,afficher);
	}
}



static void noeud_afficher_infixe ( noeud n ,FILE * f ,void ( * afficher ) ( void * val ,FILE * f ) ) {
	if(n!=NULL){
		if(n->f_g!=NULL){
			noeud_afficher_infixe(n->f_g,f,afficher);
		}

		afficher(n->val,f);

		if(n->f_d!=NULL){
			 noeud_afficher_infixe(n->f_d,f,afficher);
		}

	}
	
}


static void noeud_afficher_postfixe ( noeud n , FILE * f ,void ( * afficher ) ( void * val ,FILE * f ) ) {
	if(n!=NULL){
		if(n->f_g!=NULL) noeud_afficher_prefixe(n->f_g,f,afficher);
		if(n->f_d!=NULL) noeud_afficher_prefixe(n->f_d,f,afficher);
		afficher(n->val,f);
	}
}


int noeud_taille ( noeud n ) {
	if(n==NULL) return 0;
	else return 1+(noeud_taille(n->f_g))+noeud_taille(n->f_d);
}


arbre arbre_creer ( void ( * copier ) ( void * val ,void * * pt ) , void ( * detruire ) ( void * * pt ) ,int ( * comparer ) ( void * val1 , void* val2 ) ) {
	arbre a=malloc(sizeof(struct arbre_struct));
	a->racine=NULL;
	a->copier=copier;
	a->detruire=detruire;
	a->comparer=comparer;
	return a ;
}

void arbre_detruire ( arbre * a ) {
	noeud_detruire_recursivement(&((*a)->racine),(*a)->detruire);
	free(*a);
	*a=NULL;
}

/*
 * Simplifier largement insertion, recherche et suppression
 * (factorisation de code !)
 */
static noeud* arbre_chercher_position(arbre a, void* val){
	noeud* n = &(a->racine);
	while ((*n) != NULL) {
		int comp = a->comparer(val,(*n)->val);
	    	if (comp<=-1) 
		 	n = &((*n)->f_g);
		else if (comp>=1) 
		      	n = &((*n)->f_d);
		else 
			return n;
	  }
	  return n;
}

void arbre_insertion ( arbre a ,void * val ) {
	if(a->racine==NULL) a->racine=noeud_creer(val,a->copier);
	else{
		int comp=(a->comparer)(a->racine->val,val);
		noeud racine=a->racine;
		if(comp>=1){
			if(a->racine->f_g==NULL){
				(a->racine)->f_g=noeud_creer(val,a->copier);
			}
			else{
				a->racine=a->racine->f_g;
				arbre_insertion(a,val);
			}
		}
		if(comp<=-1){
			 if(a->racine->f_d==NULL){
				(a->racine)->f_d=noeud_creer(val,a->copier);;
			}
			else{
				a->racine=a->racine->f_d;
				arbre_insertion(a,val);
			}
		}
		a->racine=racine;
	}
}

void arbre_afficher_prefixe ( arbre a ,FILE * f ,void ( * afficher ) ( void * val ,FILE * f ) ) {
	noeud_afficher_prefixe(a->racine,f,afficher);
}

void arbre_afficher_infixe ( arbre a ,FILE * f ,void ( * afficher ) ( void * val ,FILE * f ) ) {
	noeud_afficher_infixe(a->racine,f,afficher);
}

void arbre_afficher_postfixe ( arbre a ,FILE * f ,void ( * afficher ) ( void * val ,FILE * f ) ) {
	noeud_afficher_postfixe(a->racine,f,afficher);
}


bool arbre_est_vide ( arbre a ) {
	return ( a!=NULL || (a->racine->val!=NULL && a->racine->f_d!=NULL && a->racine->f_d!=NULL));
}


int arbre_taille ( arbre a ) {
  return noeud_taille(a->racine);
}



void * arbre_rechercher ( arbre a ,void * val ) {
	noeud* racine=arbre_chercher_position(a,val);
	if(NULL!=racine){
		 return (*racine)->val;
	}
	return racine;
}


void arbre_supprimer ( arbre a ,void * val ) {
	noeud* n=arbre_chercher_position(a,val);
	if((*n)!=NULL){
		noeud_detruire_simple(n,a->detruire);
	}
}



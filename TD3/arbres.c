#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#undef NDEBUG

#include "arbres.h"

/*!
 * \file
 * \brief
 * Les implémentations des deux structures arbre (cf arbres.h) et noeud
 * cette dernière est cachée et permet de construire effectivement l'arbre binaire
 * les fonctions associées à noeud sont donc "static"
 * \copyright PASD
 * \version 2017 
 */

typedef struct noeud_struct* noeud ;

struct noeud_struct {
	void* val;
	noeud f_g;
	noeud f_d;

} ; 


struct arbre_struct {
	noeud racine;
	void ( * copier ) ( void * val ,void * * pt );
	void ( * detruire ) ( void * * pt );
	int ( *comparer) (void* val1, void* val2);
}; 


/*!
 * Création d'un noeud
 * \param val la valeur affectée à ce noeud à partir d'une copie
 * \param copier fonction pour copier les valeurs au sein d'un noeud
 * \return un noeud feuille initialisé à val
 */
static noeud noeud_creer(void* val, void(*copier)(void *val, void** pt))
{
	noeud n=malloc(sizeof(struct noeud_struct));
	copier(val,&(n->val));
	//n->f_d=malloc(sizeof(struct noeud_struct));
	//n->f_g=malloc(sizeof(struct noeud_struct));
	n->f_g=NULL;
	n->f_d=NULL;  
	
	return n ;
}


/*!
 * Destruction d'un noeud et de tous les noeuds se trouvant en dessous. 
 * \param n_pt le noeud départ de la destruction (remis à NULL à la fin)
 * \param detruire la fonction permettant de détruire la valeur au sein du noeud
 */
static void noeud_detruire_recursivement(noeud* n_pt, void(*detruire)(void** pt)) {
	
	if(!n_pt) return;
	if((*n_pt)->f_g) noeud_detruire_recursivement(&((*n_pt)->f_g),detruire);
	if((*n_pt)->f_d) noeud_detruire_recursivement(&((*n_pt)->f_d),detruire);
	detruire(n_pt);
	n_pt=NULL;

}


/*!
 * Détruit un noeud sans détruire les noeuds se trouvant en dessous.
 * Il faut donc assurer la structure de l'arbre binaire de recherche après la suppression.
 * \param n_pt noeud à détruire car il contient la valeur à supprimer
 * \param detruire la fonction permettant de détruire une valeur au sein d'un noeud
 */
static void noeud_detruire_simple(noeud* const n_pt, void(* detruire)(void** pt ))
{
	/*noeud* temp=NULL;
	if(*n_pt!=NULL){
		if((*n_pt)->f_g==NULL && (*n_pt)->f_d==NULL){
			detruire(n_pt);
		}
		else if((*n_pt)->f_d==NULL){		
			(*n_pt)->val = (*n_pt)->f_g->val;
			noeud_detruire_simple(&((*n_pt)->f_g),detruire);
		}else{
			temp = &((*n_pt)->f_d);
			while((*temp)->f_g!=NULL){
				(temp) = &((*temp)->f_g);
			}
			(*n_pt)->val = (*temp)->val;
			noeud_detruire_simple(&((*n_pt)->f_d),detruire);
		
		}

	}*/
	if(NULL!=((*n_pt)->f_d)){
		if(NULL==((*n_pt)->f_d)->f_g){
			((*n_pt)->val)=((*n_pt)->f_d->val);
			noeud_detruire_simple(&((*n_pt)->f_d),detruire);
		}else{
			noeud* temp = &((*n_pt)->f_g);
			while(NULL!=(*temp)->f_g){
				*temp = (*temp)->f_g;
			}
			(*n_pt)->val = (*temp)->val;
			detruire(temp);
		//noeud_detruire_simple(&((*n_pt)->f_g),detruire);
		}
	}else if(NULL!=((*n_pt)->f_g)){
		noeud* x=&((*n_pt)->f_g);		
		*n_pt=((*n_pt)->f_g);
	/*	noeud * temp = &((*n_pt)->f_d);
		while((*temp)->f_g!=NULL){
			(temp) = &((*temp)->f_g);
		}
		(*n_pt)->val = (*temp)->val;
		noeud_detruire_simple(&((*n_pt)->f_d),detruire);
	*/
	}else{
		detruire(n_pt);
	}

}

/*! 
 * affichage selon le parcours prefixe à partir d'un noeud donné
 * \param n le noeud débutant l'affichage
 * \param f le flux de sortie
 * \param afficher la fonction permettant d'afficher la valeur au sein d'un noeud
 */
static void noeud_afficher_prefixe(noeud n, FILE* f, void(* afficher)(void* val, FILE* f)) {
	if(n!=NULL){
		afficher(n->val,f);
		if(n->f_g!=NULL) noeud_afficher_prefixe(n->f_g,f,afficher);
		if(n->f_d!=NULL) noeud_afficher_prefixe(n->f_d,f,afficher);
	}
}

/*! 
 * affichage selon le parcours infixe à partir d'un noeud donné
 * \param n le noeud débutant l'affichage
 * \param f le flux de sortie
 * \param afficher la fonction permettant d'afficher la valeur au sein d'un noeud
 */
static void noeud_afficher_infixe(noeud n, FILE * f, void(* afficher)(void* val, FILE * f))
{
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

/*! 
 * affichage selon le parcours postfixe à partir d'un noeud donné
 * \param n le noeud débutant l'affichage
 * \param f le flux de sortie
 * \param afficher la fonction permettant d'afficher la valeur au sein d'un noeud
 */
static void noeud_afficher_postfixe(noeud n, FILE * f, void(* afficher)(void* val, FILE * f))
{
	if(n!=NULL){
		if(n->f_g!=NULL) noeud_afficher_prefixe(n->f_g,f,afficher);
		if(n->f_d!=NULL) noeud_afficher_prefixe(n->f_d,f,afficher);
		afficher(n->val,f);
	}
}

/*!
 * 1+le nombre de noeud en dessous du noeud donné
 * \param n le noeud de départ
 * \return le nombre de noeuds à partir de n
 */
int noeud_taille(noeud n) {
	if(n==NULL) return 0;
	else return 1+(noeud_taille(n->f_g))+noeud_taille(n->f_d);
}


arbre arbre_creer(void(* copier)(void* val, void** pt), void(* detruire)(void** pt), int(* comparer)(void *val1, void * val2))
{
	arbre a=malloc(sizeof(struct arbre_struct));
	a->racine= malloc(sizeof(struct noeud_struct));
	//(a->racine)->f_g=malloc(sizeof(struct noeud_struct));
	//(a->racine)->f_d=malloc(sizeof(struct noeud_struct));
	//(a->racine)->f_g=NULL;
	//(a->racine)->f_d=NULL;
	a->copier=copier;
	a->detruire=detruire;
	a->comparer=comparer;
	return a ;
}


void arbre_detruire(arbre* a ) {
	noeud_detruire_recursivement(&((*a)->racine),(*a)->detruire);
	(*a)->detruire(a);
	
}

/*!
 * A compléter
 */

static noeud* arbre_chercher_position(arbre a, void* val)
{
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



void arbre_insertion(arbre a, void *val )
{
	if(a->racine->val==NULL) a->racine=noeud_creer(val,a->copier);
	else{
		noeud racine=(a->racine);
		if(((a->comparer)(a->racine->val,val))>0){
			if(a->racine->f_g==NULL){
				(a->racine)->f_g=noeud_creer(val,a->copier);
			}
			else{
				a->racine=a->racine->f_g;
				arbre_insertion(a,val);
			}
		}
		if(((a->comparer)(val,a->racine->val))>0){
			 if(a->racine->f_d==NULL){
				(a->racine)->f_d=noeud_creer(val,a->copier);
			}
			else{
				a->racine=a->racine->f_d;
				arbre_insertion(a,val);
			}
		}
		a->racine=racine;
	}
}


void arbre_afficher_prefixe(arbre a, FILE * f, void(* afficher)(void * val, FILE * f))
{  
	noeud_afficher_prefixe(a->racine,f,afficher);
}

void arbre_afficher_infixe(arbre a, FILE * f, void(* afficher)(void* val, FILE* f))
{
	noeud_afficher_infixe(a->racine,f,afficher);
}

void arbre_afficher_postfixe(arbre a, FILE * f, void(* afficher)(void* val, FILE* f))
{
	noeud_afficher_postfixe(a->racine,f,afficher);
}


bool arbre_est_vide(arbre a)
{
  if(a->racine==NULL) return 1;
  else return -1;
}



int arbre_taille(arbre a )
{
	return noeud_taille(a->racine);
}



void* arbre_rechercher(arbre a, void* val) {
	noeud* racine=arbre_chercher_position(a,val);
	if(NULL!=*racine){
		return (*racine)->val;
	}else return NULL;
}


void arbre_supprimer(arbre a, void* val)
{
	noeud* racine=arbre_chercher_position(a,val);
	if((*racine)!=NULL){
		noeud_detruire_simple(racine,a->detruire);
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "liste_simplement_chainee.h"

/*! \file listes_generiques.c
 * \brief L'implémentation des fonctions
 * Les définitions des fonctions sont identiques à celles de liste des entiers.
 * Mais certaines nécessitent un paramètre supplémentaire la fonction copier 
 * afficher ou detruire qui permettent de rendre générique la liste.
 * Pour l'essentiel il s'agit de reprendre les fonctions pour les listes 
 * d'entiers et de les adapter à la généricité .
 *
 * \copyright PASD
 * \version 2017
 */


static maillon maillon_creer(void * val, void(*copier)(void* val, void** pt)) {
	maillon m=malloc(sizeof(struct maillon_struct));
	copier(val,&(m->val));
	m->suivant=NULL;
	return m;
	
}

static void maillon_detruire_simple(maillon* m, void(* detruire)(void** pt)) {
	detruire(&((*m)->val));
	free(*m);
	*m=NULL;
}

static void maillon_detruire(maillon* m, void(* detruire)(void** pt)) {
	if((*m)->suivant==NULL){
		detruire(&((*m)->val));
		free(*m);
		*m=NULL;
	}
	else maillon_detruire(&((*m)->suivant),detruire);
}


static void maillon_afficher(FILE* f, maillon m_debut, void(* afficher )(FILE *f, void* val)) {
	maillon curseur=m_debut;
	assert(NULL!=curseur);
	while(curseur!=NULL){
		afficher(f,curseur->val);
		//fprintf(f,"\n");
		curseur=curseur->suivant;
	}
	//fprintf(f,"\n");
}

static maillon maillon_precedent(liste l,maillon m){
	maillon* m1=&(l->tete);
	while(*m1!=NULL && m->suivant->val!=m->val){
		m1=&((*m1)->suivant);
	}
	return *m1;
}

static void maillon_ajouter_avant( void* _val,maillon m, void(*copier)(void* val, void** pt)) {
	maillon m_avant=maillon_creer(_val,copier);
	m_avant->suivant=m;
}


/*static void maillon_ajouter_apres(maillon m, void * _val, void(*copier)(void* val, void** pt)) {
	maillon m_apres=maillon_creer(_val,copier);
	if(m->suivant==NULL) m->suivant=m_apres;
	else{
		m->suivant=m_apres;
	}
}*/

liste liste_creer(void(*_copier)(void* val, void** pt),void(*_afficher)(FILE *f, void* val),void(* _detruire )(void** pt),int(*_comparer)(void* val1, void* val2)) {
	liste l=malloc(sizeof(struct liste_struct));
	l->tete=NULL;
	l->copier=_copier;
	l->afficher=_afficher;
	l->detruire=_detruire;
	l->comparer=_comparer;
	return l;
}


void liste_detruire(liste* l){
	 if (*l != NULL) {
		maillon_detruire(&((*l)->tete),(*l)->detruire);
	    	free(*l);
	    	*l= NULL;
 	 }	
}


void liste_insertion_debut(liste l, void* val){
	if(NULL==l->tete) l->tete=maillon_creer(val,l->copier);
	else maillon_ajouter_avant(val,l->tete,l->copier);
	
}

void liste_insertion_fin(liste l, void* val){
	if(NULL==l->tete) l->tete=maillon_creer(val,l->copier);
	else{
		maillon* p=&(l->tete);
		while(NULL!=(*p)->suivant){
			p=&((*p)->suivant);
		}
		(*p)->suivant=maillon_creer(val,l->copier);
	}
	
}

maillon* liste_chercher_maillon(liste l ,void* val){
	maillon* curseur=&(l->tete);
	while(NULL!=*curseur && (*curseur)->val!=val){
		curseur=&((*curseur)->suivant);
	}
	return curseur;
}

void liste_copier(maillon *m,liste l){
	maillon* curseur=&(l->tete);
	maillon* curseur1=m;
	while(*curseur!=NULL){
		*curseur1=maillon_creer((*curseur)->val,l->copier);
		curseur=&((*curseur)->suivant);
		curseur1=&((*curseur1)->suivant);
		
	}
}

void liste_concatener(liste l1,liste l2){
	assert(NULL!=l1);
	assert(NULL!=l2);
	maillon curseur=l1->tete;
	while(curseur->suivant!=NULL){
		curseur=curseur->suivant;
	}
	liste_copier(&(curseur->suivant),l2);
	
}

void liste_supprimer_maillon(liste l,void * val){
	if(l->tete->val==val){
		maillon m=l->tete->suivant;
		maillon_detruire_simple(&(l->tete),l->detruire);
		l->tete=m;
	}
	else{
		maillon*m=&(l->tete);
		while(NULL!=(*m)->suivant){
			if((*m)->suivant->val==val){
				maillon m1=(*m)->suivant->suivant;
				maillon_detruire_simple(&((*m)->suivant),l->detruire);
				(*m)->suivant=m1;	
			}
			m=&((*m)->suivant);
		}
	}
}

void liste_affichage(FILE* f,liste l){
	fprintf(f,"[");
	maillon_afficher(f,l->tete,l->afficher);
	fprintf(f,"]\n");
}

void * liste_valeur_tete(liste l){
	return l->tete->val;
}

bool liste_est_tete(liste l){
	return (l->tete==NULL);
}


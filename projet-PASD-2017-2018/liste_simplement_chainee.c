#include "liste_simplement_chainee.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>


//CHAINE
maillon creer_maillon_vide(){
    maillon ch = malloc(sizeof(struct maillon));
    ch->val=NULL;
    ch->suivant=NULL;
    return ch;
}

maillon maillon_creer(void* val,void* ( * copier ) ( void * val )){
    maillon ch = malloc(sizeof(struct maillon));
    ch->val=copier(val);
    ch->suivant=NULL;
    return ch;
}
/*
void maillon_afficher(maillon* m,char* fichier, void ( * afficher ) (void* val)){
    afficher()
}*/

void maillon_detruire(maillon* m,void ( * detruire ) ( void * * pt )){

    maillon_supprimer(&((*m)->suivant),detruire);
    detruire(&((*m)->val));
    free(m);
    *m=NULL;
}

void maillon_detruire_simple(maillon* m,void ( * detruire ) ( void * * pt )){    
        detruire(&((*m)->val));
        free(m);
        *m=NULL;
}

//LISTE

liste creer_liste_vide(){
    liste l = malloc(sizeof(struct liste));
    l->tete=NULL;
    l->taille=0;
}

liste creer_liste(void* ( * copier ) ( void * val ), void ( * detruire ) ( void * * pt ), void ( * afficher ) (void* val, FILE * f)){
    
    liste l = malloc(sizeof(struct liste));
    l->tete=NULL;
    l->copier=copier;
    l->afficher=afficher;
    l->detruire=detruire;

    return l;
}

int liste_a_tete(liste l){
    if (l->tete!=NULL) return 1;
    else return 0; 
}

maillon* liste_rechercher(liste l, void* val){

    maillon *p=&(l->tete);
    while(NULL!=p && (*p)->val!=val){
        p=&((*p)->suivant);
    }
    return p;
}

liste* liste_inserer_maillon_fin(liste* l,void* val){

    if(1==liste_a_tete(l)){
        (*l)->tete=maillon_creer(val,(*l)->copier);
    }else{
        maillon* p=&((*l)->tete);
        while(NULL!=(*p)->suivant){
            p=(*p)->suivant;
        }
        p=maillon_creer(val,(*l)->copier);
    }
    return l;
}

liste liste_inserer_maillon_debut(liste l,void* val){
    if(1==liste_a_tete(l)){
        l->tete=maillon_creer(val,l->copier);
    }else{
        maillon m = maillon_creer(val,l->copier);
        m->suivant=l->tete;
        l->tete=m;
    }
    return l;
}

liste* liste_concatener(liste* a, liste* b){
    if((*a)->taille > (*b)->taille){
        liste_inserer_maillon_fin(a,&((*b)->tete),(*a)->copier);
        (*a)->taille+=(*b)->taille;
        return a;
    }else{
        liste_inserer_maillon_fin(b,&((*a)->tete),(*a)->copier);
        (*b)->taille+=(*a)->taille;
        return b;
    }
}

int liste_contient_maillon(liste l, maillon ch){
    maillon* p = l->tete;
    while(p!=NULL){
        if(p->val==ch->val){
            return 1; //VRAI
        }
        p=p->suivant;
    }
    return 0; //FAUX
}

maillon* liste_acceder_maillon(liste l, void* val){
    
}

liste* liste_supprimer_maillon(liste* l,void* val,void ( * detruire ) ( void * * pt )){
    maillon* ptr = &((*l)->tete);
    maillon* ptr2;
    while(NULL!=ptr && (*ptr)->val!=val){
        ptr2 = ptr;
        ptr=(&((*l)->suivant));
    }
    if(ptr!=NULL{
        (*ptr2)->suivant=(*ptr)->suivant;
        maillon_detruire_simple(ptr,detruire);
    }
    return l;
}

liste liste_supprimer(liste* l,void ( * detruire ) ( void * * pt )){
    maillon_supprimer(&(l->tete),detruire);
    free(l);
    *l=NULL;
}

void afficher_liste_union(liste* l,char* fichier,void ( * afficher ) ( void * val , FILE * f )){
    FILE f = fopen(fichier);

    maillon* m = &(l->tete);
    while(m!=NULL){

        maillon_afficher(m,fichier,afficher);
        afficher((*m)->val->representant,f);
        if(NULL!=(*m)->val->elements){
            afficher((*m)->val->elements,f);
        }
        m=&((*m)->suivant);
    }
    f.close();
}
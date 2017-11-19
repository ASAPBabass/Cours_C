#include "union_find.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

//IMPLEMENTATION DE LA LISTE CHAINEE

ensemble copier_int(void* a){
    ensemble p = malloc(sizeof(struct ensemble));
    p->elements=creer_liste(copier_int,detruire_int,afficher_int);
    liste_inserer_maillon_debut(p->elements,a);
    p->representant=(long) p->elements->tete->val;
    p->rang=0;
    return p;
}

void afficher_int(void* a, FILE* f){
    ensemble e = (ensemble) a;
    maillon* m = &(e->elements->tete);
    
    while(NULL!=m){
        fprintf(f,"%p",(*m)->val);
    }

}

void detruire(void** a){
    ensemble* e = (ensemble*) a;
    liste_supprimer((*e)->elements,(*e)->elements->detruire);
    free(e);
    *e=NULL;
}


liste creer_liste_ensemble_int(int taille){ // r est un MAILLON
    liste l = creer_liste(copier_int,detruire_int,afficher_int);
    for(int i=0;i<taille;i++){
        liste_inserer_maillon_fin(l,creer_ensemble(i,l->copier,l->detruire,l->afficher));
    }
    return l;
}

ensemble creer_ensemble(int a, void ( * copier ) ( void * val ,void * * pt ), void ( * detruire ) ( void * * pt ), void ( * afficher ) (void* val)){
    ensemble p = malloc(sizeof(struct ensemble));
    p->elements=creer_liste(copier,detruire,afficher);
    liste_inserer_maillon_debut(p->elements,a);
    p->representant=p->elements->tete;
    p->rang=0;
    return p;
}

void union_ensemble(liste* l,ensemble* e1, ensemble* e2){

    if((*e1)->rang > (*e2)->rang || (((*e1)->rang == (*e2)->rang) && ((*e1)->representant) > (*e2)->representant)){
        liste_concatener(&((*e1)->elements),&((*e2)->elements));
        (*e1)->rang++;
        liste_supprimer_maillon(&l,e2,(*l)->detruire);
    }else{
        liste_concatener(&((*e2)->elements),&((*e1)->elements));
        (*e2)->rang++;
        liste_supprimer_maillon(&l,e1,(*l)->detruire);
    }
}

int trouver_ensemble(liste l,int val){
    maillon* m=l->tete;
    while((*m)!=NULL){
        //on caste la valeur du maillon en un ensemble
        ensemble* e =(ensemble*) &(*m)->val; 
        for(int i=0;i<(*e)->rang;i++){
            if(NULL!=liste_rechercher((*e)->elements,val)){
                return (*e)->representant;
            }
        }
        m=&((*m)->suivant);
    }
    printf("PAS TROUVER");
    return NULL;
}


/*
liste union_creation(char* fichier){
    
    FILE* input=fopen(fichier,"r");
    fscanf(input,"%d",taille);
    
    liste l = creer_liste_vide(taille); //liste de taille sommets

    while(input!=EOF){
        fscanf(input,"%d %d %d",s1,s2,arete);
        
        

    }

    fclose(input);
}*/



//IMPLEMENTATION DE LA FORET
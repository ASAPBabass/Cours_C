#ifndef LISTE_SIMPLEMENT_CHAINEE_H
#define LISTE_SIMPLEMENT_CHAINEE_H


typedef struct maillon * maillon;

struct maillon{
    void* val;
    maillon suivant;
    //maillon pere; REPRESENTANT
};

typedef struct liste * liste;

struct liste{
    maillon tete;
    void* ( * copier ) ( void * val );
	void ( * detruire ) ( void * * pt );
	void ( * afficher ) (void* val);
};


//CHAINE
maillon creer_maillon_vide();

maillon maillon_creer(void* val,void* ( * copier ) ( void * val ));

void maillon_detruire(maillon* m,void ( * detruire ) ( void * * pt ));

void maillon_detruire_simple(maillon* m,void ( * detruire ) ( void * * pt ));

//LISTE

liste creer_liste_vide();

liste creer_liste(void* ( * copier ) ( void * val ), void ( * detruire ) ( void * * pt ), void ( * afficher ) (void* val));

int liste_a_tete(liste l);

maillon* liste_rechercher(liste l, void* val);

liste* liste_inserer_maillon_fin(liste* l,void* val);

liste liste_inserer_maillon_debut(liste l,void* val);

liste* liste_concatener(liste* a, liste* b);

int liste_contient_maillon(liste l, maillon ch);

liste* liste_supprimer_maillon(liste* l,void* val,void ( * detruire ) ( void * * pt ));

liste liste_supprimer(liste* l,void ( * detruire ) ( void * * pt ));

void afficher_liste_union(liste* l,char* fichier,void ( * afficher ) ( void * val , FILE * f ));


#endif


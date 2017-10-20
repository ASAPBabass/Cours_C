# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>

# undef NDEBUG

# include "arbre.h"

/*!
 * \file
 * \brief Implémentation des fonctions des trois structures arbre, arbre_parcours et noeud (cachée dans ce arbre.c)
 *
 * Attention : peu d'assert sur les fonctions static car elles ne peuvent être appelées que du module qui garantit la validité des données.
 * Certains existent néanmoins pour la mise au point du module.
 *
 *
 * \copyright PASD
 * \version 2017
 */




/*!
 * Représente un noeud de l'arbre (Pointeur/référence).
 */
typedef struct noeud_struct* noeud; 

/*!
 * Représente un noeud de l'arbre (structure).
 * Il indique son 
 * \li père (pour les parcours), 
 * \li son fils le plus à gauche
 * \li le frère à gauche suivant
 */
struct noeud_struct {
  void* val; 
  noeud pere; 
  noeud fils_gauche; 
  noeud frere_droit; 
}; 


/*!
 *  Pour creer un nœud sans valeur
 */
static noeud noeud_creer_vide()
{ 
  noeud n =malloc(sizeof(struct noeud_struct));
  assert(NULL != n);
  n -> val = NULL; 
  n -> pere = NULL; 
  n -> fils_gauche = NULL; 
  n -> frere_droit = NULL; 
  return n;
}


/*!
 * pour créer un nœud avec une valeur
 * \param val la valeur du noeud à créer
 * \param copier la fonction de copie pour le type de val
 * \return un noeud simple
 */
static noeud noeud_creer(void* val, void(* copier)(void* val, void** ptr))
{ 
  assert(NULL != val);
  assert(NULL != copier);
  noeud n =  noeud_creer_vide ();
  copier(val, &(n -> val)); 
  n -> pere = NULL; 
  n -> fils_gauche = NULL; 
  n -> frere_droit = NULL; 
  return n;
}


/*!
 * pour créer un nœud avec une valeur comme premier fils gauche d'un nœud
 * \param n le noeud référence pour l'ajout
 * \param val la valeur du noeud à créer et ajouter
 * \param copier la fonction de copie pour le type de val
 */
static void noeud_ajouter_fils_a_gauche(noeud n, void* val, void(* copier)(void* val, void** ptr))
{
  if(NULL==n->fils_gauche){
    n->fils_gauche=noeud_creer(val,copier);
    n->fils_gauche->pere = n;
  }else{
    noeud m = noeud_creer(val,copier);
    m->frere_droit = n->fils_gauche;
    m->pere = n;
    n->fils_gauche = m;
  }  
}


/*!
 * ajoute à l'extrème droite
 * \param n le noeud référence pour l'ajout
 * \param val la valeur du noeud à créer et ajouter
 * \param copier la fonction de copie pour le type de val
 */
static void noeud_ajouter_frere_a_droite(noeud n, void* val, void(* copier)(void* val, void** ptr))
{
  if(NULL==n->frere_droit){
    noeud m = noeud_creer(val,copier);
    m->pere = n->pere;
    n->frere_droit = m;
  } 
  else  noeud_ajouter_frere_a_droite(n->frere_droit,val,copier);

}


/*!
 * ajoute un fils à un nœud le plus à droite possible
 * \param n le noeud référence pour l'ajout
 * \param val la valeur du noeud à créer et ajouter
 * \param copier la fonction de copie pour le type de val
 */
static void noeud_ajouter_fils (noeud n, void* val, void(* copier)(void* val, void** ptr))
{
  if(NULL==n->fils_gauche){
    n->fils_gauche = noeud_creer(val,copier);
    n->fils_gauche->pere = n;
  } 
  else noeud_ajouter_frere_a_droite(n->fils_gauche,val,copier);


   /* noeud* pt = &(n->fils_gauche);
    while(NULL!=(*pt)->frere_droit){
      *pt -> (*pt)->frere_droit;
    }
    (*pt)->frere_droit = noeud_creer(val,copier);
  }*/
}




/*!
 * fait un affichage préfixe du sommet, de ses descendants et de ses frères (et de leur descendants)
 * \param n le noeud référence pour l'ajout
 * \param f le flux de sortie
 * \param afficher la fonction d'affichage pour le type de val
 */
static void noeud_afficher(noeud n, FILE * f, void(* afficher)(void* val, FILE * f), char const * const sep)
{
  afficher(n->val,f);
  
  if(NULL!=n->fils_gauche){
    fputs(sep,f);
    noeud_afficher(n->fils_gauche,f,afficher,sep);
  } 
  if(NULL!=n->frere_droit){
    fputs(sep,f); 
    noeud_afficher(n->frere_droit,f,afficher,sep);
  } 
}

/*!
 * fait un affichage préfixe du sommet, de ses descendants et de ses frères (et de leur descendants)
 * avec parenthèses et virgules pour montrer la structure arborescente
 * \param n le noeud référence pour l'ajout
 * \param f le flux de sortie
 * \param afficher la fonction d'affichage pour le type de val
 */
static void noeud_afficher_tuple(noeud n, FILE * f, void(* afficher )(void* val, FILE * f))
{
  afficher(n->val,f);
  if(NULL!=n->fils_gauche){
    fprintf(f," ( ");
    noeud_afficher_tuple(n->fils_gauche,f,afficher);
    fprintf(f," )");
  } 
  if(NULL!=n->frere_droit){
  fprintf(f," , ");
  noeud_afficher_tuple(n->frere_droit,f,afficher);
  }
}


/*!
 * Détruit un nœud et la valeur qu'il contient
 * \param n la location du noeud à détruire
 * \param detruire la fonction pour détruire adaptée au type de val
 */
static void noeud_detruire(noeud* n, void(detruire )(void** val))
{
  if(NULL!=n){
		if(NULL!=(*n)->fils_gauche) noeud_detruire(&((*n)->fils_gauche),detruire);
		if(NULL!=(*n)->frere_droit) noeud_detruire(&((*n)->frere_droit),detruire);
		detruire(&((*n)->val));
		free(*n);
		*n=NULL;
	}
}

/*!
 * Recherche préfixe d'un nœud égal (au sens de la fonction en argument) à une valeur
 * attention, on retourne l'endroit où ce nœud est référencé
 * \param n_pt la location du noeud à partir duquel se fait la recherche
 * \param val la valeur recherchée
 * \param est_egal la fonction adaptée au type des valeurs pour tester l'égalité 
 * \return la location du noeud recherché
 */
static noeud* noeud_chercher(noeud* n_pt, void* val, bool(*est_egal)(void* val1, void* val2)){
  if(est_egal((*n_pt)->val,val)) return n_pt;
  else if (NULL!=(*n_pt)->fils_gauche) noeud_chercher(&((*n_pt)->fils_gauche),val,est_egal);
  else if (NULL!=(*n_pt)->frere_droit) noeud_chercher(&((*n_pt)->frere_droit),val,est_egal);
  else return NULL;
}


/*! 
 * structure arbre
 * \param racine pointe sur la racine de l'arbre (le noeud qui n'a pas de père) 
 * \param copier pour copier/mettre en place une valeur
 * \param detruire pour détruire une valeur stockée dans l'arbre
 */
struct arbre_struct {
  noeud racine;   
  void(* copier )(void* val, void* * pt); 
  void(* detruire )(void* * pt);  
}; 

/* Partie codée et donnée aux étudiants */


arbre arbre_creer(void(* copier )(void* val, void** pt), void(* detruire )(void** pt))
{
  assert(NULL != copier);
  assert(NULL != detruire);
  arbre n = (arbre)malloc(sizeof(struct arbre_struct));
  assert(NULL != n);
  n -> racine = NULL; 
  n -> copier = copier; 
  n -> detruire = detruire; 
  return n;
}

void arbre_detruire(arbre * a)
{ 
  assert(NULL != a);
  noeud_detruire(&(( * a)-> racine),(* a)-> detruire);
  free(* a);
  *a = NULL;
}

void arbre_inserer_racine(arbre a, void* val)
{ 
  assert(NULL != a);
  assert(NULL != val);
  noeud n = noeud_creer(val, a -> copier);
  n -> fils_gauche = a -> racine;
  a -> racine = n;
  printf("fin insertion\n");
}


void arbre_afficher(arbre a, FILE * f, void(* afficher)(void* val,FILE * f), char const * const sep)
{
  assert(NULL != a);
  assert(NULL != f);
  assert(NULL != afficher);
  noeud_afficher(a -> racine, f, afficher, sep);
  fputc('\n', f);
}

void arbre_afficher_tuple(arbre a, FILE * f, void(* afficher )(void* val, FILE * f))
{
  assert(NULL != a);
  assert(NULL != f);
  assert(NULL != afficher);
  noeud_afficher_tuple(a -> racine, f, afficher);
  fputc('\n', f);
}



arbre arbre_extraction(arbre a, void* val, bool(* est_egal)(void* val1, void* val2))
{
  assert(NULL != a);
  assert(NULL != val);
  assert(NULL != est_egal);
  noeud* n=noeud_chercher(&(a->racine),val,est_egal);
  if(NULL!=*n){
  	noeud e=(*n);
	  *n=(*n)->frere_droit;
  	arbre b = arbre_creer(a->copier,a->detruire);
  	b->racine=e;
	  b->racine->pere=NULL;
	  b->racine->frere_droit=NULL;
  	return b;
  }
  else{
	return NULL;
  }
}


/*!
 * structure pour enregistrer un arbre à parcourir et le nœud où en est le parcours.
 * a l'arbre concerné
 * courant la position dans l'arbre pour le parcours (vaut NULL quand le parcours est fini)
 */
struct arbre_parcours_struct {
  arbre a;
  noeud courant; 
};



arbre_parcours arbre_creer_parcours(arbre a){
  
  arbre_parcours b = malloc(sizeof(struct arbre_parcours_struct));
  b->a = a;
  b->courant = a->racine;
return b;

}


void arbre_parcours_detruire(arbre_parcours p){
  free(p);
  p=NULL;
}


bool arbre_parcours_est_fini(arbre_parcours p){
  assert(NULL != p);
  return p->courant==NULL;
}


void arbre_parcours_suivant(arbre_parcours p){
  assert(NULL!=p);
  if(NULL!=p->courant->fils_gauche) p->courant= p->courant->fils_gauche;
  else if(NULL!=p->courant->frere_droit) p->courant = p->courant->frere_droit;
  else if(NULL!= p->courant->pere){
    p->courant = p->courant->pere->frere_droit;
  }
}


void* arbre_parcours_valeur(arbre_parcours p){
  assert(p!=NULL);
  return (p->courant)->val;
}


bool arbre_parcours_a_fils(arbre_parcours p){
  assert(! arbre_parcours_est_fini(p));
  return(NULL != p -> courant -> fils_gauche);
}


void arbre_parcours_aller_fils_gauche(arbre_parcours p){
  assert(arbre_parcours_a_fils(p));
  p -> courant =  p -> courant -> fils_gauche;
}


void arbre_parcours_aller_fils_droite(arbre_parcours p){
  assert(arbre_parcours_a_fils(p));
  p->courant = p->courant->fils_gauche;
  while(NULL != p->courant->frere_droit){
    p->courant = p->courant->frere_droit;
  }
}


bool arbre_parcours_a_frere_droit(arbre_parcours p){
  assert(! arbre_parcours_est_fini(p));
  return(NULL != p->courant -> frere_droit);
}


void arbre_parcours_aller_frere_droit(arbre_parcours p){
  assert(!arbre_parcours_est_fini(p));
  p->courant = p->courant;
  while(NULL != p->courant->frere_droit){
    p->courant = p->courant->frere_droit;
  }
}


bool arbre_parcours_a_pere(arbre_parcours p){
  assert(! arbre_parcours_est_fini(p));
  return(NULL != p -> courant -> pere);
}


void arbre_parcours_aller_pere(arbre_parcours p){
  assert(arbre_parcours_a_pere(p));
  p -> courant =  p -> courant -> pere;
}


void arbre_parcours_ajouter_frere_a_droite(arbre_parcours p, void* val){
  assert(!arbre_parcours_est_fini(p));
  assert(NULL != val);
  noeud_ajouter_frere_a_droite(p->courant, val, p->a->copier);
}



void arbre_parcours_ajouter_fils_a_gauche(arbre_parcours p, void* val){
  assert(! arbre_parcours_est_fini(p));
  noeud_ajouter_fils_a_gauche(p -> courant, val, p -> a -> copier);
}


void arbre_parcours_ajouter_fils_a_droite(arbre_parcours p, void* val){
  assert(! arbre_parcours_est_fini(p));
  noeud_ajouter_fils(p -> courant, val, p -> a -> copier);
}


void arbre_parcourir(arbre a,  void(* faire )(void* val1,va_list args),...){
  assert(NULL != a);
  assert(NULL != faire);
  arbre_parcours p = arbre_creer_parcours(a);
  while(! arbre_parcours_est_fini(p)) {
    va_list va;
    va_start(va,faire);
    (* faire)(arbre_parcours_valeur(p), va);
    va_end(va);
    arbre_parcours_suivant(p);
  }
  arbre_parcours_detruire(p);
}

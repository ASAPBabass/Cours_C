# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <assert.h>
# include <ctype.h>

# undef NDEBUG

# include "arbre.h"
# include "chaine.h"
# include "xml.h"


struct balise_struct {
  enum { ouvrante , fermante } type; 
  chaine nom; 
}; 




balise balise_creer(char const * st){
  balise b = malloc(sizeof(struct balise_struct));
  int i=1,j=0;
  
  if('/' ==  st[1]){
    b->type = fermante; 
  }else b->type = ouvrante; 
  char* c = malloc(sizeof(char)*strlen(st));
  for(;st[i]!='>';i++,j++){
    c[j]=st[i];
  }
  c[j+1]=0;
  b->nom = chaine_creer_char(c);
  return b;
  
}


void balise_detruire(balise* x){
  chaine_detruire(&((*x)->nom));
  free(*x);
  *x=NULL;
}

bool balise_est_ouvrante(balise x){ 
  assert(x != NULL ); 
  return(x -> type==ouvrante ); 
}

bool balise_est_fermante(balise x){ 
  assert(x != NULL ); 
  return(x -> type==fermante ); 
}

void balise_afficher (balise x, FILE* f) {
  chaine_afficher(f,x->nom);
}

/*! Les 4 fonctions ci-dessous sont usuels maintenant pour la manipulation d'un arbre de balises 
 * Elles sont "static" quand elles sont utiles à la création de l'arbre et "non static" sinon
 */
/*!
 * Pour copier une balise et utiliser la généricité des arbres
 * \param val la balise initiale
 * \param la location de la copie
 */
static void copier_balise(void* val, void** ptr){
  balise s=(balise) val;
  *ptr=s;
}

void afficher_balise(void* val, FILE* f){
  balise_afficher((balise) val,f);
}

/*!
 * Pour détruire une balise et utiliser la généricité des arbres
 * \param ptr la location de la balise à détruire
 */
static void detruire_balise(void** ptr){
  balise_detruire((balise*) ptr);
}

bool est_egal_balise(void* val1, void* val2){
  balise a = (balise) val1;
  balise b = (balise) val2;
  return chaine_est_egal(a->nom,b->nom);
}


/*!
 * Pour supprimer les espaces d'une chaine de caractères
 * \param st la chaine (au sens C) cible
 * \return une chaine (au sens C) sans espace
 */
static char* trim (char* st) {
  char* s = malloc(sizeof(char)*strlen(st));
  int j=0;
  for(unsigned int i=0;i<strlen(st);i++){
    if(st[i]!=' '){
      s[j]=st[i];
      j++;
    }
  }
  return s;
}


arbre xml_construction_arbre(char* source){
  
  FILE * f_in = fopen ( source , "r" );
  //creation de l'arbre
  arbre a = arbre_creer(copier_balise,detruire_balise);

  //on crée la racine de l'arbre
  char* s = malloc(sizeof(char)*20);
  fgets(s,20,f_in); 
  s = trim(s);
  balise b = balise_creer(s);
  arbre_inserer_racine(a,b);

  
  //on crée l'arbre de parcours
  arbre_parcours p = arbre_creer_parcours(a);
  
  while(!feof(f_in)){
    char* c = malloc(sizeof(char)*20);
    fgets(c,20,f_in);
    c = trim(c);
    printf("%s",c);
    balise b = balise_creer(c);
    if(b->type == ouvrante){
      arbre_parcours_ajouter_fils_a_droite(p,b);
      arbre_parcours_aller_fils_droite(p);
    }else{
      if(arbre_parcours_a_pere(p)) arbre_parcours_aller_pere(p);
      else break;
    } 
    free(c);
    c=NULL;
  }

  fclose(f_in);
  return a;
}


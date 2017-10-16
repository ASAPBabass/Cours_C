#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <assert.h>

#undef NDEBUG

#include "arbres.h"

/*!
 * \file
 * \brief Le programme de test associé à la structure arbres et pour des valeurs de type int
 *
 * \copyright PASD
 * \version 2017
 */


/*!
 * taille de la chaîne de caractères pour le sigle
 */
#define T_SIGLE 10
/*! taille de la chaîne de caractères pour la signification du sigle
 */
#define T_DETAILS 100 


typedef struct sigle_struct * sigle; 


/*!
 * \struct sigle_struct
 * court pour le sigle
 * details pour la description du sigle
 */

struct sigle_struct {
  char* court;   
  char* details; 
}; 


/*! 
 * Pour créer un signe à partir de deux chaînes de caractères
 * \param court le sigle 
 * \param details la description
 * \return un sigle selon la définition de la structure
 */
sigle sigle_creer(char* court, char* details) {
	sigle s=malloc(sizeof(struct sigle_struct));
	s->court=malloc(sizeof(char)*T_SIGLE);
	s->details=malloc(sizeof(char)*T_DETAILS);
	strcpy(s->court,court);
	strcpy(s->details,details);
	return s;
}


/*! 
 *  Destruction d'un sigle 
 * \param s sigle à détruire ((*s) mis à NULL à la fin)
 */
void sigle_detruire(sigle* s) {
	if((*s)!=NULL){
		if((*s)->court!=NULL){
			free((*s)->court);
		}
		if((*s)->details!=NULL){
			free((*s)->details);
		}
		free(*s);
		(*s)=NULL;
	}
}

/*! 
 *  Destruction d'un sigle 
 * \param s sigle dont on veut afficher les éléments sous la forme d'un couple des deux chaînes de caractères.
 * \param f le flux de sortie.
 */
void sigle_afficher(sigle  s, FILE* f) {
	fprintf(f,"(%s, %s)\n",s->court,s->details);
}

/*! 
 * Pour copier un sigle manipulé par un arbre binaire de recherche
 * attention à la signature (void car utilisable pour les arbres)
 * \param val la valeur à copier
 * \param pt le lieu de la copie.
 */
void copier_sigle(void* val, void** pt) {
	assert ( NULL != val ) ;
  	assert ( NULL != pt ) ;
	sigle s=(sigle)val;
	sigle n = sigle_creer(s->court,s->details);
	*pt = n;
}


/*! 
 * Pour afficher un sigle manipulé par un arbre binaire de recherche
 * attention à la signature (void car utilisable pour les arbres)
 * \param val la valeur à afficher
 * \param f le flux de sortie.
 */
void afficher_sigle(void *val, FILE* f){
	if(val!=NULL){
		sigle s=(sigle) val;
		sigle_afficher(s,f);
	}
	
}

/*! 
 * Pour détruire un sigle manipulé par un arbre binaire de recherche
 * attention à la signature (void car utilisable pour les arbres)
 * \param pt la location à détruire
 */
void detruire_sigle(void** pt){
	assert(NULL!=pt);
	if((*pt)!=NULL){
		sigle_detruire((sigle *)pt);	
	}
}


/*! 
 * Fonction de comparaison selon l'ordre lexicographique sur le champ court du sigle
 * attention à la signature (void car utilisable pour les arbres)
 * \param val1 première valeur
 * \param val2 deuxième valeur
 * \return >=1 si val1> val2, ==0 si val1=val2, <=-1 si val1>val2
 */
int comparer_sigle(void* val1, void* val2) {
	sigle s1=(sigle) val1;
	sigle s2=(sigle) val2;
	return strcmp((s1)->court,(s2)->court);
}



int main(void) {
  FILE* f_in = fopen("test_arbres_sigle_in.txt", "r"); 
  FILE* f_out = fopen("test_arbres_sigle_out.txt", "w"); 
  arbre abr = arbre_creer(copier_sigle , detruire_sigle , comparer_sigle); 
  char s[T_SIGLE]; 
  char d[T_DETAILS]; 
  
  fgets(s, T_SIGLE, f_in); 
 while(! feof(f_in)) {
    s[strlen(s)-1] = '\0'; 
    fgets(d, T_DETAILS, f_in); 
    d[strlen(d)-1] = '\0';
    sigle a1 = sigle_creer(s, d);
    arbre_insertion(abr, a1); 
    sigle_detruire(&a1); 
    fgets(s, T_SIGLE, f_in); 
  } 

  fprintf(f_out , "Arbre des sigles\n"); 
  arbre_afficher_infixe(abr , f_out , afficher_sigle);
  fprintf(f_out , "\n"); 
  
  fprintf(f_out , "recherche de "); 
  sigle ref = sigle_creer("OTAN" , ""); 
  afficher_sigle(ref , f_out); 
  sigle res = arbre_rechercher(abr , ref); 
  
  if(res != NULL) {
    fprintf(f_out , "le résultat est :"); 
    afficher_sigle(res , f_out); 
  }

  arbre_supprimer(abr , ref);
  fprintf(f_out , "Le résultat de la suppression\n"); 
  arbre_afficher_infixe(abr , f_out , afficher_sigle); 
  fprintf(f_out , "\n"); 
  int taille = arbre_taille(abr); 
  fprintf(f_out , "taille = %d \n" , taille); 
  
  sigle_detruire(&ref); 

  arbre_detruire(&abr);
 
  fclose(f_in); 
  fclose(f_out); 
 
  return 0; 
}

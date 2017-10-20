# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <assert.h>

# undef NDEBUG

/*!
 * \file
 * \brief Programme de test pour les entiers
 *
 * Pas de modifications à faire !
 * \copyright PASD
 * \version 2017
 */


# include "arbre.h"

# define LG 13

void copier_int (void* val, void** pt)
{
  *pt = (int*)malloc(sizeof(int)); 
  memcpy (*pt, val, sizeof(int)); 
}

void afficher_int(void* val, FILE* f)
{
  fprintf(f,"%d",*((int*)(val))); 
}

void detruire_int(void** pt) {
  if(*pt != NULL) {
    free(*pt); 
    (*pt) = NULL; 
  }
}

bool est_egal_int(void* val1, void* val2)
{
  int a = *(int*) val1; 
  int b = *(int*) val2; 
  return(a==b); 
}


void sommer(void* val, va_list vl)
{
  int* pt_i = va_arg(vl, int*);
  (*pt_i) += *((int*) val);
}


void afficher_int_separes(void* val, va_list vl) {
  FILE* f = va_arg(vl, FILE*);
  bool* test = va_arg(vl,bool*);
  if (!(*test)) {
    fprintf(f,"%d",*(int*)val);
    *test = true;
  }
  else
    fprintf(f," - %d",*(int*)val);
}


int main(void ) 
{

  int num[LG] = {29,15,27,21,25,8,1,10,2,3,13,16,9};
  
  FILE* f_out = fopen("test_arbre_int_out.txt" , "w"); 
 
  arbre a = arbre_creer(copier_int , detruire_int); 

  srand(1234); 
  
  int val = 24; 
  fprintf(f_out,"racine = %d \n", val); 
  arbre_inserer_racine(a, &val); 
  
  arbre_parcours parcours = arbre_creer_parcours(a); 

  int i = 0;
  val = num[i];
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_fils_a_gauche(parcours, &val); //29
  i++;
  val = num[i];
  
  arbre_parcours_aller_fils_gauche(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //15
  
  i++;
  val = num[i];
  arbre_parcours_aller_frere_droit(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_fils_a_gauche(parcours, &val); //27
  i++;
  val = num[i];

  arbre_parcours_aller_fils_gauche(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_fils_a_gauche(parcours, &val); //21
  i++;
  val = num[i];
  
  arbre_parcours_aller_fils_gauche(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //25
  i++;
  val = num[i];
  
  arbre_parcours_aller_frere_droit(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_fils_a_gauche(parcours, &val); //8
  i++;
  val = num[i];
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //1
  i++;
  val = num[i];

  arbre_parcours_aller_pere(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //10
  i++;
  val = num[i];
  
  arbre_parcours_aller_pere(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //2
  i++;
  val = num[i];
  
  arbre_parcours_aller_frere_droit(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val);//3
    i++;
  val = num[i];

  arbre_parcours_aller_frere_droit(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_fils_a_gauche(parcours, &val); //13
  i++;
  val = num[i];
  
  arbre_parcours_aller_fils_gauche(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //16
  i++;
  val = num[i];

  arbre_parcours_aller_pere(parcours);
  fprintf(f_out,"insérer = %d\n",val);
  arbre_parcours_ajouter_frere_a_droite(parcours, &val); //9
  
  
  
  arbre_parcours_detruire(parcours);

  arbre_afficher(a, f_out, afficher_int, " : "); 
  arbre_afficher_tuple(a, f_out, afficher_int); 
  val = 15;  
  arbre a_extrait = arbre_extraction(a, &val, est_egal_int); 
  
  fprintf(f_out, "arbre extrait : "); 
  arbre_afficher(a_extrait, f_out, afficher_int, " : "); 
  arbre_afficher_tuple(a_extrait, f_out, afficher_int); 
  
  fprintf(f_out, "arbre restant : "); 
  arbre_afficher(a, f_out, afficher_int, " : "); 
  arbre_afficher_tuple(a, f_out, afficher_int); 
  
  int s_ext = 0;
  arbre_parcourir(a_extrait, sommer, & s_ext);
  fprintf(f_out, "Somme arbre extrait : %d\n", s_ext);
  
  bool interne = false;
  arbre_parcourir(a_extrait, afficher_int_separes, f_out, & interne);
  fputc('\n', f_out);
  arbre_detruire(& a_extrait); 
 
  int s_res = 0;
  arbre_parcourir(a, sommer, & s_res);
  fprintf(f_out, "Somme arbre restant : %d\n", s_res);

  printf("dernier test\n");
  interne = false;
  arbre_parcourir(a, afficher_int_separes, f_out, & interne);
  fputc('\n',f_out);
  
  arbre_detruire(& a); 
  
  fclose(f_out); 

  return 0; 
}

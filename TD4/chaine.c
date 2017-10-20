#include "chaine.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/*!
 * \file chaine.c
 * \brief Les implémentations relatives à la manipulation des chaînes de caractères
 * \author PASD
 * \version 1.0
 * \date 2017
 *
 * La structure et toutes les fonctions de manipulation des chaines 
 *
 */


chaine chaine_creer_vide(){
	chaine ch=malloc(sizeof(struct chaine));
	ch->taille=0;
	ch->tab=NULL;
	return ch;
}

chaine chaine_creer_char(char* c){
	chaine ch=chaine_creer_vide();
	ch->tab=(char*)malloc(sizeof(char));
	ch->taille=strlen(c);
 	for(unsigned int i=0;i<=strlen(c)-1;i++){
		(ch->tab)[i]=c[i];
	}
	return ch;
}

void chaine_detruire(chaine* ch)
{
	free((*ch)->tab);
	free(*ch);
	(*ch) =NULL;
}

void chaine_afficher(FILE* f, chaine ch){
	fprintf(f,"%s\n",(ch->tab));
}

unsigned int chaine_extraire_taille(chaine ch)
{
	return ch->taille;
}


bool chaine_est_vide(chaine ch)
{
	return (ch->taille)==0;
}

bool chaine_est_egal(chaine ch1, chaine ch2){
	if(ch1->tab==NULL || ch2->tab==NULL) return false;
	if(ch1->taille!=ch2->taille) return false;
	if(ch1->tab==ch2->tab) return true;
	if(strcmp(ch1->tab,ch2->tab)==0) return true;
	return false;
	
}

void chaine_concatener(chaine ch1, chaine ch2){
	if(ch1->tab==NULL) ch1->tab=(char*)malloc(sizeof(char));
	if(ch2->tab==NULL) ch2->tab=(char*)malloc(sizeof(char));
	ch1->taille=ch1->taille + ch2->taille;
	ch1->tab=strcat(ch1->tab,ch2->tab);
	
}

char chaine_extraire_char_i(chaine ch, const unsigned int i){
	return (ch->tab)[i];
}

void chaine_modifier_char_i(chaine ch, const unsigned int i, const char c){
	(ch->tab)[i]=c;
}

chaine chaine_copier(chaine ch1){
	chaine ch=chaine_creer_vide();
	(ch->taille)=(ch1->taille);
	ch->tab=(char *)malloc(sizeof(char));
	strcpy(ch->tab,ch1->tab);
	return ch;
}

void chaine_en_minuscules(chaine ch){
	for(unsigned int i=0;i<ch->taille;i++){
		(ch->tab)[i]=tolower((ch->tab)[i]);
	}
}

void chaine_en_majuscules(chaine ch){
	for(unsigned int i=0;i<ch->taille;i++){
		(ch->tab)[i]=toupper((ch->tab)[i]);
	}
}

bool chaine_appartenir(const char c, chaine ch, int* i){
	for(unsigned int j=0;j<ch->taille;j++){
		if((ch->tab)[j]==c){
			*i=j;
			return true ;
		}

	}
	return false;
}

chaine chaine_lire(FILE* f, unsigned int taille){
	chaine ch=chaine_creer_vide();
	ch->taille=taille;
	do{
		(ch->tab)[taille]= fgetc(f); 
            	taille--;
        }while(taille>0);
	return ch;
}
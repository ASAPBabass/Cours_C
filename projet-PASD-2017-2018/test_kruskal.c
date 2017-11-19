# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
#include "kruskal.h"

arete* lire_fichier(char* fichier, int * nb_s, int * nb_a){
	FILE * f = fopen(fichier,"r");
        int nb_arete=0;
        int nb_sommet;int s1;int s2; int poids;
        int cpt_taille=0;
           
        fscanf(f,"%d",&nb_sommet);
    	arete* t_arete =(arete*) malloc (sizeof(struct arete)*(nb_sommet*nb_sommet));
        
        while(!feof(f)){
                fscanf(f,"%d %d %d",&s1,&s2,&poids);
                printf("Arete :%d %d %d\n",s1,s2,poids);
		t_arete[cpt_taille] = creer_arete(s1,s2,poids);
                nb_arete++;
                cpt_taille++;
        
        }
        *nb_s=nb_sommet;
        *nb_a=cpt_taille-1;
        fclose(f);
        return t_arete;
}


int main(int argc, char** argv) {
        int nb_s;int nb_arete;
        char* nom_fichier="/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/graphes/G_10_SOMMETS";
        char* nom_f="/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/test.txt";

        arete* t_arete=lire_fichier(nom_fichier, &nb_s, &nb_arete);
        liste ens = creer_liste_ensemble_int(10);
        afficher_liste_union(ens,nom_f,ens->afficher);

       // printf("%d %d %d",(t_arete[4])->s1,(t_arete[4])->s2,(t_arete[4])->poids);
        //printf("%d %d",nb_s,nb_arete);



        //liste arbre = algo_kruskal(t_arete,nb_arete,nb_s);
        //arete b = malloc(sizeof(struct arete));
        //arete a = creer_arete(1,2,3);
        //printf("%d",a->s1);
        return 0;

}


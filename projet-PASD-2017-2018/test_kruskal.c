# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "kruskal.h"

arete* lire_fichier(char* fichier, int * nb_s, int * nb_a){
	FILE * f = fopen(fichier,"r");
        int nb_arete=0;
        int nb_sommet;int s1;int s2; int poids;
        int cpt_taille=0;
           
        fscanf(f,"%d",&nb_sommet);
    	arete* t_arete =(arete*) malloc (sizeof(struct arete)*(nb_sommet*nb_sommet));
        
        while(!feof(f)){
                fscanf(f,"%d %d %d",&s1,&s2,&poids);
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

        int nb_s,nb_arete;
        FILE* f_out = fopen(argv[1] , "w+");
        //char* fichier = argv[1];
       // printf("\n%d\n%s \n%s\n %s\n",argc,argv[0], argv[1], argv[2]);
	arete* t_arete=lire_fichier(argv[2],&nb_s,&nb_arete);
	liste l =kruskal(t_arete,nb_s,nb_arete);
	liste_affichage(f_out,l);
	detruire_tab_arete(t_arete);
	liste_detruire(&l);
	fclose(f_out);
	
        return 0;

}

#include "segmentation.h"

int main(int argc, char** argv) {


        pgm img = lire_image_pgm("/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/images/cameraman.pgm");
        int largeur = largeur_image(img);
        int hauteur = hauteur_image(img);

        int nb_sommets = hauteur * largeur;
        int nb_aretes = 0;

        arete* t_arete = lire_matrice(image_matrice(img),largeur_image(img),hauteur_image(img),&nb_aretes);
        FILE* f_out = fopen("/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/test.txt", "w");
       // FILE* f_o = fopen(,w);


        liste ensembles = segmentation(image_matrice(img),t_arete,largeur,hauteur,nb_aretes,40);
        liste_affichage(f_out,ensembles);
        ecrire_image_pgm("/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/img.pgm",img,NULL);


     /*   printf("%d %d \n",largeur , hauteur);
       // ecrire_image_pgm("/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/test_image/image1.pgm",img,NULL);

        unsigned int** tab = image_matrice(img);

        FILE* f_out = fopen("/home/bastien/Documents/Cours_C/projet-PASD-2017-2018/test.txt", "w");
        arete* t_arete = lire_matrice(image_matrice(img),largeur_image(img),hauteur_image(img),&nb_aretes);
        //trier_arete(t_arete, 0 , nb_aretes-1);

        for(int i=0;i<nb_aretes;i++){
                afficher_arete(f_out,t_arete[i]);
                fprintf(f_out,"\n");
        }*/
        
                
        //liste l = kruskal(t_arete,nb_sommets,nb_aretes); //15 minutes

        //liste_affichage(f_out,l);

        //printf("%d",nb_aretes);
        
        
        
        
        
        
        return 0;

}


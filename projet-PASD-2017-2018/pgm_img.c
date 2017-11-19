#include "pgm_img.h"

/*!
 * Structure contenant les informations de base de l'image
 */
struct pgm_img {
    unsigned int largeur;
    unsigned int hauteur;
    unsigned int valeur_max;
    unsigned int** image;
};

/*!
 * Crée une image
 * \param _largeur la largeur de l'image
 * \param _hauteur la hauteur de l'image
 * \param _valeur_max la valeur max des pixels de l'image
 * \return l'image créée
 */
pgm initialiser_image_pgm(const unsigned int _largeur, const unsigned int _hauteur, const unsigned int _valeur_max) {
        
    pgm p = malloc(sizeof(struct pgm_img));
    
    p->largeur = _largeur;
    p->hauteur = _hauteur;
    p->valeur_max = _valeur_max;

    p->image = malloc(sizeof(unsigned int*) * _hauteur);
    if(p->image == NULL) {
        fprintf(stderr, "Allocation memoire impossible pour l'image-hauteur");
    }

    for(unsigned int i = 0; i < _hauteur; i++) {
        p->image[i] = malloc(sizeof(unsigned int) * _largeur);
        if(p->image[i] == NULL) {
            fprintf(stderr, "Allocation memoire impossible pour l'image-largeur %d", i);
        }
        for(unsigned int j = 0; j < _largeur; j++)
            p->image[i][j] = 0;
    }
        
    return p;

}

pgm creer_image_pgm(const unsigned int _largeur, const unsigned int _hauteur, const unsigned int valeur_max, unsigned int** image) {
    pgm p = initialiser_image_pgm(_largeur, _hauteur, valeur_max);
    p->image = image;
     
    return p;
}

/*! 
 * Fonction statique lisant l'entête d'une image
 * \param fichier l'image 
 * \param largeur la largeur de l'image (à stocker)
 * \param hauteur la hauteur de l'image (à stocker)
 * \param valeur_max l'intensité maximale d'un pixel (à stocker)
 * \return true si la lecture s'est bien déroulée, false sinon
 */
static bool lire_entete_image_pgm(const FILE* fichier, unsigned int* largeur, unsigned int* hauteur, unsigned int* valeur_max) {

    enum etats { INIT, MAGIC_NUMBER_FOUND, WIDTH_HEIGHT_FOUND, MAX_VAL_FOUND, ERROR };
    enum etats etat = INIT ; 
    const int MAX_LENGTH = 4096;

    char* buf = malloc(sizeof(char)*MAX_LENGTH);
    bool lireEntete = true;

    while(lireEntete) {

        fgets(buf, MAX_LENGTH, (FILE *) fichier);
        switch(etat) {

            case INIT:
            if(strncmp(buf,"P",1) == 0) etat = MAGIC_NUMBER_FOUND;
            break;
            case MAGIC_NUMBER_FOUND:
            while(strncmp(buf,"#",1) == 0) 
                fgets(buf, MAX_LENGTH, (FILE *) fichier);
            if(sscanf(buf,"%u %u", largeur, hauteur) == 2) etat = WIDTH_HEIGHT_FOUND; 
            else lireEntete = false;
            break;
            case WIDTH_HEIGHT_FOUND:
            if(sscanf(buf,"%u", valeur_max) == 1) {
                if(*valeur_max == 0) fprintf(stderr, "Entete PGM : une valeur max de 0 n'est pas autorisee.");
                else etat = MAX_VAL_FOUND;
            }
            lireEntete = false;
            break;
            default:
            etat = ERROR;
            lireEntete = false;
        }

    }

    free(buf);

    if(etat != MAX_VAL_FOUND) {
        fprintf(stdout, "Entete PGM incorrect, evaluation terminee a l'etat %d\n", etat);
        return false;
    }

    return true;

}

/*! 
 * Fonction statique lisant une image en binaire
 * \param fichier l'image 
 * \param valeur_max p l'image dans laquelle lire
 * \return true si la lecture s'est bien déroulée, false sinon
 */
static bool lire_donnees_image_pgm(const FILE* fichier, pgm p) {

    const int BYTES_TO_READ = p->valeur_max < 256 ? 1 : 2;

    for(unsigned int i = 0; i < p->hauteur; i++) {
        for(unsigned int j = 0; j < p->largeur; j++) {
            if(fread(&p->image[i][j], BYTES_TO_READ, 1, (FILE*)fichier) == 0)
                return false;
        }
    }

    return true;

}

/*!
 * Lit une image
 * \param fichier l'image à lire
 * \return l'image créée
 */
pgm lire_image_pgm(const char* fichier) {

    FILE* f = fopen(fichier, "rb");
        
    if(f == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier PGM en lecture");
        return NULL;
    }

    unsigned int largeur, hauteur, valeur_max;
        
    if(!lire_entete_image_pgm(f, &largeur, &hauteur, &valeur_max)) {
        fclose(f);
        return NULL;
    }
        
    pgm p = initialiser_image_pgm(largeur, hauteur, valeur_max);

    if(!lire_donnees_image_pgm(f, p)) {
        detruire_image_pgm(&p);
        fclose(f);
        return NULL;
    }

    fclose(f);
    return p;
 
}

/*!
 * Ecrit une image
 * \param fichier le fichier où écrire l'image
 * \param p l'image à écrire
 * \param un pointeur vers une fonction de filtre à appliquer (NULL si aucun filtre)
 * \return true si l'écriture s'est déroulée correctement, false sinon
 */
bool ecrire_image_pgm(const char* fichier, const pgm p, void(*filtre)(pgm p)) {

    FILE* img = fopen(fichier, "wb");
    if(img == NULL) {
        fprintf(stderr, "Ouverture de l'image en ecriture impossible.");
        return false;
    }

    // Ecriture du header
    fprintf(img, "P5\n");

    fprintf(img, "# Created by PASD 2017\n");
    
    fprintf(img, "%u %u\n", p->largeur, p->hauteur);
    
    fprintf(img, "%u\n", p->valeur_max);

    const int BYTES_TO_READ = p->valeur_max < 256 ? 1 : 2;

    if(filtre != NULL)
        filtre(p);

    for(unsigned int i = 0; i < p->hauteur; i++) {
        for(unsigned int j = 0; j < p->largeur; j++) {
            fwrite(&p->image[i][j], BYTES_TO_READ, 1, img);
        }
    }

    fclose(img);
    return true;

}

/*! 
 * Getteurs et accesseurs 
 */
unsigned int** image_matrice(pgm p) {
    return p->image;
}

unsigned int largeur_image(pgm p) {
    return p->largeur;
}

unsigned int hauteur_image(pgm p) {
    return p->hauteur;
}

/*!
 * Détruit une image
 * \param p un pointeur sur l'image à détruire
 */
void detruire_image_pgm(pgm* p) {
    
    for(unsigned int i = 0; i < (*p)->hauteur; i++) 
        free((*p)->image[i]);
                    
    free((*p)->image);
    free(*p);
    *p = NULL;

}


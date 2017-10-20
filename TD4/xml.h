# ifndef __XML_H
# define __XML_H
# define SIZE 50

/*!
 * \file
 * \brief Implémentation des balises 
 *
 * \copyright PASD
 * \version 2017
 */

/*!
 * Pointeur sur une balise_struct.
 */
typedef struct balise_struct * balise ; 


/*!
 * A partir d'une chaîne de caractères correspondant à une balise( <xxx> ou </xxx> ) 
 * on construit un balise avec ses deux champs nom et type.
 * \param s la chaine de caractères au sens du C qui contient une balise au format xml
 * \return une balise (à partir de l'implémentation chaine du TD1)
 */
balise balise_creer(char const * s);

/*!
 * Destruction d'une balise
 * \param x la location de la balise cible
 */
void balise_detruire(balise * x);

/*!
 * Pour tester le type de la balise
 * \param x la balise cible
 * \return vrai si c'est une balise ouvrante
 */
bool balise_est_ouvrante(balise x);

/*!
 * Pour tester le type de la balise
 * \param x la balise cible
 * \return vrai si c'est une balise fermante
 */
bool balise_est_fermante(balise x); 

/*!
 * Fonction pour un simple affichage (le nom)
 * \param x la balise à afficher
 * \param f le flux de sortie
 */
void balise_afficher (balise x, FILE * f);

/*! 
 * pour afficher une balise de manière compatible avec la généricité
 * \param val la balise
 * \param f le flux de sortie
 */
void afficher_balise (void* val, FILE* f);

/*! 
 * Fonction qui teste si deux balises (soit le nom) sont égales
 * fonction pour la généricité d'où les void*
 * \param val1 la première balise
 * \param val2 la deuxième balise
 * \return vrai si les noms des balises sont égaux.
 */
bool est_egal_balise(void* val1 , void* val2); 


/*!
 * Pour construire un arbre en lisant un fichier XML simple ne contenant qu'une série de balises 
 * on supposera ce fichier bien formé au sens XML. 
 * \param source le nom du fichier contenant le document XML bien formé
 * \return un arbre "XML"
 */

arbre xml_construction_arbre(char* source); 

# endif

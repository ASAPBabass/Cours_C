# ifndef __FACTORIZE_LU_HPP_
# define __FACTORIZE_LU_HPP_

/* !
 * \brief This module provides a function to compute the L U decomposition of any square matrix.. 
 * 
 * \author PASD
 * \date 2017
 */


# include "matrix.hpp"


/*!
 * This function computes the decomposition L U (lower upper) of a square matrix.
 * After the call, Matrix m will hold L in the upper part and U in the lower part.
 * \pre m Matrix to be replaced by its LU decomposition.
 * \pre Matrix \c m is square.
 */
void factorize_lu ( Matrix & m ) ; 


# endif

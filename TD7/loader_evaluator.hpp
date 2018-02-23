# ifndef __LOADER_EVALUATOR_HPP_
# define __LOADER_EVALUATOR_HPP_

/*!
 * \file 
 * This module provides a class to read (from a stream) an expression an store it for evaluation.
 *
 * \pre For all method, no pointer should NULL
 *
 * \author PASD
 * \date 2016
 */


# include <list>
# include <istream>

# include "exparith.hpp"

# undef NDEBUG
# include <assert.h>



/*! Sign making the end of the input of an expression. */
extern std :: string const sign_read_stop ;


/*!
 * This class is used to read an expression in postfix form on an input stream and then to evaluate it at will.
 */
class Loader_Evaluator {
  /*! Expression read on the \c postfixe_stream. 
    Ready for evaluation. */
  Expr * expression ;
public:
  /*! 
   * Constructor.
   * Elements of the expression should be separated by spaces.
   * The expression reading stops when a point (\c '.' ) is read.
   * \param postfixe_stream
   */
  Loader_Evaluator ( std :: istream & postfixe_stream ) ;
  /*!
   * Evaluate the held expression with a given context.
   * \param ec Context for the evaluation.
   * \return The computed value.
   */
  double evaluate ( Evaluation_Context & ec ) ; 
  /*!
   * Evaluate the held expression starting from an empty Evaluation_Context_Simple.
   * \param in \c istream to read the value from.
   * \return The computed value.
   */
  double evaluate ( std :: istream & in ) ;
  /*! Destructor. */
  ~ Loader_Evaluator () {
    delete expression ; 
  } ; 
} ; 


# endif
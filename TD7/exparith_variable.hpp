# ifndef __EXPARITH_VARIABLE_HPP_
# define __EXPARITH_VARIABLE_HPP_

/*!
 * \file 
 * This module provides the classes to represent and use variables in arithmetical expressions.
 *
 * \pre For all method, no pointer should NULL
 *
 * \author PASD
 * \date 2016
 */

# include "exparith.hpp"


# undef NDEBUG
# include <assert.h>

/*! Symbol for operator \c := . */
extern std :: string const sign_set ; 


/*!
 * This class is used to encode variables.
 * Their values is provided by the \c Evaluation_Context
 * \pre The variable id should not be "".
 */
class Variable : public Expr {
  /* Variable name. */
  std :: string const id ;
public :
  // CONSTRUCTORS
  Variable ( std :: string const & _id
	     ) 
    : Expr ( priority_var_con ) 
    , id ( _id )
  {
    assert ( "" != _id ) ;
  } ; 
  /*! Destructor. */
  ~ Variable () {} ;
  std :: string const & get_id () { return id ; }
  double eval ( Evaluation_Context & ec ) const ;
  std :: string  toString () const ; 
} ; 


/*!
 * This is the affectation operation.
 * Left operand (or first in postfix form) should be a variable.
 * The value of the expression is the one of affected to the value.
 */
class Set : public Expr {
  /*! Variable to valuate. */
  Variable * variable ; 
  /*! Expression to compute its value. */
  Expr * value ;
public:
  // CONSTRUCTOR 
  Set ( Variable * variable , 
	Expr * value ) 
    : Expr ( priority_set ) 
    , variable ( variable ) 
    , value ( value ) 
  {
    assert ( NULL != variable ) ;
    assert ( NULL != value ) ;
  } ; 
  /*! Destructor. */
  ~ Set () {
    delete variable ; 
    delete value ; 
  } ; 
  std :: string  toString () const ; 
  double eval ( Evaluation_Context & ec ) const ;
} ; 




# endif

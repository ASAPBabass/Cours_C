# ifndef __EXPARITH_UNARY_HPP_
# define __EXPARITH_UNARY_HPP_

/*!
 * \file 
 * This module provides the classes to represent unary arithmetical expressions.
 *
 * \pre For all method, no pointer should NULL
 *
 * \author PASD
 * \date 2016
 */

# include "exparith.hpp"


# undef NDEBUG
# include <assert.h>

/*! Symbol for operator \c exp . */
extern std :: string const sign_exp ; 
/*! Symbol for operator \c log . */
extern std :: string const sign_log ;


/*! classe de opérateur unaire, Log et Exp */
class Op_Unary : public Expr {
  /*! Exp ou Log */
  std :: string sign ;
  /*! Valeur à laquelle on applique l'opérateur */
  Expr * argument ;
public:
  // CONSTRUCTOR
  Op_Unary ( priority_enum priority ,
	     std :: string sign ,
	     Expr * exp ) 
    : Expr ( priority ) 
    , sign ( sign ) 
    , argument ( exp ) 
  {
    assert ( NULL != exp ) ;
  } ; 
  /*! Destructor. */
  ~ Op_Unary () {
    delete argument ; 
  } ;
  std :: string  toString () const ; 
  double eval ( Evaluation_Context & ec ) const ;
protected :
  /*! ??? */
  virtual double compute ( double x ) const = 0 ;
} ; 



//
// Very powerfull, but ugly
// wait till templates
// in C++11 lambda / functional approach even better
//
/*! This is used to defined simpli similar things: classes for binary operators. */
# define CLASS_OP_UNARY( name , priority , sign )	\
  class name : public Op_Unary {			\
  public:						\
  name ( Expr * Exp )					\
    : Op_Unary ( priority ,				\
		 sign ,					\
		 Exp ) {} ;				\
  ~ name () {} ;					\
  protected :						\
  double compute ( double x ) const ;			\
  } ; 

CLASS_OP_UNARY ( Exp , priority_exp_log , sign_exp )
CLASS_OP_UNARY ( Log , priority_exp_log , sign_log )



# endif

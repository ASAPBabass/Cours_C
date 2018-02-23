# ifndef __EXPARITH_HPP_
# define __EXPARITH_HPP_

/*!
 * \file 
 * This module provides the classes to represent the different parts of arithmetical expressions.
 *
 * \pre For all method, no pointer should NULL
 *
 * \author PASD
 * \date 2016
 */

# include "evaluation_context.hpp"


# include <string>

# undef NDEBUG
# include <assert.h>



/*!
 * enum to provide the different levels of priority between operators.
 */
typedef enum {
  /*! Priority of set operator. */
  priority_set = 0 , 
  /*! Priority of binary plus and minus. */
  priority_add_sub = 10 , 
  /*! Priority of multiplication and division. */
  priority_mul_div = 20 , 
  /*! Priority log and exp */
  priority_exp_log = 30 , 
  /*! Priority of variables and constants. */
  priority_var_con = 40 
} priority_enum ; 





/*!
 * This is ground class for the all arithmetical (sub-)expression.
 * This class should not be instantiated and is virtual.
 * It only manage the priority.
 */
class Expr {
  /*! Priority level of the expression. */
  priority_enum const priority ; 
public:
  // CONSTRUCTOR
  /*! 
   * Plain constructor.
   * \param p level of priority.
   */
  Expr ( priority_enum p ) 
    : priority ( p ) 
  {} ; 
  /*!
   * Evaluate the expression.
   * \return The double value of the expression. 
   */
  virtual double eval ( Evaluation_Context & ec ) const = 0 ;
  /*!
   * Output the expression to \c cout .
   */
  virtual std :: string toString () const = 0 ;
  /*!
   * Return the priority level of the expression.
   */
  priority_enum get_priority () const {
    return priority ; 
  } ;
  /*! Destructor. */
  virtual ~ Expr () {} ; 
} ; 


/*!
 * This class is used to encode constants.
 */
class Constant : public Expr {
  /*! Value of the constant. */
  double const value ; 
public:
  // CONSTRUCTOR
  /*! 
   * Plain constructor.
   * \param v value of the constant.
   */
  Constant ( double v ) 
    : Expr ( priority_var_con ) 
    , value ( v ) 
  {} ; 
  /*! Destructor. */
  ~ Constant () {} ; 
  std :: string  toString () const ; 
  double eval ( Evaluation_Context & ec ) const ; 
} ; 



# endif




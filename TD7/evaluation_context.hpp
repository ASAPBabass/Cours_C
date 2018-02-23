# ifndef __EVALUATION_CONTEXT_HPP_
# define __EVALUATION_CONTEXT_HPP_

/*!
 * \file 
 * This file provides the classes to manage the context of evaluation, in particular the value of variables.
 *
 * \author PASD
 * \date 2016
 */

# include <string>
# include <map>

# include <math.h>

# undef NDEBUG
# include <assert.h>


/*! 
 * Abstract class used to provide a context for evaluation.
 * In particular, it manages the value of variables.
 */
class Evaluation_Context {
public :
  
  /*! 
   * Retrieve the value of a variable.
   * \param id Variable name.
   * \return the value associated to \c id or NAN if undefined.
   */
  
  virtual double get_value ( std :: string const & id ) = 0 ;

  /*!
   * Set the value of a variable.
   * \param id Variable name.
   * \param value Value to associate to the variable.
   */
  virtual void valuate ( std :: string const & id ,
			 double value ) = 0 ;

  /*! Destructor. */
  virtual ~ Evaluation_Context () {} ;
} ;



/*!
 * Concrete instance used when no variable should be used. 
 */
class Evaluation_Context_No_Variable
  : public Evaluation_Context {
public :
  /*! It is asserted that this method is not used. */
  double get_value ( std :: string const & id ) ;
  /*! It is asserted that this method is not used. */
  void valuate ( std :: string const & id ,
		 double value ) ;
} ;



/*!
 * Concrete instance used when variable are available.
 * Their values are recorded in a map.
 */
class Evaluation_Context_Simple 
  : public Evaluation_Context {
protected :
  std :: map < std :: string const , double > valuation ;
public :
  double get_value ( std :: string const & id ) ;
  void valuate ( std :: string const & id ,
		 double value ) ;
} ;


# endif

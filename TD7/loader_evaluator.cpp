# include <stack>
# include <stdlib.h>

# include <iostream>
#include <iostream>
#include <string>
#include <sstream>
# include "loader_evaluator.hpp"
# include "exparith_unary.hpp"
# include "exparith_unary.hpp"
# include "exparith_binary.hpp"
# include "exparith_variable.hpp"

# include <assert.h>

# define NDEBUG 1

using namespace std ; 


string const sign_read_stop = "." ;

// help write a lot of simular cases
# define CASE_UNARY( sign , exp )		\
  else if ( sign == string_read ) {		\
    assert ( 1 <= l . size () ) ;		\
    Expr * f = l.top () ; 			\
    l.pop () ;					\
    l.push ( new exp ( f ) ) ;			\
  }


// help write a lot of simular cases
# define CASE_BINARY( sign , exp )		\
  else if (sign==string_read) {			\
    assert( 2<= l.size() ) ;			\
    Expr * f1 = l.top () ;			\
    l.pop () ;					\
    Expr * f2 = l.top () ;			\
    l.pop () ;					\
    l.push ( new exp ( f2 , f1) ) ;		\
  }
    
Loader_Evaluator :: Loader_Evaluator ( istream & postfixe_stream ) {
	assert(NULL!=postfixe_stream);
	string string_read;
	postfixe_stream >> string_read;
	std::stack<Expr*> l;
	while(true){
		if(string_read==sign_read_stop)  break;

		CASE_BINARY("*",Mul)
		
		CASE_BINARY("/",Div)

		CASE_BINARY("+",Add)

		CASE_BINARY("-",Sub)

		CASE_UNARY("exp",Exp)

		CASE_UNARY("log",Log)

		else if(":="==string_read){
			assert( 2<= l.size() ) ;
   			Expr * f1 = l.top () ;	
    			l.pop () ;		
    			Expr * f2 = l.top () ;
    			l.pop () ;		
			l.push(new Set((Variable*) f2,f1));
		}
		/*else if(isalpha(string_read[0]))
				l.push(new Variable(string_read));*/
		else {
				/*double d = atof(string_read.c_str());
				l.push(new Constant(d));*/
			double d;
			std::istringstream iss(string_read);
			if(iss >>d){
				l.push(new Constant(d));
			}
			else  l.push(new Variable(string_read));
		}
		postfixe_stream >> string_read;
	}
	expression=l.top();
	l.pop();
	assert(0==l.size());	
}



/*!
 * This is a simple context evaluation (variables are managed correctly) with the special characteristic that if a value is not valuated, it reads the value of the variable on an input stream.
 */
class Evaluation_Context_IStream
  : public Evaluation_Context_Simple {
  istream & in ;
public :
  Evaluation_Context_IStream ( istream & in )
    : in ( in ) {}
  /*! Read from the map otherwise from the input stream \c in.
   */
  double get_value ( string const & id ) { 
  std::map<string,double>::iterator it=valuation.find(id);
  if(it == valuation.end()){
	double d;
	in>>d;
	valuate(id,d);
	return d ;
  }
  else return it->second;
  }
  
} ;


double Loader_Evaluator :: evaluate ( istream & in ) {
  Evaluation_Context_IStream ec ( in ) ;
  return evaluate ( ec ) ;
}


double Loader_Evaluator :: evaluate ( Evaluation_Context & ec ) { 
  return expression->eval(ec);
}
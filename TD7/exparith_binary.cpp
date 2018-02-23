# include "exparith_binary.hpp"


# include <assert.h>
# define NDEBUG 1


using namespace std ; 


std :: string const sign_add = "+" ; 
std :: string const sign_sub = "-" ; 
std :: string const sign_mul = "*" ; 
std :: string const sign_div = "/" ; 



double Op_Binary :: eval ( Evaluation_Context & ec ) const { 
  if("+"==sign){
    return left->eval(ec)+right->eval(ec);
  }
  else if("-"==sign){
    return left->eval(ec)-right->eval(ec);
  }
  else if("*"==sign){
    return left->eval(ec)*right->eval(ec);
  }else{
    return left->eval(ec)/right->eval(ec);
  }
}


string Op_Binary :: toString () const { 
  string s1=left->toString();
  string s2 = right->toString();
  if(left->get_priority()<20) s1="( " + s1 + " )";
  if(right->get_priority()<20) s2="( " + s2 + " )";
  return s1+" "+sign+" "+s2;
}


# define COMPUTE_BINARY( class , op )				\
    double class :: compute ( double left ,			\
    double right ) const {					\
    return NAN ;						\
  }

COMPUTE_BINARY ( Add , + )
COMPUTE_BINARY ( Sub , - )
COMPUTE_BINARY ( Mul , * )
COMPUTE_BINARY ( Div , / )



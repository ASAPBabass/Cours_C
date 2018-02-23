# include "exparith_variable.hpp"


# include <assert.h>
# define NDEBUG 1


using namespace std ; 


std :: string const sign_set = ":=" ; 


double Variable :: eval ( Evaluation_Context & ec ) const{ 
  return ec.get_value(id);
}


string Variable :: toString () const { 
  return id;
} 


double Set :: eval ( Evaluation_Context & ec ) const { 
  ec.valuate(variable->get_id(),(double) value->eval(ec));
  return value->eval(ec);
}

string Set :: toString () const { 
  string s="";
  return s+variable->toString()+ " := "+value->toString();
}


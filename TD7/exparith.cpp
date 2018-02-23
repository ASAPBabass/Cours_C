# include <sstream>

# include "exparith.hpp"


# include <assert.h>
# define NDEBUG 1


using namespace std ; 



double Constant :: eval ( Evaluation_Context & ec ) const{ 
  return value;
}


string Constant :: toString () const { 
  string s="";
  ostringstream strs;
  strs << value;
  s = strs.str();
  return s;
}


# include "evaluation_context.hpp"


using namespace std ;


double Evaluation_Context_No_Variable :: get_value ( string const & id ) {
  assert ( false ) ;
  return NAN ;
}


void Evaluation_Context_No_Variable :: valuate ( string const & id ,double value ) {

}

double  Evaluation_Context_Simple :: get_value ( string const & id ) { 
  std::map<std::string,double>::  iterator it = valuation.find(id);
  if(id != it->first) return NAN;
  else return it->second;
}


void  Evaluation_Context_Simple :: valuate ( string const & id ,double value ) { 
  valuation.erase(id);
  valuation.insert(std::pair<std::string,double> (id,value));
}

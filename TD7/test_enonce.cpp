# include <string>
# include <iostream>
# include <sstream>

# include "exparith.hpp"
# include "exparith_unary.hpp"
# include "exparith_binary.hpp"
# include "exparith_variable.hpp"
# include "exparith_variable.hpp"


using namespace std ; 


int main () {
  Expr * add = new Add ( new Variable ( "x" ) , new Constant ( 3 ) ) ;
  Expr * set = new Set ( new Variable ( "y" ) , add ) ;
  Expr * exp =  new Add ( set , new Variable ( "y" ) ) ;
  Evaluation_Context_Simple ec  ;
  ec . valuate ( "x" , 7 ) ;
  cout << exp -> toString () << "  ==>  " << exp -> eval ( ec ) << endl ;
  ec . valuate ( "x" , 11 ) ;
  cout << exp -> toString () << "  ==>  " << exp -> eval ( ec ) << endl ;
  delete ( exp ) ;
  return 0 ; 
}
 

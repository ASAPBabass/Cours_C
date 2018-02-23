# include <string>
# include <fstream> 
# include <iostream> 
# include <sstream> 
# include <list>

# include "exparith.hpp"
# include "loader_evaluator.hpp"


using namespace std ; 

namespace {

  void test_file ( char const * const file_name ) {
    std::list<string> formula ; 
    std::ifstream file ( file_name ) ; 
    Loader_Evaluator el ( file ) ;
    file . close () ;
    stringstream in ( " 90 -3.5  77 0 ") ;
    cout << el . evaluate ( in ) << endl ;
  }

}


int main () {

  test_file ( "data_expression_1.txt" ) ;
  test_file ( "data_expression_2.txt" ) ;
  test_file ( "data_expression_3.txt" ) ;
  test_file ( "data_expression_4.txt" ) ;
  test_file ( "data_expression_5.txt" ) ;
  test_file ( "data_expression_6.txt" ) ;

  return 0 ; 
}
 
 

# include <string>
# include <iostream>
# include <sstream>

# include "exparith.hpp"
# include "exparith_unary.hpp"
# include "exparith_binary.hpp"
# include "exparith_variable.hpp"
# include "exparith_variable.hpp"


using namespace std ; 


namespace {


  void test_expr_eval ( Expr * e ,
			Evaluation_Context & ec ) {
    cout << e -> toString () ; 
    cout << " \t~~~>  " ;
    cout << e -> eval ( ec ) ; 
    cout << endl ;
  }

  
  void test_expr ( Expr * e ) {
    Evaluation_Context_No_Variable ec ;
    test_expr_eval ( e , ec ) ;
    delete e ;
  }

  
  void test_expr_x_y ( Expr * e ) {
    Evaluation_Context_Simple ec ;
    ec . valuate ( "x" , 0 ) ;
    ec . valuate ( "y" , 0 ) ;
    test_expr_eval ( e , ec ) ;
    ec . valuate ( "x" , 100 ) ;
    ec . valuate ( "y" , 0 ) ;
    test_expr_eval ( e , ec ) ;
    ec . valuate ( "x" , 0 ) ;
    ec . valuate ( "y" , 100 ) ;
    test_expr_eval ( e , ec ) ;
    ec . valuate ( "x" , 100 ) ;
    ec . valuate ( "y" , 100 ) ;
    test_expr_eval ( e , ec ) ;
    delete e ;
  }

  
  void test_expr_var ( Expr * e ) {
    Evaluation_Context_Simple ec ;
    test_expr_eval ( e , ec ) ;
    delete e ;
  }
  


  void test_without_variables () {
    test_expr ( new Constant ( 4.2 ) ) ; 
    test_expr ( new Add ( new Constant ( 4.2 ) , new Constant ( 2.4 ) ) ) ; 
    test_expr ( new Div ( new Constant ( 4.2 ) , new Constant ( 2.4 ) ) ) ; 
    test_expr ( new Mul ( new Constant ( 4.2 ) , new Constant ( 2.4 ) ) ) ; 
    test_expr ( new Sub ( new Constant ( 4.2 ) , new Constant ( 2.4 ) ) ) ; 
    test_expr ( new Exp ( new Constant ( 2.4 ) ) ) ; 
    test_expr ( new Log ( new Constant ( 2.4 ) ) ) ; 
    test_expr ( new Exp ( 
			 new Sub ( 
				  new Mul ( 
					   new Add ( 
						    new Constant ( 5.6 ) , 
						    new Constant ( 7.6 ) 
						     ) , 
					   new Div ( 
						    new Constant ( 7 ) , 
						    new Constant ( 4.2 ) 
						     ) 
					    ) , 
				  new Constant ( 5.6 ) 
				   ) 
				) ) ;
				
  }



  void test_with_variables () {
    test_expr_x_y ( new Variable ( "x" ) ) ; 
    test_expr_x_y ( new Sub ( new Constant ( 1 ) ,
			      new Variable ( "y" )
			      )
		    ) ;
    test_expr_x_y (  new Mul ( 
			      new Add ( 
				       new Variable ( "x" ) , 
				       new Variable ( "y" )
					) , 
			      new Constant ( 7 ) 
			       )
		     ) ;
    test_expr_x_y (  new Div ( 
			      new Add ( 
				       new Variable ( "x" ) , 
				       new Variable ( "y" )
					) , 
			      new Constant ( 7 ) 
			       )
		     ) ;
    test_expr_x_y (  new Div (
			      new Constant ( 7 ) ,
			      new Add ( 
				       new Variable ( "x" ) , 
				       new Constant ( 1 )
					) 
			      )
		     ) ;
    test_expr_x_y ( new Log ( 
			     new Mul ( 
				      new Add ( 
					       new Variable ( "x" ) , 
					       new Variable ( "y" )
						) , 
				      new Div ( 
					       new Constant ( 7 ) , 
					       new Add ( new Constant ( 1 ) ,
							 new Variable ( "x" )
							 )
						) 
				       )  
			      )
		    ) ;
    test_expr_x_y ( new Log ( 
			     new Sub ( 
				      new Mul ( 
					       new Add ( 
							new Variable ( "x" ) , 
							new Variable ( "y" )
							 ) , 
					       new Div ( 
							new Constant ( 7 ) , 
							new Add ( new Constant ( 1 ) ,
								  new Variable ( "x" )
								  )
							 ) 
						) , 
				      new Constant ( 5.6 ) 
				       ) 
			      ) ) ; 
    test_expr_var ( new Variable ( "var" ) ) ; 
    test_expr_var ( new Set (
			     new Variable ( "var" ) ,
			     new Constant ( 7 )
			     ) ) ; 
    test_expr_var ( new Set (
			     new Variable ( "var" ) ,
			     new Set (
				      new Variable ( "v" ) ,
				      new Constant ( 7 )
				      )
			     )
		    ); 
    test_expr_var ( new Mul (
			     new Mul ( new Set (
						new Variable ( "v1" ) ,
						new Set (
							 new Variable ( "v2" ) ,
							 new Constant ( 7 )
							 )
						) ,
				       new Variable ( "v1" ) 
				       ),
			     new Variable ( "v2" ) 
			     )
		    ); 
    test_expr_var ( new Add (
			     new Set (
				      new Variable ( "var" ) ,
				      new Constant ( 7 ) ) ,
			     new Constant ( 5.6 ) 			     
			     ) ) ; 
    test_expr_var ( new Add (
			     new Set (
				      new Variable ( "va" ) ,
				      new Constant ( 7 ) ) ,
			     new Variable ( "va" ) 			     
			     ) ) ; 
    test_expr_var ( new Mul (
			     new Add (
				      new Set (
					       new Variable ( "va" ) ,
					       new Constant ( 7 ) ) ,
				      new Variable ( "va" ) 			     
				      ) ,
			     new Add (
				      new Set (
					       new Variable ( "va" ) ,
					       new Constant ( 100 ) ) ,
				      new Variable ( "va" ) 			     
				      )
			     ) ) ; 
  }

}


int main () {

  test_without_variables () ;

  test_with_variables () ;

  return 0 ; 
}
 

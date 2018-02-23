/*! \file
 * \brief This file is meant to test vector implantation.
 * 
 * \author PASD
 * \date 2016
 */

# include "vector.hpp"


# undef NDEBUG
# include <assert.h>

using namespace std ; 


namespace {
  const int size = 10 ;
  const int scalaire = 2.3 ;
}


int main ( int argc ,
	   const char * argv[] ) {
  Vector v1 ( size ) ; 
  for ( unsigned int i=0 ; i < size ; i++ ) {
    v1 [ i ] = i ;
  }
  cout << v1 ; 
 
  Vector v2 ( size ) ; 
  v2.init_alea () ; 
  cout << v2 ; 
 
  Vector v3 = v1 + v2 ; 
  cout << v3 ; 
 
  Vector v4 = scalaire * v1 ; 
  cout << v4 ; 

  cout << "v1 == v1 |- " << ( v1 == v1 ) << endl ;
  cout << "v1 == v2 |- " << ( v1 == v2 ) << endl ;
  cout << "v4 == v1 * " << scalaire << " |- " << ( v4 == v1 * scalaire ) << endl ;

  cout << ( v4 | v4 ) << endl; 

  return 0 ; 
}

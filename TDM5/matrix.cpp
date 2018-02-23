# include <iostream>
# include <stdlib.h>  // drand48

# include "matrix.hpp"

# undef NDEBUG
# include <assert.h>

using namespace std ; 


/*! To simplify all traversal of a matrix.
 */
# define FOR_L_C( mat , code )						\
  for ( unsigned int l = 0 ; l < ( mat ) . line_nbr ; l ++ ) {		\
    for ( unsigned int c = 0 ; c < ( mat ) . column_nbr; c ++ ) {	\
      code ;								\
    }									\
  }						


Matrix :: Matrix ( unsigned int const _line_nbr ,
		   unsigned int const _column_nbr ) 
  : line_nbr ( _line_nbr ) 
  , column_nbr ( _column_nbr )
  , element ( new float [ _line_nbr * _column_nbr ] ) { 
} 


Matrix :: Matrix ( Matrix const & m ) 
  : line_nbr ( m . line_nbr ) 
  , column_nbr ( m . column_nbr ) 
  , element ( new float [ m . column_nbr * m . line_nbr ] ) { 
} 


Matrix :: ~ Matrix () {
  delete [] element ; // works with NULL
}


void Matrix :: init_alea () { 
  for ( unsigned int i = 0 ; i < column_nbr*line_nbr ; i++ ) {	
    element[ i ] = drand48 () ; 
  }				
}


void Matrix :: init ( float const * coefficients ) { 
  for ( unsigned int i = 0 ; i < column_nbr*line_nbr ; i++ ) {	
    element[ i ] = coefficients[i]; 
  }				
}


void Matrix :: set_identity () { 
  assert(column_nbr == line_nbr);
  unsigned int id =0;
  for ( unsigned int i = 0 ; i < column_nbr*line_nbr; i++ ) {	
    if(id == i){
      element[i] = 1;
      id += line_nbr+1;
    } 
    else{
      element[ i ] = 0;
    }
  }				
}


std :: ostream & operator << ( std :: ostream & ost , Matrix const & m ) { 
              
  for(unsigned int l=0;l<m.line_nbr;l++){
    for(unsigned int c=0;c<m.column_nbr;c++){
      ost << m(l,c) << "	";
    }
    ost << endl;
  }
  return ost;
}


Matrix & Matrix :: operator = ( Matrix const & m ) { 
  assert(line_nbr==m.line_nbr && column_nbr == m.column_nbr);
  for(unsigned int i=0; i<line_nbr*column_nbr; i++){
    element[i]=m.element[i];
  }
  return (*this);
}


Matrix Matrix :: operator + ( Matrix const & m ) const { 
  assert((line_nbr*column_nbr) == (m.line_nbr*m.column_nbr));
  float* tab = new float [line_nbr*column_nbr];
  for(unsigned int i=0; i<line_nbr*column_nbr;i++){
    tab[i]=element[i]+m.element[i];
  }
  Matrix res (line_nbr,column_nbr);
  res.init(tab);
  return res; 

}


Matrix Matrix :: operator - ( Matrix const & m ) const { 
  assert((line_nbr*column_nbr) == (m.line_nbr*m.column_nbr));
  float* tab = new float [line_nbr*column_nbr];
  for(unsigned int i=0; i<line_nbr*column_nbr;i++){
    tab[i]=element[i]-m.element[i];
  }
  Matrix res (line_nbr,column_nbr);
  res.init(tab);
  return res; 
}


Matrix Matrix :: operator * ( Matrix const & m ) const { 
  Matrix n (line_nbr,m.column_nbr);
  for(unsigned int l=0,i=0;l<line_nbr;l++){ 
    for(unsigned int c2=0;c2<m.column_nbr;c2++,i++){
      n.element[i] = (extract_ligne(l,0,column_nbr) | m.extract_col(0,line_nbr,c2));
      
    }
  }
  return n;
}


Vector Matrix :: operator * ( Vector const & v ) const { 
  assert(column_nbr==v.get_size());
  Vector w (line_nbr);
  for ( unsigned int i=0 ; i < line_nbr ; i++ ) {
   // cout << extract_ligne(i,0,column_nbr);
    w[i] = (extract_ligne(i,0,column_nbr)) | v; //somme du produit entre les deux vecteurs
  }

  return w;
}


Matrix Matrix :: operator * ( const float a ) const { 
  Matrix n (line_nbr,column_nbr);
  for(unsigned int i=0;i<line_nbr*column_nbr;i++){ 
    n.element[i] = element[i]*a;
  }
  return n;
}


Matrix operator * ( float const a ,
		    Matrix const & m ) {
  return m * a ; 
}


Matrix & Matrix :: operator += ( Matrix const & m ) { 
  assert((line_nbr*column_nbr) == (m.line_nbr*m.column_nbr));
  for(unsigned int i=0; i<line_nbr*column_nbr;i++){
    element[i]+=m.element[i];
  }
  return (*this);
}


Matrix & Matrix :: operator *= ( Matrix const & m ) { 
  assert(line_nbr == m.column_nbr);
  for(unsigned int l=0,i=0;l<line_nbr;l++){ 
    for(unsigned int c2=0;c2<m.column_nbr;c2++,i++){
      element[i] = (extract_ligne(l,0,column_nbr) | m.extract_col(0,line_nbr,c2));
      
    }
  }
  return (*this);

}


bool Matrix :: operator == ( Matrix const & m ) const { 
  assert((line_nbr == m.line_nbr) && (column_nbr == m.column_nbr));
  for(unsigned int i=0; i<line_nbr*column_nbr;i++){
    if(element[i]!= m.element[i]){
      return false;
    }
  }
  return true;
}


Vector Matrix :: extract_ligne ( unsigned int const l ,
				 unsigned int const c1 ,
				 unsigned int const c2 ) const { 
  assert(c1<=c2);
  Vector v (c2-c1);
  for(unsigned int i=c1,j=0;i<c2;i++,j++){
    v[j] = element [ l * column_nbr + i ];
  }
  return v;
}


Vector Matrix :: extract_col ( unsigned int const l1 ,
			       unsigned int const l2 ,
			       unsigned int const c ) const { 
  assert(l1<=l2);
  Vector v (l2-l1);
  for(unsigned int i=l1,j=0;i<l2;i++,j++){
    v[j] = element [ i * column_nbr + c ];
  }
  return v;

} 


Matrix Matrix :: extract_triangular_lower_diag_one () const { 
  assert(line_nbr==column_nbr);
  Matrix x (line_nbr, column_nbr);
  for(unsigned int l = 0,i=0; l < line_nbr ; l++){
    for(unsigned int c = 0; c < column_nbr ; c++,i++){
      if(l<c){
        x.element[i] = 0;
      }else if(l>c){
        x.element[i] = element[i];
      }else{
        x.element[i] = 1;
      }
    }
  }
  return x;
}


Matrix Matrix :: extract_triangular_upper_diag () const { 
  assert(line_nbr==column_nbr);
  Matrix x (line_nbr, column_nbr);
  for(unsigned int l = 0,i=0; l < line_nbr ; l++){
    for(unsigned int c = 0; c < column_nbr ; c++,i++){
      if(l>c){
        x.element[i] = 0;
      }else if(l<c){
        x.element[i] = element[i];
      }else{
        x.element[i] = 1;
      }
    }
  }
  return x;
}


Matrix Matrix :: extract_diagonal () const { 
  assert(line_nbr==column_nbr);
  Matrix x (line_nbr, column_nbr);
  for(unsigned int l = 0,i=0; l < line_nbr ; l++){
    for(unsigned int c = 0; c < column_nbr ; c++,i++){
      if(l==c){
        x.element[i] = element[i];
      }else{
        x.element[i] = 0;
      }
    }
  }
  return x;
}


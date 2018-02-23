# include <stdlib.h>

# include "vector.hpp"


# undef NDEBUG
# include <assert.h>


using namespace std ; 


// Might prove usefull
# define COPY_VECT( v_dest , v_source )					\
  {									\
    ( v_dest ) . size = ( v_source ) . size ;				\
    element = new float [ size ] ;					\
    for ( unsigned int i = 0 ; i < size ; i++ ) {			\
      ( v_dest ) . element [ i ] = ( v_source ) . element [ i ] ;	\
    }									\
  }


Vector :: Vector ( const Vector & v ) {
	Vector w (v.size);
	COPY_VECT(w,v);
}

Vector :: ~Vector () { 
	delete [] element;
}


void Vector :: init_alea () { 
  for ( unsigned int i = 0 ; i < size ; i++ ) {	
    element[ i ] = drand48 () ; 
  }					
}


float & Vector :: operator [] ( unsigned int const i ) { 
  return element[i] ;
}


float const & Vector :: operator [] ( unsigned int const i ) const { 
  return element[i];
}


std :: ostream & operator << ( std :: ostream& ost ,Vector const & v ) {
	ost << "("<< v.element[0] <<"," ;
	for(unsigned int i=1;i<v.size-1;i++){
		ost << v.element[i]<<",";
	}
	cout << v.element[v.size-1] << ")"<< endl ;
 	return ost ; 
}


Vector & Vector :: operator = ( Vector const & v ) {
	*this=v;
  return ( * this ) ; 
}


Vector Vector :: operator + ( Vector const & v ) const {
	assert(size==v.size);
	Vector s(size);
	s.size=size;
	for(unsigned int i=0;i<size;i++){
		s.element[i]=element[i]+v.element[i];
	}
	return s ;
}


Vector Vector :: operator - ( Vector const & v ) const { 
	assert(size==v.size);
	Vector d(size);
	d.size=size;
	for(unsigned int i=0;i<size;i++){
		d.element[i]=element[i]-v.element[i];
	}
	return d ;
}


Vector Vector :: operator * ( float const a ) const {
	Vector p (size);
	p.size=size;
	for(unsigned int i=0;i<size;i++){
		p.element[i]=a*element[i];
	}
	return p ;
}


float Vector :: operator | ( Vector const & v ) const {
	assert(size==v.size);
	float sum=0;
	//float prod=1;
	for(unsigned int i=0;i<size;i++){
		sum+=v.element[i]*element[i];
	}
	return sum;
}


bool Vector :: operator == ( Vector const & v ) const {
	assert(size==v.size);
	for(unsigned int i=0;i<size;i++){
		if(element[i]!=v.element[i]) return false;
	}
  	return true;
}


Vector operator * ( float const a ,Vector const & v ) { 
  	return v*a;
}



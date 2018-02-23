# include "factorize_lu.hpp"

# undef NDEBUG
# include <assert.h>


void factorize_lu ( Matrix & m ) { 
    assert(m->get_column_nbr == m->get_line_nbr);
    Matrix lu (m->get_line_nbr,m->get_column_nbr);
    for(unsigned int k=0;k<m->get_column_nbr;k++){
        for(unsigned int i=k+1;i<m->get_line_nbr;i++){
            m(i,k) = m(i,k) /  m(i,j);
            for(unsigned intj=k+1;k<m->get_column_nbr;k++){
                m(i,j) = m(i,j) - (m(i,j)*m(k,j)); 
            }
        }

    }

}



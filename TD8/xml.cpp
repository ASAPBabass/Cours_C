


# include <string>
# include <fstream>

# include <iostream>

# include "xml.hpp"

#include <sstream>

# undef NDEBUG
# include <assert.h>


using namespace std ; 

extern char const open_sons [] = " ( " ;
  /*! Separator between brothers for example.
   * Have to be declared as extern and array to be a template char cont * parameter. */
extern char const sep_brothers [] = " , " ;
  /*! Closing parenthesis for example.
   * Have to be declared as extern and array to be a template char cont * parameter. */
extern char const close_sons [] = " )" ;

void delete_Tag ( Tag * & t ) {
  delete t ;
}


namespace {

  char const * const STR_SPC = " \t" ;
  
  /*
   * Remove all trailing space at beginning and end.
   * \param str string to be trimmed.
   */
  void trim ( string & str ) {
	  for(unsigned int i=0;i<str.length();i++){
		  if(str[i]==' ') str.erase(i,1);
    }
  }

  /*
   * Test if a trimmed string is an opening tag (of the form '<' then a letter then letters and/or digits then '>')
   * If this is an opening tag, then the string is reduced to the letters and digits. 
   * \param str trimmed string.
   * \return true if this is an opening tag.
   */
  bool is_opening_tag ( string & str ) {
	  trim(str);
	  if(str[0]=='<' && str[1]!='/'){
      str.erase(0,1);
      str.erase(str.length()-1,1);
	    return true ; 
    }else return false;
  }

  /*
   * Test if a trimmed string is an closing tag (of the form "</" then a letter then letters and/or digits then '>')
   * If this is an closing tag, then the string is reduced to the letters and digits. 
   * \param str trimmed string.
   * \return true if this is an closing tag.
   */
  bool is_closing_tag ( string & str ) { 
    assert(2<str.length());
    trim(str);
    if(str[1]=='/'&&str[0]=='<'){
      str.erase(0,2);
      str.erase(str.length()-1,1);  
      return true;
    }else return false;
  }

  enum load_state {
    beginning ,
    beginning_open ,
    last_open_son ,
    last_open_brother ,
    last_data ,
    last_close 
  } ;
    
}


# define FAIL_LOAD return NULL ; 


/*! This one comes with debugging outputs. */
# define TEST_TAG( lib1 , lib2 )				\
  if ( ( lib1 ) != ( lib2 ) ) {					\
    cerr << "ERROR " << * xml << endl ;				\
    cerr << "tag " << ( lib1 ) <<  " is closed by " << endl ;	\
    cerr << "tag " << ( lib2 ) << endl  ;			\
    FAIL_LOAD ;							\
  }



Xml * Xml :: load ( char const * const file_name ) {
  load_state ls=beginning;
  string str1,str2;
  ifstream file (file_name); 
  
  //getline(file,str1);
  getline(file,str1);
  assert(is_opening_tag(str1));
  
  /*Tag_Inner t = Tag_Inner(str1);
  Tree < Tag *, delete_Tag > tree ( &t ) ;
  Node < Tag *, delete_Tag > *node_current = tree . get_root () ;*/
  ls=beginning;
  bool fin=false;
  cout << str1 << endl;
  cout << str1 << endl;
  Tree < Tag *, delete_Tag > * ptr_tree=NULL;
  
  while(!fin){
    
    Node < Tag *, delete_Tag > * node_current;
    
    getline(file,str2);
   // is_opening_tag(str2);
    cout << ls << endl;
    switch(ls){
       
      case beginning : 
        if(!is_opening_tag(str2)){
          cout << str2 << "opening" << endl;
          Tag_Inner t = Tag_Inner(str1);
          
          ls=last_open_son;
          Tree < Tag *, delete_Tag > tree ( &t ) ;
          Node < Tag *, delete_Tag > *node_current = tree . get_root () ;
          ptr_tree=&(tree);
          //node_current=node_current;
        }else if(is_closing_tag(str2)){
          cout << str2 << "closing" << endl;
          Tag_Inner t = Tag_Inner(str1);
          ls=last_close;
          Tree < Tag *, delete_Tag > tree ( &t ) ;
          Node < Tag *, delete_Tag > *node_current = tree . get_root () ;
          ptr_tree=&(tree);
          //node_current=&(*node_current);
        }else{ //forcément un data
          cout << str2 << "data" << endl;
          //*ptr_node_current=(*ptr_node_current)->add_left_son(new Tag_Data(str1,str2));
          Tag_Data t = Tag_Data(str1,str2);
          ls=last_close;
          Tree < Tag *, delete_Tag > tree ( &t ) ;
          Node < Tag *, delete_Tag > *node_current = tree . get_root () ;
          ptr_tree=&(tree);
          //ptr_node_current=&(*node_current);
          getline(file,str2);
        }
        str1=str2;
        break;

      /*case beginning_open :
        if(is_opening_tag(str2)){
          *ptr_node_current=*ptr_node_current->add_left_son(new Tag_Inner(str1));
          ls=last_open_son;
        }else if(is_closing_tag(str2)){
          ls=last_close;
        }else{ //forcément un data
          *ptr_node_current=(*ptr_node_current)->add_left_son(=new Tag_Inner(new Tag_Data(str1,str2));
          ls=last_close;//data
          getline(file,str2);
        }
        str1=str2;
      break;*/

      case last_open_son : 
        if(!is_opening_tag(str2)){
          cout << str2 << " OPENING SON" <<endl;
          
          Tag_Inner t1 (str1);
          cout << "ajout fils" << endl;
          //node_current->son
          node_current->add_left_son(&t1);
          assert(NULL!=node_current->get_left_son());
          node_current=node_current->get_left_son();
          cout << "ajout fils2" << endl;
        }else if(is_closing_tag(str2)){
          cout << str2 << " CLOSING SON " <<endl;
          //node_current=node_current->get_father();
          ls=last_close;
        }else{
          cout << str2 << " DATA SON " <<endl;
          (node_current)->add_left_son(new Tag_Data(str1,str2));
          ls=last_close;
          getline(file,str2);
        }
        str1=str2;
        break;

      case last_open_brother : 
        if(!is_opening_tag(str2)){
          node_current=(node_current)->add_left_son(new Tag_Inner(str2));
          ls=last_open_son;
        }else if(is_closing_tag(str2)){
          node_current=(node_current)->get_right_brother();
          ls=last_close;
        }else{
          (node_current)->add_left_son(new Tag_Data(str1,str2));
          ls=last_close;//data
          getline(file,str2);
        }
        str1=str2;
      break;

      case last_data : 
        assert(is_opening_tag(str2));
        //node_current=node_current->get_right_brother();
        ls=last_close;
        break;

      case last_close :
        cout << str2 << endl;
        if(file.eof()){
          fin=true;
          break;
        }else if(!is_opening_tag(str2)){
          node_current=(node_current)->get_right_brother();
          ls=last_open_brother;
        }else if(is_closing_tag(str2)){ //forcément un data
          node_current=(node_current)->get_father();
          ls=last_close;
        }else{
          printf("GROS PROBLEME");
        }
        str1=str2;
        break;

      default : fin=true;
        cout << "GROS PROBLEME";
        break;
    }

    
  }
  Xml * xml = new Xml(ptr_tree);
  file.close();

  return xml;
  
} 





std :: ostream & operator << ( std :: ostream & out ,
			       Xml const & xml ) {  
  //char* open_sons_parent =  , sep_brothers_comma , close_sons_parent > (out);
  //std::stack < Node<Tag *, delete_Tag>* > l;
	Node <Tag *, delete_Tag> * p =xml.tree->get_root();
	while(NULL!=p){
		out << p->get_value()->get_tag() << endl;
		if(NULL!=p->get_left_son() && NULL!=p->get_right_brother()){
			p=p->get_left_son();
		}
		else if(NULL!=p->get_left_son() && NULL==p->get_right_brother()){
			p=p->get_left_son();
		}
		else if(NULL==p->get_left_son() && NULL!=p->get_right_brother()){
			p=p->get_right_brother();
		}else{
      out << p->get_value()->get_tag() << endl;
      p=NULL;
    } 		
	}
	return out;
 
 /*
  Node < Tag *, delete_Tag > *current = xml.tree->get_root();
   out << (current)->get_value()->get_tag();
  return out;*/
}


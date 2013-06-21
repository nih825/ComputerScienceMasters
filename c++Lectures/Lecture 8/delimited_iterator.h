#ifndef DELIMITED_ITERATOR_H
#  define DELIMITED_ITERATOR_H

#include <boost/function_output_iterator.hpp>
#include <iostream>
#include <string>
using std::basic_ostream;
using std::ostream;
using boost::function_output_iterator;
using std::string;
using std::basic_string;
using std::char_traits;
using std::allocator;

namespace cspp51044 {
// First, a version just for ostreams (no wide chars, etc.)
template<class T>
struct my_do_output {
    my_do_output(ostream &_os, string _del)
        : first(true), os(_os), del(_del) {
    }
    void operator()(T t) {
        if(!first) {
            os << del;
        }
        first = false;
        os << t;
    }
private:
    bool first;
    ostream &os;
    string del;
};

template<class T>
struct my_ostream_iterator
  : public function_output_iterator<my_do_output<T> > {
    my_ostream_iterator(ostream &os, string str)
      : function_output_iterator<my_do_output<T> >(my_do_output<T>(os, str)) {
    }
};

// Now a version for any kind output stream
template
  <class T,
   class CharT,
   class Traits = char_traits<CharT>,
   class Alloc = allocator<CharT> >
struct do_delimited_output {
    do_delimited_output
      (basic_ostream<CharT, Traits> &_os,
       const basic_string<CharT, Traits, Alloc> &_del)
        : first(true), os(_os), del(_del) {
    }
    void operator()(T t) {
        if(!first) {
            os << del;
        }
        first = false;
        os << t;
    }
private:
    bool first;
    basic_ostream<CharT, Traits> &os;
    basic_string<CharT, Traits> del;
};

template
  <class T,
   class CharT = char,
   class Traits = char_traits<CharT>,
   class Alloc = std::allocator<CharT> >
struct delimited_iterator
  : public function_output_iterator
             <do_delimited_output<T, CharT, Traits, Alloc> > {
    delimited_iterator
      (basic_ostream<CharT, Traits> &os, basic_string<CharT, Traits, Alloc> str)
      : function_output_iterator
          <do_delimited_output<T, CharT, Traits, Alloc> >
            (do_delimited_output<T, CharT, Traits, Alloc>(os, str)) {
    }
    delimited_iterator
      (basic_ostream<CharT, Traits> &os, const CharT *str)
      : function_output_iterator
          <do_delimited_output<T, CharT, Traits, Alloc> >
            (do_delimited_output<T, CharT, Traits, Alloc>(os, str)) {
    }
};

}
#endif
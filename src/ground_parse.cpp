#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include "Ground.hpp"

struct commaSeparator : std::ctype<char> {
  commaSeparator(std::size_t refs = 0) : ctype<char>(make_table(), false, refs) {}

  static const mask* make_table()
    {
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[','] |= static_cast<mask>(std::ctype_base::space);
        //v[' '] &= static_cast<mask>(~std::ctype_base::space);
        return &v[0];
    }
}; //Modified from the example on https://en.cppreference.com/w/cpp/locale/ctype_char,
   //and https://stackoverflow.com/a/7304184


Ground Ground::generate_file(char const * fname)
{
  std::ifstream file;
  std::vector<std::size_t> temp;
  file.exceptions(std::ifstream::badbit);
  file.open(fname);
  // std::string const data = [&] (void) {
  //                            std::ostringstream tmp;
  //                            tmp << file.rdbuf();
  //                            return tmp.str();} ();
  file.imbue(std::locale(file.getloc(), new commaSeparator{}));

  //Testing
  std::size_t word;
  while(file >> word) {
    std::cout << "IS GOOD : " << (file.good() ? "YES" : "NO") << "\t: " << word << '\n';
  }
  std::cout << "Good: " << (file.good() ? "YES" : "NO") << '\n';
  std::cout << "fail: " << (file.fail() ? "YES" : "NO") << '\n';
  std::cout << "Bad : " << (file.bad() ? "YES" : "NO") << '\n';
  std::cout << "EOF : " << (file.eof() ? "YES" : "NO") << '\n';
  return Ground{temp};
}

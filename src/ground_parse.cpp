#include <fstream>
#include <string>
#include <sstream>
#include <string_view>
#include "Ground.hpp"


Ground Ground::generate_file(char const * fname)
{
  std::ifstream file;
  std::vector<std::size_t> temp;
  file.exceptions(std::ifstream::badbit);
  file.open(fname);
  std::string const data = [&] (void) {
                               std::ostringstream tmp;
                               tmp << file.rdbuf();
                               return tmp.str();} ();
  return Ground{temp};
}

#include <fstream>
#include <string>
#include <sstream>
#include <string_view>
#include "Ground.hpp"
#include "InvalidGroundHeight.hpp"
#include "ParseGround.hpp"

struct commaSeparator : std::ctype<char> {
  commaSeparator(std::size_t refs = 0) : ctype<char>(make_table(), false, refs) {}

  static const mask* make_table()
    {
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[','] |= static_cast<mask>(std::ctype_base::space);
        v[' '] &= static_cast<mask>(~std::ctype_base::space);
        return &v[0];
    }
}; //Modified from the example on https://en.cppreference.com/w/cpp/locale/ctype_char,
   //and https://stackoverflow.com/a/7304184


Ground Ground::generate_file(char const * fname)
{
  std::ifstream file;
  std::vector<std::size_t> temp;
  file.open(fname);
  auto const baseExceptionsMask = file.exceptions();
  file.exceptions(std::ifstream::failbit);
  file.imbue(std::locale(file.getloc(), new commaSeparator{}));
  file.exceptions(baseExceptionsMask);

  //Testing
  std::string word;
  std::size_t count = 0;
  while(file >> word && count <= 10) {
    //TODO : This seems so resourcefull and unoptimized
    std::istringstream strm{word};
    std::ostringstream backBuffer;
    std::string middleBuffer;
    while(strm >> middleBuffer){
      backBuffer << middleBuffer;
    }
    middleBuffer = backBuffer.str();
    strm = std::istringstream{middleBuffer};
    std::size_t data;
    strm >> data;
    if(data > 9){
      throw Exc::InvalidGroundHeight{count};
    }
    temp.emplace_back(data);
    count++;
    if(!strm.eof()){
      //Error
      throw Exc::GroundParse{count};
    }
  }
  return Ground{temp};
}

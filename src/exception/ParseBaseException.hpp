#ifndef MINTAKA_EXCEPTION_FILE_PARSE_BASE_HEAD_HPP
#define MINTAKA_EXCEPTION_FILE_PARSE_BASE_HEAD_HPP
#include <utility>
#include "BaseException.hpp"

namespace Exc
{
  class ParseBase : public Exc::Base
  {
  private:
    std::size_t charLoc;
  public:
    ParseBase(std::size_t loc = 0) :
      Base{"Unknown Parsing File Error"},
      charLoc{loc}
    {}
    ParseBase(char const * in, std::size_t loc = 0) :
      Base{in},
      charLoc{loc}
    {}
    ParseBase(std::string && in, std::size_t loc = 0) :
      Base{std::move(in)},
      charLoc{loc}
    {}
    ParseBase(std::string const & in, std::size_t loc = 0) :
      Base{in},
      charLoc{loc}
    {}
    virtual std::size_t where(void) const noexcept {
      return this->charLoc;
    }
    virtual ~ParseBase(void){}
  };
}

#endif //MINTAKA_EXCEPTION_FILE_PARSE_BASE_HEAD_HPP

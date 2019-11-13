#ifndef MINTAKA_EXCEPTION_FONT_DIR_HEAD_HPP
#define MINTAKA_EXCEPTION_FONT_DIR_HEAD_HPP
#include <string>
#include "BaseException.hpp"

namespace Exc
{
  class FontDir : public Exc::Base
  {
  public:
    FontDir(void) :
      Base{std::move(std::string{"Unable to open font on: "})}
    {}
    FontDir(char const * in) :
      Base{std::move(std::string{"Unable to open font on: "} + in)}
    {}
    FontDir(std::string && in) :
      Base{std::move(std::string{"Unable to open font on: "} + std::move(in))}
    {}
    FontDir(std::string const & in) :
      Base{std::move(std::string{"Unable to open font on: "} + in)}
    {}
    virtual ~FontDir(void){}
    virtual int excID(void) const noexcept {
      return 15;
    }
  };
}

#endif //MINTAKA_EXCEPTION_FONT_DIR_HEAD_HPP

#ifndef MINTAKA_EXCEPTION_BASE_HEAD_HPP
#define MINTAKA_EXCEPTION_BASE_HEAD_HPP
#include <string>
#include <utility>
#include <exception>

namespace Exc
{
  class Base : public std::exception
  {
  private:
    std::string text;
  public:
    Base(void) :
      text{}
    {}
    Base(char const * in) :
      text{in}
    {}
    Base(std::string && in) :
      text{std::move(in)}
    {}
    Base(std::string const & in) :
      text{in}
    {}
    virtual ~Base(void){}
    virtual char const * what(void) const noexcept {
      return text.c_str();
    }
    virtual int excID(void) const noexcept = 0;
  };
}

#endif //MINTAKA_EXCEPTION_BASE_HEAD_HPP

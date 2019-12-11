#ifndef MINTAKA_EXCEPTION_GROUND_PARSE_HEAD_HPP
#define MINTAKA_EXCEPTION_GROUND_PARSE_HEAD_HPP
#include <utility>
#include "ParseBaseException.hpp"

namespace Exc
{
  class GroundParse final : public Exc::ParseBase
  {
  public:
    GroundParse(std::size_t loc = 0) :
      ParseBase{"Ground parsing error", loc}
    {}
    virtual ~GroundParse(void){}
    virtual int excID(void) const noexcept {
      return 21;
    }
  };
}

#endif //MINTAKA_EXCEPTION_GROUND_PARSE_HEAD_HPP

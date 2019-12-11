#ifndef MINTAKA_EXCEPTION_INVALID_GROUND_HEIGHT_HEAD_HPP
#define MINTAKA_EXCEPTION_INVALID_GROUND_HEIGHT_HEAD_HPP
#include <utility>
#include "ParseBaseException.hpp"

namespace Exc
{
  class InvalidGroundHeight final : public Exc::ParseBase
  {
  public:
    InvalidGroundHeight(std::size_t loc = 0) :
      ParseBase{"Ground Height invalid", loc}
    {}
    virtual ~InvalidGroundHeight(void){}
    virtual int excID(void) const noexcept {
      return 22;
    }
  };
}

#endif //MINTAKA_EXCEPTION_INVALID_GROUND_HEIGHT_HEAD_HPP

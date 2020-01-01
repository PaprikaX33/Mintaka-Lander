#ifndef MINTAKA_UTILS_RANGE_HEAD_HPP
#define MINTAKA_UTILS_RANGE_HEAD_HPP
#include <algorithm>

namespace utls
{
  template <typename T>
  struct Range
  {
    T min;
    T max;
    constexpr Range(T const & l, T const & r) :
      min{std::min(l, r)},
      max{std::max(l, r)}
    {}
    template <typename Compare>
    constexpr Range(T const & l, T const & r, Compare comp) :
      min{std::min(l, r, comp)},
      max{std::max(l, r, comp)}
    {}
  };
  template<typename T>
  bool overlap(T const & lf, T const & rg) noexcept
  {
    return (lf.min >= rg.min && lf.min <= rg.max) || (lf.max >= rg.min && lf.max <= rg.max);
  }
}

#endif //MINTAKA_UTILS_RANGE_HEAD_HPP

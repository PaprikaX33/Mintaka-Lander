#ifndef MINTAKA_UTILS_RANGE_HEAD_HPP
#define MINTAKA_UTILS_RANGE_HEAD_HPP
#include <algorithm>
#include <utility>

namespace utls
{
  template <typename T>
  struct Range
  {
    T min;
    T max;
    template <typename Ti>
    constexpr Range(Ti && l, Ti && r) :
      min{std::min(std::forward<Ti>(l), std::forward<Ti>(r))},
      max{std::max(std::forward<Ti>(l), std::forward<Ti>(r))}
    {}
    template <typename Ti, typename Compare>
    constexpr Range(Ti && l, Ti && r, Compare comp) :
      min{std::min(std::forward<Ti>(l), std::forward<Ti>(r), comp)},
      max{std::max(std::forward<Ti>(l), std::forward<Ti>(r), comp)}
    {}
  };
  template<typename T>
  bool overlap(T const & lf, T const & rg) noexcept
  {
    return (lf.min >= rg.min && lf.min <= rg.max) || (lf.max >= rg.min && lf.max <= rg.max);
  }
}

#endif //MINTAKA_UTILS_RANGE_HEAD_HPP

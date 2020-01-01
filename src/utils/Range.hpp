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
    explicit constexpr Range(T const & v) :
      min{v},
      max{v}
    {}
    constexpr Range(T const & l, T const & r) :
      min{std::min(l, r)},
      max{std::max(l, r)}
    {}
    template <typename Compare>
    constexpr Range(T const & l, T const & r, Compare comp) :
      min{std::min(l, r, comp)},
      max{std::max(l, r, comp)}
    {}

    constexpr Range & append(T const & v)
    {
      min = std::min(min, v);
      max = std::max(max, v);
      return *this;
    }

    template <typename Compare>
    constexpr Range & append(T const & v, Compare comp)
    {
      min = std::min(min, v, comp);
      max = std::max(max, v, comp);
      return *this;
    }
  };

  template<typename T>
  bool overlap(T const & lf, T const & rg) noexcept
  {
    return (lf.min >= rg.min && lf.min <= rg.max) || (lf.max >= rg.min && lf.max <= rg.max);
  }
}

#endif //MINTAKA_UTILS_RANGE_HEAD_HPP

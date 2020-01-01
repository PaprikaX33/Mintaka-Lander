#ifndef MINTAKA_UTILS_RANGE_HEAD_HPP
#define MINTAKA_UTILS_RANGE_HEAD_HPP

namespace utls
{
  template <typename T>
  struct Range
  {
    T min;
    T max;
    explicit constexpr Range(T const & v);
    constexpr Range(T const & l, T const & r);

    template <typename Compare>
    constexpr Range(T const & l, T const & r, Compare comp);

    constexpr Range & append(T const & v);

    template <typename Compare>
    constexpr Range & append(T const & v, Compare comp);
  };

  template<typename T>
  constexpr bool overlap(Range<T> const & lf, Range<T> const & rg) noexcept;
}

#include "Range.inl"

#endif //MINTAKA_UTILS_RANGE_HEAD_HPP

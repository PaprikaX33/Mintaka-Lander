#ifndef MINTAKA_UTILS_RANGE_HEAD_HPP
#define MINTAKA_UTILS_RANGE_HEAD_HPP

namespace utls
{
  template <typename T>
  struct Range
  {
    T min;
    T max;
    explicit constexpr Range(T const &);
    constexpr Range(T const &, T const &);

    template <typename Compare>
    constexpr Range(T const &, T const &, Compare);

    constexpr Range & append(T const &);
    template <typename Compare>
    constexpr Range & append(T const &, Compare);

    constexpr bool contains(T const &) const;
  };

  template <typename T>
  constexpr bool overlap(Range<T> const &, Range<T> const &) noexcept;

  template <typename T>
  constexpr bool contains(T const &, Range<T> const &) noexcept;
}

#include "Range.inl"

#endif //MINTAKA_UTILS_RANGE_HEAD_HPP

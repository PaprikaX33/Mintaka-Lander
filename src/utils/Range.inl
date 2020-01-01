#include <algorithm>
template <typename T>
inline constexpr utls::Range<T>::Range(T const & v) :
  min{v},
  max{v}
{}

template <typename T>
inline constexpr utls::Range<T>::Range(T const & l, T const & r) :
  min{std::min(l, r)},
  max{std::max(l, r)}
{}

template <typename T>
inline constexpr utls::Range<T> & utls::Range<T>::append(T const & v)
{
  min = std::min(min, v);
  max = std::max(max, v);
  return *this;
}

template <typename T>
template <typename Compare>
inline constexpr utls::Range<T>::Range(T const & l, T const & r, Compare comp) :
  min{std::min(l, r, comp)},
  max{std::max(l, r, comp)}
{}

template <typename T>
template <typename Compare>
inline constexpr utls::Range<T> & utls::Range<T>::append(T const & v, Compare comp)
{
  min = std::min(min, v, comp);
  max = std::max(max, v, comp);
  return *this;
}

template <typename T>
constexpr bool utls::Range<T>::contains(T const & val) const
{
  return (val >= min || val <= max);
}

template <typename T>
inline constexpr bool utls::overlap(Range<T> const & lf, Range<T> const & rg) noexcept
{
  return (lf.min >= rg.min && lf.min <= rg.max) || (lf.max >= rg.min && lf.max <= rg.max);
}

template <typename T>
constexpr bool utls::contains(T const & val, Range<T> const & rng) noexcept
{
  return rng.contains(val);
}

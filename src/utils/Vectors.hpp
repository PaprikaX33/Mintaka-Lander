#ifndef MINTAKA_UTILS_VECTOR_HEAD_HPP
#define MINTAKA_UTILS_VECTOR_HEAD_HPP
#include <tuple>
#include <SFML/System/Vector2.hpp>

namespace utls
{
  sf::Vector2f normalize(sf::Vector2f const &) noexcept;
  float length(sf::Vector2f const &) noexcept;
  //AXIS MUST BE NORMALIZED
  float projection(sf::Vector2f const & vec, sf::Vector2f const & axis) noexcept;
}

#endif //MINTAKA_UTILS_VECTOR_HEAD_HPP

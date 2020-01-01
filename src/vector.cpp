#include <cmath>
#include "utils/Vectors.hpp"

sf::Vector2f utls::normalize(sf::Vector2f const & in) noexcept
{
  return in / utls::length(in);
}

float utls::length(sf::Vector2f const & in) noexcept
{
  return std::hypotf(in.x, in.y);
}

float utls::projection(sf::Vector2f const & vec, sf::Vector2f const & axis) noexcept
{
  return (vec.x * axis.x) + (vec.y * axis.y);
}

sf::Vector2f utls::normal_right(sf::Vector2f const & in)noexcept
{
  return sf::Vector2f{in.y, (-1.0f) * in.x};
}
sf::Vector2f utls::normal_left(sf::Vector2f const & in)noexcept
{
  return sf::Vector2f{(-1.0f) * in.y, in.x};
}

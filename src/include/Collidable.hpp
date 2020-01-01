#ifndef MINTAKA_COLIDABLE_HEAD_HPP
#define MINTAKA_COLIDABLE_HEAD_HPP
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "utils/Range.hpp"

struct Collidable
{
  virtual std::vector<utls::Range<float>> axis_projection(sf::Vector2f const & axis) const = 0;
  virtual ~Collidable() = default;
};

#endif //MINTAKA_COLIDABLE_HEAD_HPP

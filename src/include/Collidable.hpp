#ifndef MINTAKA_COLIDABLE_HEAD_HPP
#define MINTAKA_COLIDABLE_HEAD_HPP
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "utils/Range.hpp"

struct Collidable
{
  std::vector<sf::Vector2f> _normal;
  virtual utls::Range<float> axis_projection(sf::Vector2f const & axis) const = 0;
  virtual ~Collidable(){}
};

#endif //MINTAKA_COLIDABLE_HEAD_HPP

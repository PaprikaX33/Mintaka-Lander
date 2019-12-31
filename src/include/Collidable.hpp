#ifndef MINTAKA_COLIDABLE_HEAD_HPP
#define MINTAKA_COLIDABLE_HEAD_HPP
#include <SFML/System/Vector2.hpp>

struct Collidable
{
  virtual sf::Vector2f axis_projection(sf::Vector2f const & axis) = 0;
  virtual ~Collidable(){}
};

#endif //MINTAKA_COLIDABLE_HEAD_HPP

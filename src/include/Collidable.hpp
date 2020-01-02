#ifndef MINTAKA_COLIDABLE_HEAD_HPP
#define MINTAKA_COLIDABLE_HEAD_HPP
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "utils/Range.hpp"

struct Collidable
{
  virtual std::size_t number_of_object(void) const = 0;
  //OBJ_no :: 0 <= obj_no < number_of_object()
  virtual utls::Range<float> important_x(std::size_t obj_no) const = 0;
  virtual utls::Range<float> axis_projection(sf::Vector2f const & axis, std::size_t obj_no) const = 0;
  virtual ~Collidable() = default;
};

#endif //MINTAKA_COLIDABLE_HEAD_HPP

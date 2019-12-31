#include <type_traits>
#include <typeinfo>
#include "Collision.hpp"
#include "utils/Range.hpp"

bool collide(Collidable const & lf, Collidable const & rg) noexcept
{
  auto const & nlf = lf._normal;
  auto const & nrg = rg._normal;
  //static_assert(std::is_same<decltype(nlf), std::vector<sf::Vector2f> const &>::value);
  for(auto const & i : nlf){
    auto const lfloc = lf.axis_projection(i);
    auto const rgloc = rg.axis_projection(i);
    if(!utls::overlap(lfloc, rgloc)){
      return false;
    }
  }

  for(auto const & i : nrg){
    auto const lfloc = lf.axis_projection(i);
    auto const rgloc = rg.axis_projection(i);
    if(!utls::overlap(lfloc, rgloc)){
      return false;
    }
  }
  return true;
}

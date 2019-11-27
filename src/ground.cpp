#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Ground.hpp"

Ground::Ground(std::vector<size_t> const & in) :
  _sprite{sf::LineStrip, 11},
  _anchor{sf::Transform::Identity}
{
  std::size_t count = 0;
  for(auto const & i : in){
    _sprite[count] = sf::Vertex{sf::Vector2f{static_cast<float>(count) * 100.0f,
                                             static_cast<float>(i) * Ground::unit_height}, sf::Color::Green};
    if(count == 11u){
      break;
    }
    ++count;
  }
  for(;count < 11; ++count){
    _sprite[count] = sf::Vertex{sf::Vector2f{static_cast<float>(count) * 100.0f,
                                             Ground::unit_height}, sf::Color::Green};
  }
  _anchor.translate(0.0f, 1000.0f);
  _anchor.scale(1.0f,-1.0f);
}

Ground::~Ground(void)
{

}

void Ground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= _anchor;
  target.draw(_sprite, states);
}

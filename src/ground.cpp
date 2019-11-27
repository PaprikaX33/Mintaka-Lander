#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Ground.hpp"

Ground::Ground(void) :
  _sprite{sf::LineStrip, 11},
  _anchor{sf::Transform::Identity}
{
  for(auto i = 0u ; i < 11; i++){
    _sprite[i] = sf::Vertex{sf::Vector2f{static_cast<float>(i) * 100.0f,
                                         static_cast<float>(i % 2) * Ground::unit_height}, sf::Color::Green};
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

#include <cmath>
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

float Ground::objRelHeight(sf::Vector2f const & pos) const
{
  //TODO : This seems broken
  if(pos.x <= 0.0f){
    return ((_anchor * _sprite[0].position).y) - pos.y;
  }
  if(pos.x >= 1000.0f){
    return ((_anchor * _sprite[10].position).y) - pos.y;
  }
  float const x_rel = pos.x / 100.0f;
  std::size_t const left_bound = static_cast<std::size_t>(std::floor(x_rel));
  float const x_diff = pos.x - std::floor(pos.x);
  float const lower = (_anchor * _sprite[left_bound].position).y;
  float const higher = (_anchor * _sprite[left_bound + 1].position).y;
  float const gradient = (higher - lower) / 100.0f;
  float const y_dir = (gradient * x_diff) + lower;
  return y_dir - pos.y;
}

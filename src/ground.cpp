#include <utility>
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Ground.hpp"
#include "utils/Vectors.hpp"

Ground::Ground(std::vector<size_t> const & in) :
  _sprite{sf::LineStrip, 11},
  _anchor{sf::Transform::Identity},
  _heightMap{in}
{
  generate_sprite();
}

Ground::Ground(std::vector<size_t> && in) :
  _sprite{sf::LineStrip, 11},
  _anchor{sf::Transform::Identity},
  _heightMap{std::move(in)}
{
  generate_sprite();
}

void Ground::generate_sprite(void)
{
  std::size_t count = 0;
  for(auto const & i : _heightMap){
    _sprite[count] = sf::Vertex{sf::Vector2f{static_cast<float>(count) * 100.0f,
                                             static_cast<float>(i) * Ground::unit_height}, sf::Color::Green};
    if(count >= 11u){
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
Ground::~Ground(void) = default;

void Ground::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= _anchor;
  target.draw(_sprite, states);
}

bool Ground::is_hit(Collidable const & col) const
{
  auto const num = col.number_of_object();

  for(auto pol_num = 0u; pol_num < num; pol_num++){
    auto const imp = col.important_x(pol_num);
    int const lf = static_cast<int>(std::floor(imp.min / 100.0f));
    int const rg = static_cast<int>(std::ceil(imp.max / 100.0f));
    int step = lf;
    bool pass = false;
    while(step < rg){
      auto const & loc_lf = step < 0 ?
                                   _sprite[0].position :
                                   step > static_cast<int>(_sprite.getVertexCount()) ?
        _sprite[_sprite.getVertexCount() -1].position :
        _sprite[static_cast<std::size_t>(step)].position;

      auto const & loc_rg = step + 1 < 0 ?
                                       _sprite[0].position :
                                       step + 1 > static_cast<int>(_sprite.getVertexCount()) ?
        _sprite[_sprite.getVertexCount() -1].position :
        _sprite[static_cast<std::size_t>(step + 1)].position;
      auto const difference = ((_anchor * loc_rg) - ( _anchor * loc_lf));
      auto const axis = utls::normalize(utls::normal_right(difference));
      auto const player_proj = col.axis_projection(axis, pol_num);
      auto const self_proj = utls::projection(_anchor * loc_lf,  axis);
      if(!utls::contains(self_proj, player_proj)){
        pass = true;
        break;
      }
      step++;
    }
    if(!pass){
      return true;
    }
  }
  return false;
}

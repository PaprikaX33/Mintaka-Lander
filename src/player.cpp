#include <SFML/Graphics/RenderTarget.hpp>
#include "Player.hpp"

Player::Player(void) :
  _velocity{0.0f, 0.0f},
  _sprite{sf::LineStrip, 5}
{
  _sprite[0] = sf::Vertex{sf::Vector2f{10.0f,  0.0f}, sf::Color::Green};
  _sprite[1] = sf::Vertex{sf::Vector2f{20.0f, 20.0f}, sf::Color::Green};
  _sprite[2] = sf::Vertex{sf::Vector2f{10.0f, 15.0f}, sf::Color::Green};
  _sprite[3] = sf::Vertex{sf::Vector2f{ 0.0f, 20.0f}, sf::Color::Green};
  _sprite[4] = sf::Vertex{sf::Vector2f{10.0f,  0.0f}, sf::Color::Green};
  this->setOrigin(10.0f, 10.0f);
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(_sprite, states);
}

sf::FloatRect Player::getBounds(void) const
{
  return _sprite.getBounds();
}

sf::Vector2<sf::Vector2f> Player::getCollisionBounds(void) const
{
  auto const & trns= this->getTransform();
  auto const first_node = trns * _sprite[0].position;
  sf::Vector2<sf::Vector2f> bound{{first_node.x, first_node.y},
                                  {first_node.x, first_node.y}};
  for(std::size_t i = 1; i < 4; i++){
    auto const i_node = trns * _sprite[i].position;
    if(i_node.x < bound.x.x){
      bound.x.x = i_node.x;
    }
    if(i_node.y < bound.x.y){
      bound.x.y = i_node.y;
    }

    if(i_node.x > bound.y.x){
      bound.y.x = i_node.x;
    }
    if(i_node.y > bound.y.y){
      bound.y.y = i_node.y;
    }
  }
  return bound;
}

Player::~Player(void)
{

}

sf::Vector2f Player::getCenterPoint(void) const
{
  return this->getTransform().transformPoint(10.0f,10.0f);
}

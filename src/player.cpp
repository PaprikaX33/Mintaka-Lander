#include <SFML/Graphics/RenderTarget.hpp>
#include "Player.hpp"

Player::Player() :
  _velocity{0.0f, 0.0f},
  _sprite{sf::LineStrip, 5}
{
  //Vertex (const Vector2f &thePosition, const Color &theColor)
  _sprite[0] = sf::Vertex{sf::Vector2f{10.0f,  0.0f}, sf::Color::Green};
  _sprite[1] = sf::Vertex{sf::Vector2f{20.0f, 20.0f}, sf::Color::Green};
  _sprite[2] = sf::Vertex{sf::Vector2f{10.0f, 15.0f}, sf::Color::Green};
  _sprite[3] = sf::Vertex{sf::Vector2f{ 0.0f, 20.0f}, sf::Color::Green};
  _sprite[4] = sf::Vertex{sf::Vector2f{10.0f,  0.0f}, sf::Color::Green};
  this->setOrigin(10.0f, 10.0f);
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  // apply the entity's transform -- combine it with the one that was passed by the caller
  states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

  // draw the vertex array
  target.draw(_sprite, states);
}

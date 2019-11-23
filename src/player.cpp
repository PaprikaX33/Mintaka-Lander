#include <iostream>
#include <array>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Player.hpp"

static constexpr std::array<std::size_t, 3> important{0,1,3};

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
  this->setPosition(sf::Vector2f{500.0f, 500.0f});
}

void Player::reset(void)
{
  this->setPosition(sf::Vector2f{500.0f, 500.0f});
  this->setRotation(0.0f);
  _velocity = sf::Vector2f{0.0f,0.0f};
}

void Player::apply_movement(float time)
{
  (void) time;
  this->move(_velocity);
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
  for(auto && i : important){
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
    std::cout << "Checked " << i << '\n';
  }
  return bound;
}

Player::~Player(void)
{

}

sf::Vector2f Player::getCenterPoint(void) const
{
  return this->getTransform().transformPoint(this->getOrigin());
}

sf::Vector2f const & Player::velocity(sf::Vector2f const & in)
{
  _velocity = in;
  return _velocity;
}
sf::Vector2f const & Player::velocity(void)
{
  return _velocity;
}
sf::Vector2f const & Player::velocity_add(sf::Vector2f const & in)
{
  return (_velocity += in);
}

void Player::vertical_stop(void)
{
  _velocity.y = 0.0f;
}

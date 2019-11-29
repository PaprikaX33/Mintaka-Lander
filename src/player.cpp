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
  //TODO Do proper movement
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

void Player::collisionCheck(Ground const & grnd)
{
  auto const & trans = this->getTransform();
  for(auto const & i : important){
    sf::Vector2f absPos = trans * _sprite[i].position;
    float const diff = grnd.objRelHeight(absPos);
    if(diff < 0.0f){
      std::cout << "\x1B[93m";
      this->move(0.0f, diff);
      //this->_velocity = sf::Vector2f{_velocity.x, 0.0f};
      this->_velocity = sf::Vector2f{0.0f, 0.0f};
    }
    std::cout << i << " : " << diff << " : " << absPos.x << ',' << absPos.y  << "\n\x1B[0m";
  }
  std::cout << '\n';
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
  if(_velocity.x < 0.0f){
    _velocity.x += 0.1f;
  }
  else{
    _velocity.x -= 0.1f;
  }
}

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

std::pair<float, float> Player::getHorizontalExtremities(void) const
{
  auto const & trans = this->getTransform();
  float initial = (trans * _sprite[0].position).x;
  std::pair<float, float> bound = std::make_pair(initial, initial);
  for(auto && i : important){
    float current = (trans * _sprite[i].position).x;
    if(current < bound.first){
      bound.first = current;
    }
    if(current > bound.second){
      bound.second = current;
    }
  }
  return bound;
}

void Player::collisionCheck(sf::Vector2f l, sf::Vector2f r)
{
  //Convert from Ground Height to world height, where 1000.0f is bottom, and 0.0f is top
  float const leftHeight = 1000.0f - l.y;
  float const rightHeight = 1000.0f - r.y;
  std::cout << "left " <<  l.x << ',' << leftHeight <<  " right "  <<  r.x << ',' << rightHeight << '\n';
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

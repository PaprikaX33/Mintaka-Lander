#include <array>
#include <SFML/Graphics/RenderTarget.hpp>
#include "utils/Vectors.hpp"
#include "Player.hpp"

static constexpr std::array<std::size_t, 3> important{0,1,3};
static auto const pos0 = sf::Vector2f{  0.0f, -10.0f};
static auto const pos1 = sf::Vector2f{ 10.0f,  10.0f};
static auto const pos2 = sf::Vector2f{  0.0f,   5.0f};
static auto const pos3 = sf::Vector2f{-10.0f,  10.0f};

Player::Player(void) :
  _velocity{0.0f, 0.0f},
  _sprite{sf::LineStrip, 5}
{
  _sprite[0] = sf::Vertex{pos0, sf::Color::Green};
  _sprite[1] = sf::Vertex{pos1, sf::Color::Green};
  _sprite[2] = sf::Vertex{pos2, sf::Color::Green};
  _sprite[3] = sf::Vertex{pos3, sf::Color::Green};
  _sprite[4] = sf::Vertex{pos0, sf::Color::Green};
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
  auto const from {this->getPosition()};
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
std::vector<utls::Range<float>> Player::axis_projection(sf::Vector2f const & axis) const
{
  std::vector<utls::Range<float>> vec;
  //RIGHT POLYGON
  {
    utls::Range<float> range{utls::projection(pos0, axis)};
    range.append(utls::projection(pos1, axis));
    range.append(utls::projection(pos2, axis));
    vec.emplace_back(range);
  }
  //LEFT POLYGON
  {
    utls::Range<float> range{utls::projection(pos0, axis)};
    range.append(utls::projection(pos2, axis));
    range.append(utls::projection(pos3, axis));
    vec.emplace_back(range);
  }
  return vec;
}

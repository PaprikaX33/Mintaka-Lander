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

void Player::speed_stop(void)
{
  _velocity = sf::Vector2f{0.0f, 0.0f};
}


//COLLIDABLE
std::size_t Player::number_of_object(void) const
{
  return 2u;
}

utls::Range<float> Player::important_x(std::size_t obj_no) const
{
  auto const & trns = this->getTransform();
  auto const ipos0 = trns * pos0;
  auto const ipos2 = trns * pos2;
  utls::Range<float> temp{ipos0.x, ipos2.x};
  switch(obj_no){
  default:
    return utls::Range<float>{0.0f};
  case 0: //RIGHT POLYGON
    {
      auto const ipos1 = trns * pos1;
      temp.append(ipos1.x);
    } break;
  case 1: //LEFT POLYGON
    {
      auto const ipos3 = trns * pos3;
      temp.append(ipos3.x);
    } break;
  }
  return temp;
}

utls::Range<float> Player::axis_projection(sf::Vector2f const & axis, std::size_t obj_no) const
{
  auto const & trns = this->getTransform();
  auto const ipos0 = trns * pos0;
  auto const ipos2 = trns * pos2;
  utls::Range<float> range{utls::projection(ipos0, axis), utls::projection(ipos2, axis)};
  switch(obj_no){
  default:
    return utls::Range<float>{0.0f};
  case 0: //RIGHT POLYGON
    {
      auto const ipos1 = trns * pos1;
      range.append(utls::projection(ipos1, axis));
    } break;
  case 1: //LEFT POLYGON
    {
      auto const ipos3 = trns * pos3;
      range.append(utls::projection(ipos3, axis));
    } break;
  }
  return range;
}

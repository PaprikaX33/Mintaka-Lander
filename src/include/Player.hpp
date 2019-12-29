#ifndef MINTAKA_PLAYER_HEAD_HPP
#define MINTAKA_PLAYER_HEAD_HPP
#include <tuple>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include "Ground.hpp"

class Player final : public sf::Drawable,
                     public sf::Transformable
{
private:
  sf::Vector2f _velocity;
  sf::VertexArray _sprite;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
public:
  Player(void);
  virtual ~Player(void) override;
  sf::Vector2f const & velocity(sf::Vector2f const &);
  sf::Vector2f const & velocity(void);
  sf::Vector2f const & velocity_add(sf::Vector2f const &);
  sf::Vector2f getCenterPoint(void) const;
  sf::FloatRect getBounds(void) const;
  void reset(void);
  void apply_movement(float time, Ground const &);
  void vertical_stop(void);
};

#endif //MINTAKA_PLAYER_HEAD_HPP

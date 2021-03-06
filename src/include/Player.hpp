#ifndef MINTAKA_PLAYER_HEAD_HPP
#define MINTAKA_PLAYER_HEAD_HPP
#include <tuple>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include "Ground.hpp"
#include "Collidable.hpp"

class Player final : public sf::Drawable,
                     public sf::Transformable,
                     public Collidable
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

  //COLLIDABLE
  virtual std::size_t number_of_object(void) const;
  virtual utls::Range<float> important_x(std::size_t obj_no) const;
  virtual utls::Range<float> axis_projection(sf::Vector2f const & axis, std::size_t obj_no) const;
  void reset(void);
  void apply_movement(float time);
  void vertical_stop(void);
  void speed_stop(void);
};

#endif //MINTAKA_PLAYER_HEAD_HPP

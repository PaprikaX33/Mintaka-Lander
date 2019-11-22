#ifndef MINTAKA_PLAYER_HEAD_HPP
#define MINTAKA_PLAYER_HEAD_HPP
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

class Player : public sf::Drawable,
               public sf::Transformable
{
private:
  sf::Vector2f _velocity;
  sf::VertexArray _sprite;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
public:
  Player(void);
  sf::Vector2<sf::Vector2f> getCollisionBounds(void) const;
  sf::Vector2f getCenterPoint(void) const;
  sf::FloatRect getBounds(void) const;
  ~Player(void);
};

#endif //MINTAKA_PLAYER_HEAD_HPP

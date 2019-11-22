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
  Player();
  sf::FloatRect getGlobalBounds() const;
  sf::FloatRect getLocalBounds() const;
  ~Player();
};

#endif //MINTAKA_PLAYER_HEAD_HPP

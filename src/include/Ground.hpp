#ifndef MINTAKA_GROUND_HEAD_HPP
#define MINTAKA_GROUND_HEAD_HPP
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Ground final : public sf::Drawable
{
private:
  sf::VertexArray _sprite;
  sf::Transform _anchor;
public:
  static constexpr float unit_height = 50.0f;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
public:
  Ground(std::vector<std::size_t> const &);
  virtual ~Ground(void) override;
  float objRelHeight(sf::Vector2f const & pos) const;
};

#endif //MINTAKA_GROUND_HEAD_HPP

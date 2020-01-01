#ifndef MINTAKA_GROUND_HEAD_HPP
#define MINTAKA_GROUND_HEAD_HPP
#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "Collidable.hpp"

class Ground final : public sf::Drawable
{
private:
  sf::VertexArray _sprite;
  sf::Transform _anchor;
  std::vector<std::size_t> _heightMap;
public:
  static constexpr float unit_height = 50.0f;
private:
  virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
  void generate_sprite(void);
public:
  Ground(std::vector<std::size_t> const &);
  Ground(std::vector<std::size_t> &&);
  virtual ~Ground(void) override;
  bool is_hit(Collidable const &) const;
  static Ground generate_file(char const *);
};

#endif //MINTAKA_GROUND_HEAD_HPP

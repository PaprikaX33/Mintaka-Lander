#ifndef MINTAKA_GAME_WORLD_HEAD_HPP
#define MINTAKA_GAME_WORLD_HEAD_HPP
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

class GameWorld
{
private:
  enum class GameState {
                        RUNNING,
                        LOSE,
                        WIN
  };
  sf::RenderWindow _window;
  sf::View _port;
  sf::Clock _clock;
  sf::RectangleShape _player;
  sf::RectangleShape _background;
  sf::RectangleShape _ground;
  sf::Vector2f _velocity;
  sf::Font _textFont;
  sf::Text _fpsCounter;
  sf::Text _debugText;
  GameState _state;
private:
  GameWorld(GameWorld const &) = delete;
  GameWorld(GameWorld &&) = delete;
  GameWorld & operator=(GameWorld const &) = delete;
  GameWorld & operator=(GameWorld &&) = delete;

  void resize_viewport(void);
  void update(void);
  void draw(void);
public:
  GameWorld();
  int run();
};

#endif //MINTAKA_GAME_WORLD_HEAD_HPP

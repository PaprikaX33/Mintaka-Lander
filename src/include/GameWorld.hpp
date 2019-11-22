#ifndef MINTAKA_GAME_WORLD_HEAD_HPP
#define MINTAKA_GAME_WORLD_HEAD_HPP
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class GameWorld
{
private:
  enum class GameState {
                        RUNNING,
                        LOSE,
                        WIN,
                        PAUSED
  };
  sf::RenderWindow _window;
  sf::View _primary;
  sf::View _secondary;
  sf::Clock _clock;
  //sf::RectangleShape _player;
  Player _player;
  sf::RectangleShape _background;
  sf::RectangleShape _secondBackground;
  sf::RectangleShape _ground;
  sf::RectangleShape _pauseOverlay;
  sf::Vector2f _velocity;
  sf::Font _textFont;
  sf::Text _fpsCounter;
  sf::Text _debugText;
  sf::Text _pauseText;
  sf::Text _winText;
  sf::Text _loseText;
  GameState _state;
private:
  GameWorld(GameWorld const &) = delete;
  GameWorld(GameWorld &&) = delete;
  GameWorld & operator=(GameWorld const &) = delete;
  GameWorld & operator=(GameWorld &&) = delete;

  void center_obj(sf::Sprite &);
  void center_obj(sf::Text &);
  void center_obj(sf::Shape &);
  void resize_viewport(void);
  void update(void);
  void draw(void);

  void key_handle(void);
public:
  GameWorld(void);
  int run(void);
};

#endif //MINTAKA_GAME_WORLD_HEAD_HPP

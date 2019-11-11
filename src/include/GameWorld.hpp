#ifndef MINTAKA_GAME_WORLD_HEAD_HPP
#define MINTAKA_GAME_WORLD_HEAD_HPP
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class GameWorld
{
private:
  sf::RenderWindow _window;
  sf::View _port;
  sf::Clock _clock;
private:
  GameWorld(GameWorld const &) = delete;
  GameWorld(GameWorld &&) = delete;
  GameWorld & operator=(GameWorld const &) = delete;
  GameWorld & operator=(GameWorld &&) = delete;

public:
  GameWorld();
  int run();
};

#endif //MINTAKA_GAME_WORLD_HEAD_HPP

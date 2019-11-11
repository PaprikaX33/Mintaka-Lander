#include <sstream>
#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"


GameWorld::GameWorld():
  _window{sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close},
  _port{sf::FloatRect{0.0f, 0.0f, 800.0f, 800.0f}},
  _clock{},
  _player{sf::Vector2f{10.0f, 10.0f}}
{
  _window.setFramerateLimit(60);
  _player.setPosition(sf::Vector2f{100.0f,100.0f});
  _player.setFillColor(sf::Color::Black);
}

int GameWorld::run()
{
  sf::Text info;
  sf::Font font;
  sf::Color resetCol{51, 77, 77, 255};
  if(!font.loadFromFile("./font/TheFont.ttf")){
    std::cerr << "Unable to open font\n";
    return -1;
  }
  info.setFont(font);
  info.setCharacterSize(30);
  info.setFillColor(sf::Color::Red);
  info.setPosition(10,10);
  _clock.restart();
  while(_window.isOpen()){
    std::stringstream stream;
    stream << "FPS:\t" << std::round(1.0f / _clock.getElapsedTime().asSeconds()) <<'\n';
    _clock.restart();
    info.setString(stream.str());
    sf::Event winEvent;
    while(_window.pollEvent(winEvent)){
      switch(winEvent.type){
      case sf::Event::Closed:
        _window.close();
        break;
      case sf::Event::KeyReleased:{
        switch(winEvent.key.code){
        case sf::Keyboard::Q:
        case sf::Keyboard::Escape:
          _window.close();
          break;
        default:
          break;
        }
      }break;
      default:
        break;
      }
    }
    _window.setView(_port);
    _window.clear(resetCol);
    _window.draw(info);
    _window.draw(_player);
    _window.display();
  }
  return 1;//TODO
}

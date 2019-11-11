#include <sstream>
#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"


GameWorld::GameWorld():
  _window{sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close},
  _port{sf::FloatRect{0.0f, 0.0f, 800.0f, 800.0f}}
{
  _window.setFramerateLimit(60);
}

int GameWorld::run()
{
  sf::Text info;
  sf::Clock clock;
  sf::Font font;
  if(!font.loadFromFile("./font/UbuntuMono-B.ttf")){
    std::cerr << "Unable to open font\n";
    return -1;
  }
  while(_window.isOpen()){
    std::stringstream stream;
    stream << "FPS:\t" << std::round(1.0f / clock.getElapsedTime().asSeconds()) <<'\n';
    clock.restart();
    info.setString(stream.str());
    sf::Event winEvent;
    info.setFont(font);
    info.setCharacterSize(30);
    info.setFillColor(sf::Color::Red);
    info.setPosition(10,10);
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
    _window.clear(sf::Color::Black);
    _window.draw(info);
    _window.display();
  }
  return 1;//TODO
}

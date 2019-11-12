#include <sstream>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"

GameWorld::GameWorld():
  _window{sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close},
  _port{sf::FloatRect{0.0f, 0.0f, 1000.0f, 1000.0f}},
  _clock{},
  _player{sf::Vector2f{10.0f, 10.0f}},
  _background{sf::Vector2f{1000.0f, 1000.0f}},
  _velocity{0.0f,0.0f}
{
  _window.setFramerateLimit(60);
  _player.setPosition(sf::Vector2f{100.0f,100.0f});
  _player.setOutlineColor(sf::Color::Green);
  _player.setFillColor(sf::Color::Transparent);
  _player.setOutlineThickness(1.0f);
  _background.setPosition(sf::Vector2f{0.0f,0.0f});
  _background.setFillColor(sf::Color::Black);
  this->resize_viewport();
}

int GameWorld::run()
{
  sf::Text info;
  sf::Text debug;
  sf::Font font;
  if(!font.loadFromFile("./font/TheFont.ttf")){
    std::cerr << "Unable to open font\n";
    return -1;
  }
  info.setFont(font);
  info.setCharacterSize(30);
  info.setFillColor(sf::Color::Green);
  info.setPosition(10,10);
  debug.setFont(font);
  debug.setCharacterSize(30);
  debug.setFillColor(sf::Color::Green);
  debug.setPosition(_port.getSize().x - 350.0f, 10.0f);
  _clock.restart();
  while(_window.isOpen()){
    std::stringstream stream;
    stream << "FPS:\t" << std::round(1.0f / _clock.getElapsedTime().asSeconds()) <<'\n';
    _clock.restart();
    info.setString(stream.str());
    std::stringstream dbg;
    auto const loc = _player.getPosition();
    dbg.precision(3);
    dbg << "X:\t" << loc.x << '\t' << _velocity.x << '\n';
    dbg << "Y:\t" << loc.y << '\t' << _velocity.y << '\n';
    dbg << "Ort:\t" << _player.getRotation() << '\n';
    debug.setString(dbg.str());
    sf::Event winEvent;
    while(_window.pollEvent(winEvent)){
      switch(winEvent.type){
      case sf::Event::Closed:
        _window.close();
        break;
      case sf::Event::Resized:
        this->resize_viewport();
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
    this->update();
    this->draw();
    _window.draw(info);
    _window.draw(debug);
    _window.display();
  }
  return 0;
}

void GameWorld::resize_viewport(void)
{
  float const windowRatio = static_cast<float>(_window.getSize().x) / static_cast<float>(_window.getSize().y);
  float const viewRatio = static_cast<float>(_port.getSize().x) / static_cast<float>(_port.getSize().y);
  float sizeX = 1;
  float sizeY = 1;
  float posX = 0;
  float posY = 0;

  if(windowRatio < viewRatio){
    sizeY = windowRatio / viewRatio;
    posY = (1 - sizeY) / 2.f;
  }
  else {
    sizeX = viewRatio / windowRatio;
    posX = (1 - sizeX) / 2.f;
  }
  _port.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}


void GameWorld::update(void)
{

  if(_player.getPosition().y >= 1000.0f){
    _player.setPosition(_player.getPosition().x, 0.0f);
  }
  bool const apr = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ^ apr){
    if(apr){
      _player.rotate(-5.0f);
    }
    else {
      _player.rotate(5.0f);
    }
  }
  _velocity += sf::Vector2f{0.0f, 0.05f};
  float const angle = _player.getRotation();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
    sf::Vector2f boost{0.15f * std::cos((2 * static_cast<float>(M_PI) * (90 - angle)) / 360.0f),
                       (-1.0f) * 0.15f * std::sin((2 * static_cast<float>(M_PI) * (90 - angle)) / 360.0f)};
    _velocity += boost;
  }
  _player.move(_velocity);
}

void GameWorld::draw(void)
{
  sf::Color resetCol{51, 77, 77, 255};
  _window.setView(_port);
  _window.clear(resetCol);
  _window.draw(_background);
  //_window.draw(info);
  _window.draw(_player);
  //_window.display();
}

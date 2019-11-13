#include <sstream>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "FontDirectory.hpp"

GameWorld::GameWorld():
  _window{sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close},
  _port{sf::FloatRect{0.0f, 0.0f, 1000.0f, 1000.0f}},
  _clock{},
  _player{sf::Vector2f{10.0f, 10.0f}},
  _background{sf::Vector2f{1000.0f, 1000.0f}},
  _ground{sf::Vector2f{1000.0f, 50.0f}},
  _velocity{0.0f,0.0f},
  _textFont{},
  _fpsCounter{},
  _debugText{},
  _state{GameState::RUNNING}
{
  char const * const fontDir = "./font/TheFont.ttf";
  if(!_textFont.loadFromFile(fontDir)){
    throw Exc::FontDir{fontDir};
  }
  _window.setFramerateLimit(60);
  _player.setPosition(sf::Vector2f{100.0f,100.0f});
  _player.setOutlineColor(sf::Color::Green);
  _player.setFillColor(sf::Color::Transparent);
  _player.setOutlineThickness(1.0f);
  _player.setOrigin(_player.getSize().x * 0.5f, _player.getSize().y * 0.5f);
  _ground.setPosition(sf::Vector2f{0.0f,1000.0f - _ground.getSize().y});
  _ground.setOutlineColor(sf::Color::Green);
  _ground.setFillColor(sf::Color::Transparent);
  _ground.setOutlineThickness(1.0f);
  _background.setPosition(sf::Vector2f{0.0f,0.0f});
  _background.setFillColor(sf::Color::Black);
  this->resize_viewport();

  _fpsCounter.setFont(_textFont);
  _fpsCounter.setCharacterSize(30);
  _fpsCounter.setFillColor(sf::Color::Green);
  _fpsCounter.setPosition(10,10);
  _debugText.setFont(_textFont);
  _debugText.setCharacterSize(30);
  _debugText.setFillColor(sf::Color::Green);
  _debugText.setPosition(_port.getSize().x - 350.0f, 10.0f);
}

int GameWorld::run()
{
  _clock.restart();
  while(_window.isOpen()){
    this->key_handle();
    this->update();
    this->draw();
  }
  return 0;
}

void GameWorld::key_handle(void)
{
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
      case sf::Keyboard::P:
        switch(_state){
        case  GameState::PAUSED:
          _state = GameState::RUNNING;
          break;
        case GameState::RUNNING:
          _state = GameState::PAUSED;
          break;
        default:
            break;
        }
        break;
      case sf::Keyboard::R:
        _player.setPosition(sf::Vector2f{100.0f,100.0f});
        _player.setRotation(0.0f);
        _velocity = sf::Vector2f{0.0f, 0.0f};
        _state = GameState::RUNNING;
        break;
      default:
        break;
      }
    }break;
    default:
      break;
    }
  }
}

void GameWorld::resize_viewport(void)
{
  float const windowRatio = static_cast<float>(_window.getSize().x) / static_cast<float>(_window.getSize().y);
  float const viewRatio = static_cast<float>(_port.getSize().x) / static_cast<float>(_port.getSize().y);
  float sizeX = 1.0f;
  float sizeY = 1.0f;
  float posX = 0;
  float posY = 0;

  if(windowRatio < viewRatio){
    sizeY = windowRatio / viewRatio;
    posY = (1.0f - sizeY) / 2.f;
  }
  else {
    sizeX = viewRatio / windowRatio;
    posX = (1.0f - sizeX) / 2.f;
  }
  _port.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}


void GameWorld::update(void)
{
  if(_state == GameState::RUNNING){
    bool const rotateLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool const rotateRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    if(rotateLeft ^ rotateRight){
      if(rotateLeft){
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
    if(_player.getPosition().y >= (1000.0f - _ground.getSize().y) - (_player.getSize().y * 0.5f)){
      _player.setPosition(_player.getPosition().x, (1000.0f - _ground.getSize().y) - (_player.getSize().y * 0.5f));
      _velocity.y = 0.0f;
    }
  }

  std::stringstream stream;
  stream << "FPS:\t" << std::round(1.0f / _clock.getElapsedTime().asSeconds()) <<'\n';
  _clock.restart();
  _fpsCounter.setString(stream.str());
  std::stringstream dbg;
  auto const & loc = _player.getPosition();
  dbg.precision(3);
  dbg << "X:\t" << loc.x << '\t' << _velocity.x << '\n';
  dbg << "Y:\t" << loc.y << '\t' << _velocity.y << '\n';
  dbg << "Ort:\t" << _player.getRotation() << '\n';
  _debugText.setString(dbg.str());
}

void GameWorld::draw(void)
{
  sf::Color resetCol{51, 77, 77, 255};
  _window.setView(_port);
  _window.clear(resetCol);
  _window.draw(_background);
  _window.draw(_player);
  _window.draw(_ground);
  _window.draw(_fpsCounter);
  _window.draw(_debugText);
  _window.display();
}

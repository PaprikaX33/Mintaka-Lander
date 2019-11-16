#include <sstream>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "FontDirectory.hpp"
#include "Icon.hpp"

GameWorld::GameWorld():
  _window{sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close},
  _primary{sf::FloatRect{0.0f, 0.0f, 1000.0f, 1000.0f}},
  _secondary{sf::FloatRect{0.0, 0.0f, 1000.0f, 1000.0f}},
  _clock{},
  _player{sf::Vector2f{10.0f, 10.0f}},
  _background{sf::Vector2f{1000.0f, 1000.0f}},
  _ground{sf::Vector2f{1000.0f, 50.0f}},
  _pauseOverlay{sf::Vector2f{1000.0f, 1000.0f}},
  _velocity{0.0f,0.0f},
  _textFont{},
  _fpsCounter{},
  _debugText{},
  _pauseText{},
  _winText{},
  _loseText{},
  _state{GameState::RUNNING}
{
  char const * const fontDir = "./font/TheFont.ttf";
  if(!_textFont.loadFromFile(fontDir)){
    throw Exc::FontDir{fontDir};
  }
  _window.setFramerateLimit(60);
  _window.setIcon(icon::width(), icon::height(), icon::data());
  _player.setPosition(sf::Vector2f{500.0f,100.0f});
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

  _pauseOverlay.setPosition(sf::Vector2f{0.0f,0.0f});
  _pauseOverlay.setFillColor(sf::Color{0, 0, 0, 150});
  this->resize_viewport();

  _fpsCounter.setFont(_textFont);
  _fpsCounter.setCharacterSize(30);
  _fpsCounter.setFillColor(sf::Color::Green);
  _fpsCounter.setPosition(10,10);
  _debugText.setFont(_textFont);
  _debugText.setCharacterSize(30);
  _debugText.setFillColor(sf::Color::Green);
  _debugText.setPosition(_primary.getSize().x - 350.0f, 10.0f);

  _pauseText.setFont(_textFont);
  _pauseText.setCharacterSize(70);
  _pauseText.setString("--PAUSED--");
  _pauseText.setFillColor(sf::Color::Green);

  _winText.setFont(_textFont);
  _winText.setCharacterSize(70);
  _winText.setString("--YOU WIN--");
  _winText.setFillColor(sf::Color::Green);
  _loseText.setFont(_textFont);
  _loseText.setCharacterSize(70);
  _loseText.setString("--YOU LOSE--");
  _loseText.setFillColor(sf::Color::Green);
  //center text
  sf::FloatRect const pauseRect = _pauseText.getLocalBounds();
  _pauseText.setOrigin(pauseRect.left + pauseRect.width/2.0f,
                       pauseRect.top  + pauseRect.height/2.0f);
  _pauseText.setPosition(sf::Vector2f(1000.0f/2.0f,1000.0f/2.0f));

  sf::FloatRect const winRect = _winText.getLocalBounds();
  _winText.setOrigin(winRect.left + winRect.width/2.0f,
                       winRect.top  + winRect.height/2.0f);
  _winText.setPosition(sf::Vector2f(1000.0f/2.0f,1000.0f/2.0f));

  sf::FloatRect const loseRect = _loseText.getLocalBounds();
  _loseText.setOrigin(loseRect.left + loseRect.width/2.0f,
                     loseRect.top  + loseRect.height/2.0f);
  _loseText.setPosition(sf::Vector2f(1000.0f/2.0f,1000.0f/2.0f));
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

        //TODO REMOVE THIS DEBUG KEY
      case sf::Keyboard::W:
        _state = GameState::WIN;
        break;
      case sf::Keyboard::L:
        _state = GameState::LOSE;
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
        _player.setPosition(sf::Vector2f{500.0f,100.0f});
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
  float const viewRatio = static_cast<float>(_primary.getSize().x) / static_cast<float>(_primary.getSize().y);
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
  _primary.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
  //_primary.setViewport(sf::FloatRect(0.0f, 0.0f, sizeX, sizeY));
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
  sf::Color const resetCol{51, 77, 77, 255};
  _window.setView(_primary);
  _window.clear(resetCol);
  _window.draw(_background);
  _window.draw(_player);
  _window.draw(_ground);
  _window.draw(_fpsCounter);
  _window.draw(_debugText);
  switch(_state){
  case GameState::LOSE:
    _window.draw(_pauseOverlay);
    _window.draw(_loseText);
    break;
  case GameState::WIN:
    _window.draw(_pauseOverlay);
    _window.draw(_winText);
    break;
  case GameState::PAUSED:
    _window.draw(_pauseOverlay);
    _window.draw(_pauseText);
    break;
  default:
    break;
  }
  _window.display();
}

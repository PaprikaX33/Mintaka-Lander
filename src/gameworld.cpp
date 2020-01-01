#include <sstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "exception/FontDirectory.hpp"
#include "Icon.hpp"

constexpr char const * fontDir = "./font/unifont.ttf";

GameWorld::GameWorld():
  _window{},
  _primary{sf::FloatRect{0.0f, 0.0f, 1000.0f, 1000.0f}},
  _secondary{sf::FloatRect{0.0, 0.0f, (200.0f / 600.0f) * 1000.0f, 1000.0f}},
  _clock{},
  _player{},
  _ground{{1,3,1,5,1,3}},
  _background{sf::Vector2f{1000.0f, 1000.0f}},
  _secondBackground{sf::Vector2f{1000.0f, 1000.0f}},
  _pauseOverlay{sf::Vector2f{1000.0f, 1000.0f}},
  _textFont{},
  _fpsCounter{},
  _debugText{},
  _pauseText{},
  _winText{},
  _loseText{},
  _state{GameState::RUNNING}
{
  if(!_textFont.loadFromFile(fontDir)){
    throw Exc::FontDir{fontDir};
  }
  _window.create(sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
  _window.setFramerateLimit(60);
  _window.setIcon(icon::width(), icon::height(), icon::data());
  _background.setPosition(sf::Vector2f{0.0f,0.0f});
  _background.setFillColor(sf::Color::Black);
  _secondBackground.setPosition(sf::Vector2f{0.0f,0.0f});
  _secondBackground.setFillColor(sf::Color::Green);

  _pauseOverlay.setPosition(sf::Vector2f{0.0f,0.0f});
  _pauseOverlay.setFillColor(sf::Color{0, 0, 0, 150});
  this->resize_viewport();

  _fpsCounter.setFont(_textFont);
  _fpsCounter.setCharacterSize(30);
  _fpsCounter.setFillColor(sf::Color::Black);
  _fpsCounter.setString("--UNINITIALIZED--");
  _fpsCounter.setPosition(10,10);
  _debugText.setFont(_textFont);
  _debugText.setCharacterSize(30);
  _debugText.setString("--UNINITIALIZED--");
  _debugText.setFillColor(sf::Color::Black);
  sf::FloatRect const fpsRect = _fpsCounter.getGlobalBounds();
  _debugText.setPosition(fpsRect.left, fpsRect.top + fpsRect.height + 5.0f);

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
  this->center_obj(_pauseText);
  this->center_obj(_winText);
  this->center_obj(_loseText);
}

//TODO : Refactor this constructor. This constructor is an exact copy with the void constructor except the _ground
GameWorld::GameWorld(char const * grname):
  _window{},
  _primary{sf::FloatRect{0.0f, 0.0f, 1000.0f, 1000.0f}},
  _secondary{sf::FloatRect{0.0, 0.0f, (200.0f / 600.0f) * 1000.0f, 1000.0f}},
  _clock{},
  _player{},
  _ground{Ground::generate_file(grname)},
  _background{sf::Vector2f{1000.0f, 1000.0f}},
  _secondBackground{sf::Vector2f{1000.0f, 1000.0f}},
  _pauseOverlay{sf::Vector2f{1000.0f, 1000.0f}},
  _textFont{},
  _fpsCounter{},
  _debugText{},
  _pauseText{},
  _winText{},
  _loseText{},
  _state{GameState::RUNNING}
{
  if(!_textFont.loadFromFile(fontDir)){
    throw Exc::FontDir{fontDir};
  }
  _window.create(sf::VideoMode(800.0f, 600.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
  _window.setFramerateLimit(60);
  _window.setIcon(icon::width(), icon::height(), icon::data());
  _background.setPosition(sf::Vector2f{0.0f,0.0f});
  _background.setFillColor(sf::Color::Black);
  _secondBackground.setPosition(sf::Vector2f{0.0f,0.0f});
  _secondBackground.setFillColor(sf::Color::Green);

  _pauseOverlay.setPosition(sf::Vector2f{0.0f,0.0f});
  _pauseOverlay.setFillColor(sf::Color{0, 0, 0, 150});
  this->resize_viewport();

  _fpsCounter.setFont(_textFont);
  _fpsCounter.setCharacterSize(30);
  _fpsCounter.setFillColor(sf::Color::Black);
  _fpsCounter.setString("--UNINITIALIZED--");
  _fpsCounter.setPosition(10,10);
  _debugText.setFont(_textFont);
  _debugText.setCharacterSize(30);
  _debugText.setString("--UNINITIALIZED--");
  _debugText.setFillColor(sf::Color::Black);
  sf::FloatRect const fpsRect = _fpsCounter.getGlobalBounds();
  _debugText.setPosition(fpsRect.left, fpsRect.top + fpsRect.height + 5.0f);

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
  this->center_obj(_pauseText);
  this->center_obj(_winText);
  this->center_obj(_loseText);
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
        _player.reset();
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
  float constexpr viewRatio = 800.0f / 600.0f;
  float constexpr primRatio = 1.0f;
  float constexpr secnRatio = 200.0f / 600.0f;

  sf::FloatRect prim{0.0f, 0.0f, primRatio - secnRatio, 1.0f};
  sf::FloatRect secn{primRatio - secnRatio, 0.0f, secnRatio, 1.0f};

  if(windowRatio < viewRatio){
    //View is wider
    //Window is taller
    prim.height = windowRatio / viewRatio;
    prim.top = (1.0f - prim.height) / 2.0f;
    secn.height = windowRatio / viewRatio;
    secn.top = (1.0f - secn.height) / 2.0f;
  }
  else{
    //Window is wider
    //View is taller
    prim.width = (viewRatio / windowRatio) * (primRatio - secnRatio);
    prim.left  = (1.0f - (viewRatio / windowRatio)) / 2.0f;
    secn.width = (viewRatio / windowRatio) * secnRatio;
    secn.left  = prim.width + prim.left;
  }
  _primary.setViewport(prim);
  _secondary.setViewport(secn);
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
    _player.velocity_add(sf::Vector2f{0.0f, 0.05f});
    float const angle = _player.getRotation();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
      sf::Vector2f boost{0.15f * std::cos((2 * static_cast<float>(M_PI) * (90 - angle)) / 360.0f),
                         (-1.0f) * 0.15f * std::sin((2 * static_cast<float>(M_PI) * (90 - angle)) / 360.0f)};
      _player.velocity_add(boost);
    }
    _player.apply_movement(0.0f);
    if(_ground.is_hit(_player)){
      _state = GameState::LOSE;
    }
  }

  std::stringstream stream;
  stream << "FPS:\t" << std::round(1.0f / _clock.getElapsedTime().asSeconds()) <<'\n';
  _clock.restart();
  _fpsCounter.setString(stream.str());
  std::stringstream dbg;
  auto const & loc = _player.getPosition();
  auto const & velocity = _player.velocity();
  dbg.precision(3);
  dbg << "X:\t" << loc.x << '\t' << velocity.x << '\n';
  dbg << "Y:\t" << loc.y << '\t' << velocity.y << '\n';
  dbg << "Ort:\t" << _player.getRotation() << '\n';
  _debugText.setString(dbg.str());
}

void GameWorld::draw(void)
{
  sf::Color const resetCol{51, 77, 77, 255};
  _window.clear(resetCol);
  _window.setView(_secondary);
  _window.draw(_secondBackground);
  _window.draw(_fpsCounter);
  _window.draw(_debugText);
  _window.setView(_primary);
  _background.setFillColor(sf::Color::Black);
  _window.draw(_background);
  _window.draw(_player);
  _window.draw(_ground);
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

template<typename T>
void center_obj(T & inObj)
{
  sf::FloatRect const objRect = inObj.getLocalBounds();
  inObj.setOrigin(objRect.left + objRect.width/2.0f,
                  objRect.top  + objRect.height/2.0f);
  inObj.setPosition(sf::Vector2f(1000.0f/2.0f,1000.0f/2.0f));
}

void GameWorld::center_obj(sf::Sprite & inObj)
{
  return ::center_obj(inObj);
}
void GameWorld::center_obj(sf::Text & inObj)
{
  return ::center_obj(inObj);
}
void GameWorld::center_obj(sf::Shape & inObj)
{
  return ::center_obj(inObj);
}

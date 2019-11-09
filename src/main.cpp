#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char ** argv)
{
  for(int i = 1; i < argc; ++i){
    std::cout << argv[i] << ' ';
  }
  std::cout << '\n';
  sf::RenderWindow window{sf::VideoMode(800.0f, 800.0f), "Mintaka", sf::Style::Titlebar | sf::Style::Close};
  sf::View viewP{sf::FloatRect{0.0f, 0.0f, 800.0f, 800.0f}};
  sf::Text info;
  sf::Font font;
  if(!font.loadFromFile("./font/UbuntuMono-B.ttf")){
    std::cerr << "Unable to open font\n";
    return -1;
  }
  window.setFramerateLimit(60);
  info.setFont(font);
  info.setCharacterSize(30);
  info.setFillColor(sf::Color::Red);
  info.setPosition(10,10);

  while(window.isOpen()){
    std::stringstream stream;
    stream << "FPS:\t" << "10" <<'\n';
    info.setString(stream.str());
    sf::Event winEvent;
    while(window.pollEvent(winEvent)){
      switch(winEvent.type){
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyReleased:{
        switch(winEvent.key.code){
        case sf::Keyboard::Q:
        case sf::Keyboard::Escape:
          window.close();
          break;
        default:
          break;
        }
      }break;
      default:
        break;
      }
    }
    window.setView(viewP);
    window.clear(sf::Color::Black);
    window.draw(info);
    window.display();
  }
  return 0;
}

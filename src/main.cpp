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
  while(window.isOpen()){
    sf::Event winEvent;
    while(window.pollEvent(winEvent)){
      switch(winEvent.type){
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyReleased: {
        switch(winEvent.key.code){
        case sf::Keyboard::Q:
        case sf::Keyboard::Escape:
          window.close();
          break;
        default:
          break;
        }
      }
        break;
      default:
        break;
      }
    }
    window.setView(viewP);
    window.clear(sf::Color::Black);
    window.display();
  }
  return 0;
}

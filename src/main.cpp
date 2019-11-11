#include <sstream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameWorld.hpp"

int main(int argc, char ** argv)
{
  for(int i = 1; i < argc; ++i){
    std::cout << argv[i] << ' ';
  }
  std::cout << '\n';
  GameWorld game;
  return game.run();
}

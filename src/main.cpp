#include <sstream>
#include <cmath>
#include <exception>
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
  int retcode = -1;
  try{
    GameWorld game;
    retcode = game.run();
  }
  catch(std::exception &e){
    std::cerr << "Exception: " << e.what() << '\n';
    retcode = -1;
  }
  catch(...){
    std::cerr << "Unknown Exception\n";
    retcode = -1;
  }
  return retcode;
}

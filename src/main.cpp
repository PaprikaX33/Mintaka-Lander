#include <sstream>
#include <cmath>
#include <exception>
#include <memory>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "exception/BaseException.hpp"

int main(int argc, char ** argv)
{
  std::cout << '\n';
  int retcode = -1;
  try{
    std::unique_ptr<GameWorld> game;
    if(argc > 1){
      game = std::make_unique<GameWorld>(argv[1]);
    }
    else{
      game = std::make_unique<GameWorld>();
    }
    retcode = game->run();
  }
  catch(Exc::Base &e){
    std::cerr << "Exception: " << e.excID() << " : "<< e.what() << '\n';
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

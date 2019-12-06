#include <sstream>
#include <cmath>
#include <exception>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameWorld.hpp"
#include "BaseException.hpp"

int main(int argc, char ** argv)
{
  for(int i = 1; i < argc; ++i){
    std::cout << argv[i] << ' ';
  }
  std::cout << '\n';
  int retcode = -1;
  try{
    auto testing = Ground::generate_file("foo.txt");
    // GameWorld game;
    // retcode = game.run();
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

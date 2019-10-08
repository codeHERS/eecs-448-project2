/**
 *   @author CodeHERS
 *   @date
 *   @file main.cpp
 *   @brief calls game setup and run
 */
#include "Game.h"
#include <iostream>
#include <string>

int main ()
{
  Game game1;
  try
  {
    game1.setup();
    game1.run();

  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }
  return 0;
}

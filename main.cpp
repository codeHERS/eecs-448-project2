/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date 9/20/19
 *   @file main.cpp
 *   @brief calls game setup and run
 */
#include "Game.h"
#include <iostream>
#include <string>

int main ()
{
string playWith;
std::cout<<"\nDo you want to play with AI? (y/n)";
std::cin>>playWith;
  Game game1;
  try
  {
    if(playWith=="n")
    {
      game1.setup();
      game1.run();
    }

    else
    {
      game1.setup_for_AI();
    }

  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }
  return 0;
}

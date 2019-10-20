/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao) CodeHERS (Anjali Pare, Sindhu Shakamuri, Victoria Maldonado)
 *   @date 10/20/19
 *   @file main.cpp
 *   @brief calls game setup and run
 */
#include "Game.h"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

int main ()
{


string playWith;
string diffLevel;
ifstream welcome ("welcome.txt");
system("afplay Start_game.wav -t 3");
  Game game1;
do
{
  cout << game1.getFileContents (welcome) << endl;
  std::cout<<"\nDo you want to play with AI? (y/n): ";
  std::cin>>playWith;
}while(playWith!="y" && playWith!="n");

  try
  {
    if(playWith=="n")
    {
      game1.setup();
      game1.run(false,"0");
    }

    else
    {
      do {
        std::cout<<"\nChoose the difficulty level (1,2 or 3): ";
        std::cin>>diffLevel;
      }while(diffLevel!="1" && diffLevel!="2" && diffLevel!="3");

      game1.setup_for_AI();
      game1.run(true,diffLevel);

    }

  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }
  return 0;
}

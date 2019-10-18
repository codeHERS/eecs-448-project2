/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao)
 *   @date 9/20/19
 *   @file main.cpp
 *   @brief calls game setup and run
 */
#include "Game.h"
 //#include "sl.h"
//#include <Mmsystem.h>
//#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
//#pragma comment(lib, "Winmm.lib")
//#include <windows.h>
//#pragma comment(lib,"Winmm.lib")
#include <iostream>
#include <string>

int main ()
{


string playWith;
//mciSendString("play wav wait", NULL, 0, NULL);
//PlaySound("/Users/anjalipare/Documents/Decoding.wav", 0, 0);
//cout << "Hello world!\7\a\7" << endl;
/* create command to execute */
//afplay /Users/anjalipare/Documents/Decoding.wav
//system("afplay test.wav -t 2");
system("afplay Start_game.wav -t 3");
std::cout<<"\nDo you want to play with AI? (y/n)";
std::cin>>playWith;
  Game game1;
  try
  {
    if(playWith=="n")
    {
      game1.setup();
      game1.run(false);
    }

    else
    {
      game1.setup_for_AI();
      game1.run(true);

    }

  }
  catch(std::runtime_error& rte)
  {
      std::cout<<rte.what()<<std::endl;
  }
  return 0;
}

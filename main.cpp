/**
 *   @author CodeHERS
 *   @date
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
#include <iostream>
#include <fstream>

int main ()
{


string playWith;
string diffLevel;
ifstream welcome ("welcome.txt");
//mciSendString("play wav wait", NULL, 0, NULL);
//PlaySound("/Users/anjalipare/Documents/Decoding.wav", 0, 0);
//cout << "Hello world!\7\a\7" << endl;
/* create command to execute */
//afplay /Users/anjalipare/Documents/Decoding.wav
//system("afplay test.wav -t 2");
system("afplay Start_game.wav -t 3");
  Game game1;
do
{
  system("clear");
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
      /*while(!cin)
      {
        std::cout<<"\nChoose the difficulty level (1,2 or 3)";
        cin.clear();
        cin.ignore();
        std::cin>>diffLevel;
      }*/
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

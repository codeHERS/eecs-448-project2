/**
 *   @author Runtime Terrors (Abby Davidow, Anissa Khan, Grant Schnettgoecke, Jacob Swearingen, Chongzhi Gao) CodeHERS (Anjali Pare, Sindhu Shakamuri, Victoria Maldonado)
 *   @date 10/20/19
 *   @file Game.cpp
 *   @brief implemented methods needed for game play from header file
 */
#include "Game.h"
#include "Board.h"

#include <stdexcept>
#include <cctype> //included for isUpper function
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <time.h>
#include <stdio.h>
#include <unistd.h>


using namespace std;
using namespace std;
Game::Game() {
  m_numShips = 0;

  userRow = 0;
  userCol = "";

  arrCol = 0;
  arrRow = 0;


  stormWasUsedByP1=false;
  stormWasUsedByP2=false;

  m_p1oppBoard=new Board();
  m_p1ownBoard=new Board();
  m_p2oppBoard=new Board();
  m_p2ownBoard=new Board();


    m_currentPlayer=1;

    //string variables for text in console
    letsPlay = "\n  _          _         _____  _             _ \n | |        | |       |  __ \\| |           | |\n | |     ___| |_ ___  | |__) | | __ _ _   _| |\n | |    / _ \\ __/ __| |  ___/| |/ _` | | | | |\n | |___|  __/ |_\\__ \\ | |    | | (_| | |_| |_|\n |______\\___|\\__|___/ |_|    |_|\\__,_|\\__, (_)\n                                       __/ |  \n                                      |___/   \n";
    p1Text = "\n  _____  _                          ____             \n |  __ \\| |                        / __ \\            \n | |__) | | __ _ _   _  ___ _ __  | |  | |_ __   ___ \n |  ___/| |/ _` | | | |/ _ \\ '__| | |  | | '_ \\ / _ \\\n | |    | | (_| | |_| |  __/ |    | |__| | | | |  __/\n |_|    |_|\\__,_|\\__, |\\___|_|     \\____/|_| |_|\\___|\n                  __/ |                              \n                 |___/                               \n";
    p2Text = "\n  _____  _                         _______            \n |  __ \\| |                       |__   __|           \n | |__) | | __ _ _   _  ___ _ __     | |_      _____  \n |  ___/| |/ _` | | | |/ _ \\ '__|    | \\ \\ /\\ / / _ \\ \n | |    | | (_| | |_| |  __/ |       | |\\ V  V / (_) |\n |_|    |_|\\__,_|\\__, |\\___|_|       |_| \\_/\\_/ \\___/ \n                  __/ |                               \n                 |___/                                \n";
    AIText = "  ______  _ \n |  __  || |\n | |__| || |\n |  __  || |\n | |  | || |\n |_|  |_||_|\n";
    wait = "";
    placingShipsAItext = "Placing ships...\n";
}

Game::~Game()
{
    delete m_p2ownBoard;
    delete m_p2oppBoard;
    delete m_p1ownBoard;
    delete m_p1oppBoard;
    delete m_p1Ships;
    delete m_p2Ships;
}

int Game::convertCol(string col){
    char charCol=col.at(0);
    if(isupper(charCol))
    {
        return(int(charCol)-65);
    }
    else
    {
        return(int(charCol)-97);
    }
}

std::string Game::convertStringToLower(string wordToConvert)
{
    char charWordToConvert=wordToConvert.at(0);
    int wordLength =wordToConvert.length();
    for(int i=0; i<wordLength; i++)
    {
        charWordToConvert=wordToConvert.at(i);
        if(isupper(charWordToConvert))
        {
            charWordToConvert=(char)tolower(charWordToConvert);
        }
        wordToConvert.at(i)=charWordToConvert;
    }
    return(wordToConvert);
}

void Game::setup(){

    string numShipsString="";
    string userRowString="";
    Board* currentPlayerBoard=nullptr;
    printBattleship();

  //gets number of ships
  do{
      cout << "Enter the amount of ships both players want to use (Max: 5):  ";
      cin>>numShipsString;
      if(numShipsString!="1" && numShipsString!="2" && numShipsString!="3" && numShipsString!="4" && numShipsString!="5")
      {
          std::cout<<"Invalid number of ships. Must be 1 to 5. Try again.\n";
      }
  }while(numShipsString!="1" && numShipsString!="2" && numShipsString!="3" && numShipsString!="4" && numShipsString!="5");
    m_numShips=stoi(numShipsString);
    //test code
    //printPlayerBoards(m_p1ownBoard, m_p1oppBoard);
    //test code above

  //get number ships coordinates
    for(int j=1; j<3; j++)
    {
        if(j==1){
            printPlayerTurn(1);
        }else{
          if(playingAgainstAI==false){
            printPlayerTurn(2);
          }
        }

        switch (m_numShips) {
            case 1:

                cout << "Enter the coordinates for player "<<j<<"'s ship 1 (1x1): \n";

                do{
                    cout << "Row (1-8):  ";
                    cin>>userRowString;
                    if(userRowString!="1" && userRowString!="2" && userRowString!="3" && userRowString!="4" && userRowString!="5" && userRowString!="6" && userRowString!="7" && userRowString!="8")
                    {
                        std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
                    }
                }while(userRowString!="1" && userRowString!="2" && userRowString!="3" && userRowString!="4" && userRowString!="5" && userRowString!="6" && userRowString!="7" && userRowString!="8");
                userRow=stoi(userRowString);
                arrRow=userRow-1;

                do{
                    cout << "Col (A-H): ";
                    cin >> userCol;
                    arrCol = convertCol(userCol);
                    if(arrCol < 0 || arrCol > 7)
                    {
                        std::cout<<"Invalid column. Must be A to H. Try again.\n";
                    }
                }while(arrCol < 0 || arrCol > 7);

                userDirection="none";//set userDirection=none because ship of size 1 is only one point on the array

                if(m_currentPlayer==1){
                    if (isAvailable(m_p1ownBoard,arrRow, arrCol))
                    {
                    addShiptoArray("1", arrRow, arrCol, userDirection, 1);
                    std::cout<<"Player 1's current Board:\n";
                    printOwnBoard(m_p1ownBoard);
                    }
                }else{
                    if (isAvailable(m_p2ownBoard,arrRow, arrCol))
                    {
                    addShiptoArray("1", arrRow, arrCol, userDirection, 2);
                    std::cout<<"Player 2's current Board:\n";
                    printOwnBoard(m_p2ownBoard);
                    }
                }
                break;

            case 2:

                for(int i=1; i<3; i++)
                {
                    std::string shipString=to_string(i);
                    int shipNum=i;

                    shipPlacementInteraction(i, j, currentPlayerBoard);

                    if(m_currentPlayer==1)
                    {
                        if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
                            std::cout<<"Player 1's current Board:\n";
                            printOwnBoard(m_p1ownBoard);
                        }
                    }
                    else
                    {
                        if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
                            std::cout<<"Player 2's current Board:\n";
                            printOwnBoard(m_p2ownBoard);
                        }
                    }
                }
                break;

            case 3:

                for(int i=1; i<4; i++)
                {
                    std::string shipString=to_string(i);
                    int shipNum=i;

                    shipPlacementInteraction(i, j, currentPlayerBoard);

                    if(m_currentPlayer==1)
                    {
                        if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
                            std::cout<<"Player 1's current Board:\n";
                            printOwnBoard(m_p1ownBoard);
                        }
                    }
                    else
                    {
                        if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
                            std::cout<<"Player 2's current Board:\n";
                            printOwnBoard(m_p2ownBoard);
                        }
                    }
                }
                break;

            case 4:

                for(int i=1; i<5; i++)
                {
                    std::string shipString=to_string(i);
                    int shipNum=i;

                    shipPlacementInteraction(i, j, currentPlayerBoard);

                    if(m_currentPlayer==1)
                    {
                        if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
                            std::cout<<"Player 1's current Board:\n";
                            printOwnBoard(m_p1ownBoard);
                        }
                    }
                    else
                    {
                        if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
                            std::cout<<"Player 2's current Board:\n";
                            printOwnBoard(m_p2ownBoard);
                        }
                    }
                }
                break;

            case 5:

                for(int i=1; i<6; i++)
                {
                    std::string shipString=to_string(i);
                    int shipNum=i;

                    shipPlacementInteraction(i, j, currentPlayerBoard);

                    if(m_currentPlayer==1)
                    {
                        if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
                            std::cout<<"Player 1's current Board:\n";
                            printOwnBoard(m_p1ownBoard);
                        }
                    }
                    else
                    {
                        if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
                        {
                            addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
                            std::cout<<"Player 2's current Board:\n";
                            printOwnBoard(m_p2ownBoard);
                        }
                    }
                }
                break;
        }
       m_currentPlayer=2;//change value of current player to 2 for second round of for loop
    }
  }

void Game::run(bool check, string level){
    m_p1Ships = new Ships(m_numShips);
    m_p2Ships = new Ships(m_numShips);
    playingAgainstAI = check;
  //start game
  system("clear");

  cout << letsPlay << endl;
  cout << "Press any letter key then hit Enter to continue...";
  cin >> wait;

  //loop section
  bool endGame = true;

  while(endGame){

    //player 1 turn
    printPlayerTurn(1);
    p1Turn();

    //checks if player 1 has won
    if(m_p2Ships->allSunk()){
        printWinner(1);
        system("afplay End.wav -t 5");
        endGame = false;
        break;
    }

    //player 2 turn

    if(!check)
    {
      printPlayerTurn(2);
      p2Turn();
    }
    else
    {
      printPlayerTurn(3);
      if(level == "1")
        p2Turn_AI_easy();
      else if (level == "2")
        p2Turn_AI_medium();
      else
        p2Turn_AI_hard();
    }
    //checks if player 2 has won
    if(m_p1Ships->allSunk()){
        if(playingAgainstAI==true){
        printWinner(3);
        system("afplay AIWin.wav");

        }else{
        printWinner(2);
        system("afplay End.wav -t 5");
        }
        endGame = false;
        break;
    }
  }
}

//run() helper methods
void Game::p1Turn(){

  int p1_attack_row = 0;
  int p1_attack_col = 0;
  //string p1_attack_col_string;
  string wait = "";

  string shipNum_string;
    int shipNum;

  //print Board
  printPlayerBoards(m_p1ownBoard, m_p1oppBoard);

  cout << "It's time to attack!" << endl;
  //Storm addition
  string userUseStorm;

  //checks if storm has been used before
  if(stormWasUsedByP1==true)
  {
    cout << "You used the storm already, keep playing. \n";
    userUseStorm = "no";
  }else{
    do{
      cout << "Would you like to use the storm in this turn? (yes/no) \n";
      cin >> userUseStorm;
      //this checks for correct input
      if(userUseStorm!="yes" && userUseStorm!="no")
      {
        cout<<"This input is invalid, please enter yes or no \n";
      }
    }while(userUseStorm!="yes" && userUseStorm!="no");

      if(userUseStorm=="yes")
      {
        system("afplay Thunder.wav -t 3");
        stormAffectingP2();
        stormWasUsedByP1 = true;
        if(m_p2Ships->allSunk()){
            return;
        }
      }else
      {
        cout << "Okay, let's continue the game \n";
      }
  }
  if(userUseStorm=="no"){
    while(1){
         p1_attack_row = getUserRow();
         p1_attack_col = getUserCol();

     if(m_p1oppBoard->getEntryAtPosition(p1_attack_col, p1_attack_row) == "H" || m_p1oppBoard->getEntryAtPosition(p1_attack_col, p1_attack_row) == "M"){
         cout<< "You have already tried to attack there. Pick a different coordinate." << endl;
     }else{
         break;
     }
     }
   //gets good input from the user

   //checks if isHit() or not
   if(isHit(m_p2ownBoard, p1_attack_row, p1_attack_col)){
     system("afplay Hit.wav -t 3");
     cout << "That's a HIT!" << endl;
     m_p1oppBoard->setEntryAtPosition("H", p1_attack_col, p1_attack_row);

     //decreases the opponents ship on hit and announce if sunk
     shipNum_string = m_p2ownBoard->getEntryAtPosition(p1_attack_col, p1_attack_row);
     shipNum = stoi(shipNum_string);
     m_p2Ships->decreaseSize(shipNum);
     if(m_p2Ships->allSunk()){
           return;
     }

     //puts an x on the opponnets board
     m_p2ownBoard->setEntryAtPosition("X", p1_attack_col, p1_attack_row );
   }else{
     system("afplay Miss.wav -t 1");
     cout << "That's a MISS! Better luck next time." << endl;
     m_p1oppBoard->setEntryAtPosition("M", p1_attack_col, p1_attack_row);
   }

  }

  cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
  cin>> wait;
}

void Game::p2Turn(){

    int p2_attack_row = 0;
    int p2_attack_col = 0;
    //string p2_attack_col_string;
    string wait = "";

    string shipNum_string;
    int shipNum;

    //print Board
    printPlayerBoards(m_p2ownBoard, m_p2oppBoard);
    string userUseStorm;
    if(stormWasUsedByP2==true)
    {
      cout << "You used the storm already, keep playing. \n";
      userUseStorm="no";
    }else
    {
      do{
        cout << "Would you like to use the storm in this turn? (yes/no) \n";
        cin >> userUseStorm;
        //this checks for correct input
        if(userUseStorm!="yes" && userUseStorm!="no")
        {
          cout<<"This input is invalid, please enter yes or no \n";
        }
      }while(userUseStorm!="yes" && userUseStorm!="no");

      if(userUseStorm=="yes")
      {
        system("afplay Thunder.wav -t 3");
        stormAffectingP1();
        stormWasUsedByP2 = true;
        if(m_p1Ships->allSunk()){
            return;
        }
      }else
      {
        cout << "Okay, let's continue the game \n";
      }
    }
    if(userUseStorm=="no"){
    while(1){
        p2_attack_row = getUserRow();
        p2_attack_col = getUserCol();

        if(m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "H" || m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "M"){
            cout<< "You have already tried to attack there. Pick a different coordinate." << endl;
        }else{
            break;
        }

    }

    //hit or miss,
    if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)){
      system("afplay Hit.wav -t 3");
      cout << "That's a HIT!" << endl;
      m_p2oppBoard->setEntryAtPosition("H", p2_attack_col, p2_attack_row);

        //decreases the opponents ship on hit and announces if sunk
        shipNum_string = m_p1ownBoard->getEntryAtPosition(p2_attack_col, p2_attack_row);
        shipNum = stoi(shipNum_string);
        m_p1Ships->decreaseSize(shipNum);
        if(m_p1Ships->allSunk()){
            return;
        }
        //puts an x on the opponnets board
        m_p1ownBoard->setEntryAtPosition("X", p2_attack_col, p2_attack_row );
    }else{
      system("afplay Miss.wav -t 1");
      cout << "That's a MISS! Better luck next time." << endl;
      m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
    }
  }
    cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
    cin>> wait;
}

void Game::clearConsole(){
  //A load of end lines to clear the console screen inbetween player turns so they can't cheat
  for(int i = 0; i < 200; i ++){
    cout << endl;
  }
  system("clear");
}

void Game::printWinner(int player){

  ifstream file_p1_wins ("player1wins.txt");
  ifstream file_p2_wins ("player2wins.txt");
  ifstream file_ai_wins ("aiwins.txt");

  if(player == 1){
    cout << getFileContents (file_p1_wins) << endl;
    //system("afplay End.wav -t 5");
  }else if(player == 2){
    cout << getFileContents(file_p2_wins) << endl;
    //system("afplay End.wav -t 5");
  }else if(player == 3){
      cout << getFileContents(file_ai_wins) << endl;
  }
}

int Game::getUserRow(){
  string input;
  while(1){
    cout << "Enter Row(1-8): ";
    cin >> input;

    if(input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8"){
      return (stoi(input) - 1);
    }
  }
}

int Game::getUserCol(){
  string input;
  int input_num = 0;
  while(1){
    cout << "Enter Column(A-H): ";
    cin >> input;
    input_num = convertCol(input);
    if(input_num == 0 || input_num == 1 || input_num == 2 || input_num == 3 || input_num == 4 || input_num == 5 || input_num == 6 || input_num == 7){
      return input_num;
    }
  }
}

bool Game::isHit(Board* playerBoard, int row, int col){
    if(playerBoard->getEntryAtPosition(col, row) == " "){
        return false;
    }
    return true;
}

string Game::getFileContents (std::ifstream& File){
    std::string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
        while (File.good ())
        {
            std::string TempLine;                  //Temp line
            std::getline (File , TempLine);        //Get temp line
            TempLine += "\n";                      //Add newline character

            Lines += TempLine;                     //Add newline
        }
        return Lines;
    }
    else                           //Return error
    {
        return "ERROR File does not exist.";
    }
}

void Game::printPlayerBoards(Board* ownBoard, Board* oppBoard){

    cout<<"Opponent's Board:\n";
    oppBoard->printBoard();
  cout<<"-----------------------------------------------------\n";
    cout<<"Own Board:\n";
    ownBoard->printBoard();
}

void Game::printOwnBoard(Board* ownBoard)
{
    //cout<<"Own Board:\n";
    ownBoard->printBoard();
}

void Game::addShiptoArray(string ship, int row, int col, std::string direction, int player)
{
    if(direction=="none")//direction=none means placing m_ship1 on the board: 1x1 size
    {
        if(player==1){
            m_p1ownBoard->setEntryAtPosition(ship, col, row);
        }
        else{
            m_p2ownBoard->setEntryAtPosition(ship, col, row);
        }
    }
    else if(direction=="up")
    {
        if(ship=="2")
        {
            for(int i=0;i<2;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
                }
            }
        }
        else if(ship=="3")
        {
            for(int i=0;i<3;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
                }
            }
        }
        else if(ship=="4")
        {
            for(int i=0;i<4;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
                }
            }
        }
        else if(ship=="5")
        {
            for(int i=0;i<5;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row-i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row-i);
                }
            }
        }
    }
    else if(direction=="down")
    {
        if(ship=="2")
        {
            for(int i=0;i<2;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
                }
            }
        }
        else if(ship=="3")
        {
            for(int i=0;i<3;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
                }
            }
        }
        else if(ship=="4")
        {
            for(int i=0;i<4;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
                }
            }
        }
        else if(ship=="5")
        {
            for(int i=0;i<5;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col, row+i);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col, row+i);
                }
            }
        }
    }
    else if(direction=="left")
    {
        if(ship=="2")
        {
            for(int i=0;i<2;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
                }
            }
        }
        else if(ship=="3")
        {
            for(int i=0;i<3;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
                }
            }
        }
        else if(ship=="4")
        {
            for(int i=0;i<4;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
                }
            }
        }
        else if(ship=="5")
        {
            for(int i=0;i<5;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col-i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col-i, row);
                }
            }
        }
    }
    else//happens if direction is "right"
    {
        if(ship=="2")
        {
            for(int i=0;i<2;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
                }
            }
        }
        else if(ship=="3")
        {
            for(int i=0;i<3;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
                }
            }
        }
        else if(ship=="4")
        {
            for(int i=0;i<4;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
                }
            }
        }
        else if(ship=="5")
        {
            for(int i=0;i<5;i++){
                if(player==1){
                    m_p1ownBoard->setEntryAtPosition(ship, col+i, row);
                } else {
                    m_p2ownBoard->setEntryAtPosition(ship, col+i, row);
                }
            }
        }
    }
}

bool Game::isAvailable(Board* board, int row, int col)
{
      if(board->getEntryAtPosition(col,row) == " ")
      {
        return true;
      }
      else
      {
        return false;
      }
}

bool Game::checkUpDownLeftRight(Board* board, int row, int col, int shipNum, string direction)
{
	bool alwaysFits = true;
        if(direction=="none")
        {
            alwaysFits=true;
        }
		else if(direction == "up") {
			if(row-(shipNum-1) >= 0) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row-i, col) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}else if(direction == "down") {
			if(row+(shipNum-1) <= 7) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row+i, col) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}else if(direction == "left") {
			if(col-(shipNum-1) >= 0) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row, col-i) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}else if(direction == "right") {
			if(col+(shipNum-1) <= 7) {
				for(int i = 0; i < shipNum; i++) {
					if(isAvailable(board, row, col+i) == false)
						alwaysFits = false;
					}
				}
			else{
				alwaysFits = false;
			}
		}

		return(alwaysFits);
}

void Game::printBattleship(){
  cout<<"\n*********        *******    ************  ************  **            ***********      *********    **          **  ***********   ********\n";
  cout<<"**       **    **       **       **            **       **            **             **             **          **       **       **      ** \n";
  cout<<"**        **  **         **      **            **       **            **            **              **          **       **       **       ** \n";
  cout<<"**        **  **         **      **            **       **            **            **              **          **       **       **       ** \n";
  cout<<"**       **   **         **      **            **       **            **             **             **          **       **       **      ** \n";
  cout<<"*********     *************      **            **       **            *****           *********     **************       **       ********\n";
  cout<<"**       **   **         **      **            **       **            **                       **   **          **       **       ** \n";
  cout<<"**        **  **         **      **            **       **            **                        **  **          **       **       ** \n";
  cout<<"**        **  **         **      **            **       **            **                        **  **          **       **       ** \n";
  cout<<"**       **   **         **      **            **       **            **                       **   **          **       **       ** \n";
  cout<<"*********     **         **      **            **       ***********   ***********     *********     **          **  ***********   ** \n\n\n";
}

void Game::printCoordinateInteraction(Board* currentPlayerBoard, int shipNum){
    string userRowString="";
    bool keepAsking = false;
    do{
        keepAsking = false;
        do{
            cout << "Row (1-8):  ";
            cin>>userRowString;
            if(userRowString!="1" && userRowString!="2" && userRowString!="3" && userRowString!="4" && userRowString!="5" && userRowString!="6" && userRowString!="7" && userRowString!="8")
            {
                std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
            }
        }while(userRowString!="1" && userRowString!="2" && userRowString!="3" && userRowString!="4" && userRowString!="5" && userRowString!="6" && userRowString!="7" && userRowString!="8");
        userRow=stoi(userRowString);
        arrRow=userRow-1;

        do{
            cout << "Col (A-H): ";
            cin >> userCol;
            arrCol = convertCol(userCol);
            if(arrCol < 0 || arrCol > 7)
            {
                std::cout<<"Invalid column. Must be A to H. Try again.\n";
            }
        }while(arrCol < 0 || arrCol > 7);

        if(!isAvailable(currentPlayerBoard, arrRow, arrCol)){
            cout<< "This coordinate has already been taken. Enter new coordinates:\n";
            keepAsking = true;
        }
        if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "up")==false && checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "down")==false && checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "left")==false &&
           checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "right")==false && keepAsking != true)
        {
            cout<< "Ship cannot be placed here because it will not fit on the board due to other ships.\n";
            keepAsking = true;
        }

    }while(keepAsking == true);
}

void Game::shipPlacementInteraction(int i, int j, Board* currentPlayerBoard){
    int shipNum=i;

        if(m_currentPlayer==1)
        {
            currentPlayerBoard=m_p1ownBoard;
        }
        else
        {
            currentPlayerBoard=m_p2ownBoard;
        }

        cout<<"Enter the coordinates for player "<<j<<"'s ship "<<i<<" (1x"<<i<<")\n";

        printCoordinateInteraction(currentPlayerBoard, shipNum);

        if(i>1)
        {
            std::cout<<"Given your coordinates, your ship can be placed in the following directions:";
            if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "up")){ std::cout<<" up ";}
            if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "down")){ std::cout<<" down ";}
            if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "left")){ std::cout<<" left ";}
            if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "right")){ std::cout<<" right ";}

            do
            {
                std::cout<<"\nIn which direction do you want the ship to be placed (up/down/left/right):";
                std::cin>>userDirection;
                userDirection=convertStringToLower(userDirection);
                if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)==false)
                {
                    std::cout<<"The direction you chose is not open.\n";
                }
            }while((userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right") || (checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)==false));
        }else if(i<2)
        {
            userDirection="none";
        }
}

void Game::printPlayerTurn(int player){
    clearConsole();

    if(player==1){
        cout << p1Text << endl;
    } else if(player==2){
        cout << p2Text << endl;
    }else{
      cout << AIText <<endl;

    }
    cout << "Press any letter key then hit Enter to continue...";
    cin >> wait;
}

void Game::setup_for_AI()
{
	string numShipsString="";
	string userRowString="";
	Board* currentPlayerBoard=nullptr;
	string arr_direction[4] = {"up","down","left","right"};
	printBattleship();

//gets number of ships
do{
		cout << "Enter the amount of ships both players want to use (Max: 5):  ";
		cin>>numShipsString;
		if(numShipsString!="1" && numShipsString!="2" && numShipsString!="3" && numShipsString!="4" && numShipsString!="5")
		{
				std::cout<<"Invalid number of ships. Must be 1 to 5. Try again.\n";
		}
}while(numShipsString!="1" && numShipsString!="2" && numShipsString!="3" && numShipsString!="4" && numShipsString!="5");
	m_numShips=stoi(numShipsString);

	for(int j=1; j<3; j++)
	{
	    if(j==1){
	        printPlayerTurn(1);
	    }else{
        clearConsole();
        cout<<AIText<<endl;
        //Placing ships text loop
        int lengthText = placingShipsAItext.length();
        for(int i=0;i<lengthText;i++){
        cout<<placingShipsAItext[i];
        fflush(stdout);
        sleep(0);
      }
        cout<<endl;
        cout << "Press any letter key then hit Enter to continue...";
        cin >> wait;
	    }
	    if(m_currentPlayer==1)
	    {
	    switch (m_numShips) {
	        case 1:

	            cout << "Enter the coordinates for player "<<j<<"'s ship 1 (1x1): \n";

	            do{
	                cout << "Row (1-8):  ";
	                cin>>userRowString;
	                if(userRowString!="1" && userRowString!="2" && userRowString!="3" && userRowString!="4" && userRowString!="5" && userRowString!="6" && userRowString!="7" && userRowString!="8")
	                {
	                    std::cout<<"Invalid row. Must be 1 to 8. Try again.\n";
	                }
	            }while(userRowString!="1" && userRowString!="2" && userRowString!="3" && userRowString!="4" && userRowString!="5" && userRowString!="6" && userRowString!="7" && userRowString!="8");
	            userRow=stoi(userRowString);
	            arrRow=userRow-1;

	            do{
	                cout << "Col (A-H): ";
	                cin >> userCol;
	                arrCol = convertCol(userCol);
	                if(arrCol < 0 || arrCol > 7)
	                {
	                    std::cout<<"Invalid column. Must be A to H. Try again.\n";
	                }
	            }while(arrCol < 0 || arrCol > 7);

	            userDirection="none";//set userDirection=none because ship of size 1 is only one point on the array

	            if(m_currentPlayer==1){
	                if (isAvailable(m_p1ownBoard,arrRow, arrCol))
	                {
	                addShiptoArray("1", arrRow, arrCol, userDirection, 1);
	                std::cout<<"Player 1's current Board:\n";
	                printOwnBoard(m_p1ownBoard);
	                }

	            }/*else{
	                if (isAvailable(m_p2ownBoard,arrRow, arrCol))
	                {
	                addShiptoArray("1", arrRow, arrCol, userDirection, 2);
	                std::cout<<"Player 2's current Board:\n";
	                printOwnBoard(m_p2ownBoard);
	                }
	            }*/

	            break;

	        case 2:

	            for(int i=1; i<3; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

	                shipPlacementInteraction(i, j, currentPlayerBoard);

	                if(m_currentPlayer==1)
	                {
	                    if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
	                        std::cout<<"Player 1's current Board:\n";
	                        printOwnBoard(m_p1ownBoard);
	                    }
	                }

	            }
	            break;

	        case 3:

	            for(int i=1; i<4; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

	                shipPlacementInteraction(i, j, currentPlayerBoard);

	                if(m_currentPlayer==1)
	                {
	                    if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
	                        std::cout<<"Player 1's current Board:\n";
	                        printOwnBoard(m_p1ownBoard);
	                    }
	                }

	            }
	            break;

	        case 4:

	            for(int i=1; i<5; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

	                shipPlacementInteraction(i, j, currentPlayerBoard);

	                if(m_currentPlayer==1)
	                {
	                    if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
	                        std::cout<<"Player 1's current Board:\n";
	                        printOwnBoard(m_p1ownBoard);
	                    }
	                }


	            }
	            break;

	        case 5:

	            for(int i=1; i<6; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

	                shipPlacementInteraction(i, j, currentPlayerBoard);

	                if(m_currentPlayer==1)
	                {
	                    if (isAvailable(m_p1ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p1ownBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 1);
	                        std::cout<<"Player 1's current Board:\n";
	                        printOwnBoard(m_p1ownBoard);
	                    }
	                }

	            }
	            break;
	    }
      m_currentPlayer=2;
	  }
	  else

	  {
	    switch (m_numShips) {
	        case 1:
         // srand (time(NULL));
	        arrRow=rand()%8;
	        arrCol = rand()%8;
	            userDirection="none";//set userDirection=none because ship of size 1 is only one point on the array

	            if(m_currentPlayer==1){
	                if (isAvailable(m_p1ownBoard,arrRow, arrCol))
	                {
	                addShiptoArray("1", arrRow, arrCol, userDirection, 1);
	                std::cout<<"Player 1's current Board:\n";
	                printOwnBoard(m_p1ownBoard);
	                }
	            }else{
	                if (isAvailable(m_p2ownBoard,arrRow, arrCol))
	                {
	                addShiptoArray("1", arrRow, arrCol, userDirection, 2);
	                //printOwnBoard(m_p2ownBoard);
	                }
	            }
	            break;

	        case 2:

	            for(int i=1; i<3; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

	                currentPlayerBoard = m_p2ownBoard;
                  printCoordinateInteraction_AI(currentPlayerBoard, i);
                  if(i==1)
                  {
                    userDirection="none";
                  }
                  else
                  {
                    do
  	                {
                      //  srand (time(NULL));
  	                    int index = rand()%4;
  	                    userDirection = arr_direction[index];
  	                }while((userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right") || (checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)==false));
                  }
	                    if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
	                    }
	            }
	            break;

	        case 3:

	            for(int i=1; i<4; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

									currentPlayerBoard = m_p2ownBoard;
                  printCoordinateInteraction_AI(currentPlayerBoard, i);
                  if(i==1)
                  {
                    userDirection="none";
                  }
                  else
                  {
                    do
  	                {
                      //  srand (time(NULL));
  	                    int index = rand()%4;
  	                    userDirection = arr_direction[index];
  	                }while((userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right") || (checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)==false));
                  }

	                    if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
	                    }
	            }
	            break;

	        case 4:

	            for(int i=1; i<5; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

									currentPlayerBoard = m_p2ownBoard;
                  printCoordinateInteraction_AI(currentPlayerBoard, i);
                  if(i==1)
                  {
                    userDirection="none";
                  }
                  else
                  {
                    do
  	                {
                      //  srand (time(NULL));
  	                    int index = rand()%4;
  	                    userDirection = arr_direction[index];
  	                }while((userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right") || (checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)==false));
                  }
	                    if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
	                    }

	            }
	            break;

	        case 5:

	            for(int i=1; i<6; i++)
	            {
	                std::string shipString=to_string(i);
	                int shipNum=i;

									currentPlayerBoard = m_p2ownBoard;
                  printCoordinateInteraction_AI(currentPlayerBoard, i);
                  if(i==1)
                  {
                    userDirection="none";
                  }
                  else
                  {
                    do
  	                {
                      //  srand (time(NULL));
  	                    int index = rand()%4;
  	                    userDirection = arr_direction[index];
  	                }while((userDirection!="up" && userDirection!="down" && userDirection!="left" && userDirection!="right") || (checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, userDirection)==false));
                  }
	                    if (isAvailable(m_p2ownBoard, arrRow, arrCol) && checkUpDownLeftRight(m_p2oppBoard, arrRow, arrCol, shipNum, userDirection))
	                    {
	                        addShiptoArray(shipString, arrRow, arrCol, userDirection, 2);
	                    }
	            }
	            break;
	    }
	    }
	  }
}

void Game::printCoordinateInteraction_AI(Board* currentPlayerBoard, int shipNum){
    string userRowString="";
    bool keepAsking = false;

    do{
        srand (time(NULL));
        keepAsking = false;
         arrRow=rand()%8;
        arrCol = rand()%8;

        if(!isAvailable(currentPlayerBoard, arrRow, arrCol)){
            keepAsking = true;
        }
        if(checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "up")==false && checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "down")==false && checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "left")==false &&
           checkUpDownLeftRight(currentPlayerBoard, arrRow, arrCol, shipNum, "right")==false && keepAsking != true)
        {
            keepAsking = true;
        }

    }while(keepAsking == true);
}

void Game::p2Turn_AI_easy(){

    int p2_attack_row = 0;
    int p2_attack_col = 0;
    int i = 0;
    int j = 0;
    string wait = "";
    srand (time(NULL));
    string shipNum_string;
    int shipNum;

    //print Board

    while(1){
      //srand (time(NULL));
        p2_attack_row =rand()%7;
        p2_attack_col = rand()%7;
      //std::cout<<"\nI'm YOOOO\n";
        if(m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "H" || m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "M"){
            //cout<< "You have already tried to attack there. Pick a different coordinate." << endl;
        }else{
            break;
        }

    }

    //hit or miss,
    if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)){
      //cout << "That's a HIT!" << endl;

      j=p2_attack_col;
      i=p2_attack_row;
      //std::cout<<j<<i;

      m_p2oppBoard->setEntryAtPosition("H", p2_attack_col, p2_attack_row);
      system("afplay Hit.wav -t 3");
      cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;

        //decreases the opponents ship on hit and announces if sunk
        shipNum_string = m_p1ownBoard->getEntryAtPosition(p2_attack_col, p2_attack_row);
        shipNum = stoi(shipNum_string);
        m_p1Ships->decreaseSize(shipNum);
        if(m_p1Ships->allSunk()){
            return;
        }

        //puts an x on the opponnets board
        m_p1ownBoard->setEntryAtPosition("X", p2_attack_col, p2_attack_row );
    }else{
      //cout << "That's a MISS! Better luck next time." << endl;
      j=p2_attack_col;
      i=p2_attack_row;
      //std::cout<<j<<i;

      m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
      system("afplay Miss.wav -t 1");
      cout << "AI missed your ship at "<< i+1 << char(65+j) << endl;


    }

    cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
    cin>> wait;
}

void Game::p2Turn_AI_medium(){
  int p2_attack_row = 0;
  int p2_attack_col = 0;
  int i = 0;
  int j = 0;
  //string p2_attack_col_string;

  string wait = "";

  string shipNum_string;
  int shipNum=0;
  //std::cout<<"yessssssss";
if(firstTurn==true)
{
  while(1){
    //srand (time(NULL));
      p2_attack_row =rand()%8;
      p2_attack_col = rand()%8;
      //p2_attack_row = SRow;
      //p2_attack_col = SCol;
      checkCol = p2_attack_col;
      checkRow= p2_attack_row;
    //std::cout<<"\nI'm YOOOO\n";
      if(m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "H" || m_p2oppBoard->getEntryAtPosition(p2_attack_col, p2_attack_row) == "M"){
          //cout<< "You have already tried to attack there. Pick a different coordinate." << endl;
      }else{
          break;
      }

  }

  //hit or miss,
  if(isHit(m_p1ownBoard, p2_attack_row, p2_attack_col)){

    checkCol = p2_attack_col;
    checkRow = p2_attack_row;
    j=p2_attack_col;
    i=p2_attack_row;

    m_p2oppBoard->setEntryAtPosition("H", p2_attack_col, p2_attack_row);

    //cout << "That's a HIT!" << endl;
    system("afplay Hit.wav -t 3");
    cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;
    shipNum_string = m_p1ownBoard->getEntryAtPosition(checkCol, checkRow);
    shipNum = stoi(shipNum_string);
    if(shipNum==1)
    {
      m_p1ownBoard->setEntryAtPosition("X", checkCol, checkRow );
      m_p1Ships->decreaseSize(shipNum);
          if(m_p1Ships->allSunk()){
              return;
          }
          cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
          cin>> wait;
          return;
    }
    length=shipNum;
    length--;
    m_p1Ships->decreaseSize(shipNum);
        if(m_p1Ships->allSunk()){
            return;
        }

        shipNum_string_test = m_p1ownBoard->getEntryAtPosition(checkCol, checkRow);
        m_p1ownBoard->setEntryAtPosition("X", checkCol, checkRow );
        SRow = checkRow;
        SCol = checkCol;
    //medium->setEntryAtPosition("X", p2_attack_col, p2_attack_row );
    //checkRow = p2_attack_row;
    //checkCol = p2_attack_col;
    //shipNum_string = m_p2ownBoard->getEntryAtPosition(row, col);
    firstTurn = false;
    cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
    cin>> wait;
  }
  else{
    j = p2_attack_col;
    i = p2_attack_row;
    m_p2oppBoard->setEntryAtPosition("M", p2_attack_col, p2_attack_row);
    //cout << "That's a MISS! Better luck next time." << endl;
    system("afplay Miss.wav -t 1");
    cout << "AI missed your ship at "<< i+1 << char(65+j) << endl;
    cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
    cin>> wait;
  }
}

    //checks right
    else
    {
      //std::cout<<"\nYes I rock";
      while(!m_p1Ships->allSunk())
      {
        if((checkCol+1 < 8) && (m_p1ownBoard->getEntryAtPosition(checkCol+1, checkRow) == shipNum_string_test))//&&(medium->getEntryAtPosition(checkCol+1, checkRow)!="X"))
        {
          //std::cout<<"\nHitRi";
          checkCol++;
          j=checkCol;
          i=checkRow;
          //checkRight=true;
          //medium->setEntryAtPosition("X", checkCol, checkRow);
          m_p1ownBoard->setEntryAtPosition("X", checkCol, checkRow );
          m_p2oppBoard->setEntryAtPosition("H", checkCol, checkRow );
          system("afplay Hit.wav -t 3");
          cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;
          shipNum = stoi(shipNum_string_test);
          length--;
          m_p1Ships->decreaseSize(shipNum);
          if(m_p1Ships->allSunk()){
            return;
          }
          if(length==0)
          {
            //SRow = 7;//8
            //SCol = 0;//a
            firstTurn=true;
            cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
            cin>> wait;
            //std::cout<<"this is what is first turn:"<<firstTurn;
            return;
          }
          cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
          cin>> wait;
          return;

        }
        else if((checkRow+1 < 8) && (m_p1ownBoard->getEntryAtPosition(checkCol, checkRow+1) == shipNum_string_test))//&&(medium->getEntryAtPosition( checkCol, checkRow+1)!="X" ))
        {
          //std::cout<<"\nHitDo";
          checkRow++;
          j=checkCol;
          i=checkRow;
          //medium->setEntryAtPosition("X", checkCol, checkRow);
          m_p1ownBoard->setEntryAtPosition("X", checkCol, checkRow );
          m_p2oppBoard->setEntryAtPosition("H", checkCol, checkRow );
          system("afplay Hit.wav -t 3");
          cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;
          shipNum = stoi(shipNum_string_test);
          length--;
          m_p1Ships->decreaseSize(shipNum);
          if(m_p1Ships->allSunk()){
            return;
          }
          if(length==0)
          {
            //SRow = 7;
            //SCol = 0;
            firstTurn=true;
            cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
            cin>> wait;
            //std::cout<<"this is what is first turn:"<<firstTurn;
            return;
          }
          cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
          cin>> wait;
          return;
        }

        else if((checkRow-1 > -1) && (m_p1ownBoard->getEntryAtPosition(checkCol, checkRow-1) == shipNum_string_test))//&&(medium->getEntryAtPosition(checkCol, checkRow-1)!="X" ))
        {
          //std::cout<<"\nHitUP";
          checkRow--;
          j=checkCol;
          i=checkRow;
          //medium->setEntryAtPosition("X", checkCol, checkRow);

          m_p2oppBoard->setEntryAtPosition("H", checkCol, checkRow );
          m_p1ownBoard->setEntryAtPosition("X", checkCol, checkRow );
          //std::cout<<"\nHitLe";
          system("afplay Hit.wav -t 3");
          cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;
          shipNum = stoi(shipNum_string_test);
          length--;
          m_p1Ships->decreaseSize(shipNum);
          if(m_p1Ships->allSunk()){
            return;
          }
          if(length==0)
          {
            //SRow = 7;
            //SCol = 0;
            cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
            cin>> wait;
            firstTurn=true;
            //std::cout<<"this is what is first turn:"<<firstTurn;
            return;
          }
          //m_p1Ships->decreaseSize(shipNum);
          /*if(m_p1Ships->allSunk()){
            SRow = 3;
            SCol = 5;
            firstTurn=true;
            std::cout<<"this is what is first turn:"<<firstTurn;
            return;
          }*/
          cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
          cin>> wait;
          return;

        }
        else if((checkCol-1 > -1) && (m_p1ownBoard->getEntryAtPosition(checkCol-1, checkRow) == shipNum_string_test))//&&(medium->getEntryAtPosition(checkCol, checkRow-1)!="X" ))
        {
          //std::cout<<"\nHitRi";
          checkCol--;
          j=checkCol;
          i=checkRow;
          m_p1ownBoard->setEntryAtPosition("X", checkCol, checkRow );
          m_p2oppBoard->setEntryAtPosition("H", checkCol, checkRow );
          //std::cout<<"\nHit";
          system("afplay Hit.wav -t 3");
          cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;
          shipNum = stoi(shipNum_string_test);
          length--;
          m_p1Ships->decreaseSize(shipNum);
          if(m_p1Ships->allSunk()){
            return;
          }
          if(length==0)
          {
            //SRow = 7;
            //SCol = 0;
            cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
            cin>> wait;
            firstTurn=true;
            //std::cout<<"this is what is first turn:"<<firstTurn;
            return;
          }
          cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
          cin>> wait;
          return;

        }
        else
        {
          if(length!=0)
          {
            checkRow = SRow;
            checkCol = SCol;
          }//std::cout<<"\nYooooooo";
        }
      }
      firstTurn=true;
      return;
    }
  }




void Game::p2Turn_AI_hard(){
  string wait = "";
  string shipNum_string;
  int shipNum;
  int i = 0;
  int j = 0;

  bool shipIsHit = false;

      for(int col = 0; col < 8; col++)
      {
        for(int row = 0; row < 8; row++)
        {
            //shipIsHit=false;
            if(shipIsHit == false)
            {
              //checks for an spot to hit on p1 board
              if(!(m_p1ownBoard->getEntryAtPosition(col, row) == " ") && (m_p2oppBoard->getEntryAtPosition(col, row) != "H"))
              {
                    i = row;
                    j= col;
                    cout << "That's a HIT!" << endl;

                    m_p2oppBoard->setEntryAtPosition("H",col, row);

                    //prints board

                    //decreases the opponents ship on hit and announces if sunk
                    system("afplay Hit.wav -t 3");
                    cout << "AI hit your ship at "<< i+1 << char(65+j) << endl;
                    shipNum_string = m_p1ownBoard->getEntryAtPosition(col, row);
                    if(shipNum_string == " ")
                    {

                    }
                    else
                    {
                      shipNum = stoi(shipNum_string);
                      m_p1Ships->decreaseSize(shipNum);
                      m_p1ownBoard->setEntryAtPosition("X", col, row );
                      shipIsHit = true;
                    }
                    if(shipIsHit==true)
                    {
                      goto theEnd;
                    }
              }
            }
        }

      }
      theEnd:
      if(m_p1Ships->allSunk()){
          return;
      }

  cout << "Next Player's Turn. Press any letter key then hit Enter to continue...";
  cin>> wait;
}

void Game::stormAffectingP1(){
  int i = 0;
  int j = 0;
  string shipNum_string;
  int shipNum;
  int randShipNum = rand()%m_numShips+1;
  //makes sure ship number is not 0
  if(randShipNum==0){
    randShipNum++;
  }
  string randShipNumString = to_string(randShipNum);
  bool stormHit = false;
    for(int col = 0; col < 8; col++)
    {
      for(int row = 0; row < 8; row++)
      {
        if(stormHit==true){
          break;
        }
        if((m_p1ownBoard->getEntryAtPosition(row, col) == randShipNumString))
        {
          if(stormHit==true){
            break;
          }
          i = row;
          j = col;
          //lets the player know where the storm hit
          cout << "STORM attack hit the other player's ship at "<< j+1 << char(65+i) << endl;
          m_p2oppBoard->setEntryAtPosition("H",row, col);

          stormHit = true;

          shipNum_string = m_p1ownBoard->getEntryAtPosition(row, col);
          shipNum = stoi(shipNum_string);
          m_p1Ships->decreaseSize(shipNum);
          //puts an x on the opponnets board
          m_p1ownBoard->setEntryAtPosition("X", row, col);
        }
      }
      if(m_p2oppBoard->getEntryAtPosition(i, j) == "H"){
          break;
        }
    }
    if(m_p1Ships->allSunk()){
        return;
    }
}

void Game::stormAffectingP2(){
int i = 0;
int j = 0;
string shipNum_string;
int shipNum;
int randShipNum = rand()%m_numShips+1;
//makes sure shipnum is not 0
if(randShipNum==0){
  randShipNum++;
}
string randShipNumString = to_string(randShipNum);
bool stormHit = false;
  for(int col = 0; col < 8; col++)
  {
    if(stormHit==true){
      break;
    }
    for(int row = 0; row < 8; row++)
    {
      if(stormHit==true){
        break;
      }
      if((m_p2ownBoard->getEntryAtPosition(row, col) == randShipNumString))
      {
        i = row;
        j = col;
        //lets the player know where the storm hit
        cout << "STORM attack hit the other player's ship at "<< j+1 << char(65+i) << endl;
        stormHit = true;
        m_p1oppBoard->setEntryAtPosition("H",row, col);

        shipNum_string = m_p2ownBoard->getEntryAtPosition(row, col);
        shipNum = stoi(shipNum_string);
        m_p2Ships->decreaseSize(shipNum);
        //puts an x on the opponnets board
        m_p2ownBoard->setEntryAtPosition("X", row, col );
      }
    }
    if(m_p1oppBoard->getEntryAtPosition(i, j) == "H"){
        break;
      }
  }
  if(m_p2Ships->allSunk()){
      return;
  }
}

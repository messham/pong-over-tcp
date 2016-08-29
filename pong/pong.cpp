/*
   pong.cpp

   Simply pong.

   ------------------------------------------

   Copyright 2016 JM Messham

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <QApplication>
#include "src/window-sp.h"
#include "src/window-mp.h"
#include "src/tcp/client.h"
#include "src/tcp/server.h"

#include <iostream>
#include <thread>
using namespace std;

int main(int argc, char **argv)
{
  if (argc != 2 || (string(argv[1]) != "1" && string(argv[1]) != "2")) {
    printf("usage: %s <number of players>(default: 1 player)", argv[0]);
    exit(1);
  }

  QApplication app (argc, argv);
  Window* window;
  
  if (string(argv[1]) == "2") { // multiplayer
    try {
      window = new WindowMP();  
    }
    catch (exception &e){
      printf(e.what());
      return 0; // user decided not to start server
    } 
  }
  
  else if (string(argv[1]) == "1") { //singleplayer
    // set ai
    window = new WindowSP;
    
  }

  window->show();
  return app.exec();
  
}

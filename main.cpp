// Online C++ compiler to run C++ program online
// Matthew 5:27
#include "game.h"
#include "robot.h"
#include "user.h"

int main()
{
   // Initialization
   Game game;
   Robot ai;
   User usr;

   // User Credientials
   std::string usrn;
   std::string pssc;

   std::string response;

   // User Login
   std::cout << "Username: ";
   getline(std::cin, usrn);
   usr.set_username(usrn);
   std::cout << "Password: ";
   getline(std::cin, pssc);
   usr.set_password(pssc);


   // Game start
   std::cout << "********* This is the AI Program **********" << std::endl;

   // Game loop
   while (game.get_status())
   {
        ai.printGreeting();
        ai.set_turn(1);
        response = usr.send_request();
        std::cout << ai.evaluate_response(response) << std::endl;
        ai.set_turn(0);
   }

   // Game End
   std::cout << "********* Ending the AI Program **********" << std::endl;

   return 0;
}

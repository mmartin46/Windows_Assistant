// Matthew 5:27
#include "game.h"
#include "robot.h"
#include "user.h"

void login(User &usr, std::string &usrn, std::string &pssc);

int main()
{
   // Initialization
   Game *game = new (std::nothrow) Game;
   Robot ai;
   User *usr = new (std::nothrow) User;
   RootUser *root = NULL;

   // User Credientials
   std::string usrn;
   std::string pssc;

   std::string response;

   // User Login
   login(*usr, usrn, pssc);

   // Game start
   std::cout << "********* This is the AI Program **********" << std::endl;

   // Game loop
   while (game->get_status())
   {
        ai.printGreeting();
        ai.set_turn(1);
        response = usr->send_request();
        std::cout << ai.evaluate_response(response) << std::endl;


        if (ai.evaluate_response(response) == "Root Login")
        {
            std::cout << "**************************" << std::endl;
            login(*usr, usrn, pssc);
            delete usr;
            root = new RootUser;
            root->root_init(usrn, pssc);
        }


        ai.set_turn(0);
   }

   delete usr;
   delete root;
   delete game;

   // Game End
   std::cout << "********* Ending the AI Program **********" << std::endl;

   return 0;
}

void login(User &usr, std::string &usrn, std::string &pssc)
{
   std::cout << "Username: ";
   getline(std::cin, usrn);
   usr.set_username(usrn);
   std::cout << "Password: ";
   getline(std::cin, pssc);
   usr.set_password(pssc);
}

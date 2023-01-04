// Matthew 5:27
#include "game.h"
#include "robot.h"
#include "user.h"

// Allows the user to login
void login(User &usr, std::string &usrn, std::string &pssc);


int main()
{
   // Initialization
    Game *game = NULL;
    User *usr = NULL;

   try
   {
      game = new (std::nothrow) Game;
      usr = new (std::nothrow) User;
   }
   catch (std::bad_alloc& ex)
   {
      std::cerr << "Start Up Exception: Out of memory!\n";
      exit(1);
   }

   Robot ai;


   // User Credentials
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
            usr = new RootUser();
            static_cast<RootUser*>(usr)->root_init(usrn, pssc);
        }
        else if (ai.evaluate_response(response) == "Quitting the AI Program...")
        {
            game->set_status(0);
        }

        ai.set_turn(0);
   }

   delete usr;
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

   // TODO: Have info saved to a file
   /*
   std::ofstream file;
   file.open("credentials.txt");
   file << usr.get_username() << std::endl;
   file << usr.get_password() << std::endl;
   file.close();
   */
}

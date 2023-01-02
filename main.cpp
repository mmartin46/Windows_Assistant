// Online C++ compiler to run C++ program online
// Matthew 5:27
#include "game.h"
#include "robot.h"


class User
{
   private:
      uint8_t acc_init;
      std::pair<std::string, std::string> auth;
   public:
      virtual void set_username(const std::string &);
      virtual void set_password(const std::string &);
};

void User::set_username(const std::string &usr)
{
   std::string input;
   if (!acc_init)
   {
      auth.first = usr;
   }
   else
   {
      std::cout << "Type your current password\nPassword: ";
      getline(std::cin, input);
      if (input == auth.second)
      {
         auth.first = usr;         
      }
      else
      {
         std::cout << "Incorrect password.\n";
      }
   }
}

void User::set_password(const std::string &pass)
{
   std::string input;
   if (!acc_init)
   {
      auth.second = pass;
      acc_init = 1;
   }
   else
   {
      uint8_t wrong = 1;
      while (wrong)
      {
         std::cout << "Type your current password\nPassword: ";
         getline(std::cin, input);
         if (input == auth.second)
         {
            auth.second = pass;  
            wrong = 0;
            std::cout << "Correct password.\n";       
         }
         else
         {
            std::cout << "Incorrect password.\n";
         }
      }
   }
}

class RootUser : public User
{
   private:
      uint8_t acc_init;
      std::pair<std::string, std::string> auth;
   public: 
      void set_username(const std::string &);
      void set_password(const std::string &);
};

void RootUser::set_username(const std::string &usr)
{
   auth.first = usr;
}

void RootUser::set_password(const std::string &pass)
{
   auth.first = pass;
}

int main()
{ 
   Game game;
   Robot ai;
   User usr;

   std::string usrn;
   std::string pssc;

   std::string response;

   // User Credentials
   std::cout << "Username: ";
   getline(std::cin, usrn);
   usr.set_username(usrn);
   std::cout << "Password: ";
   getline(std::cin, pssc);
   usr.set_password(pssc);

   std::cout << "********* This is the AI Program **********" << std::endl;

   while (game.status())
   {
        ai.printGreeting();
        ai.set_turn(1);
        getline(std::cin, response);
        std::cout << ai.evaluate_response(response) << std::endl;
        ai.set_turn(0);
   }

   return 0;
}
// Matthew 5:27
#ifndef USER_H
#define USER_H
#include "libraries.cpp"

// Describes the users permissions
enum permissions {
   NOT_ROOT = 0,
   IS_ROOT = 1
};

/*
User
The user is responsible for sending requests to the robot
and changing their own credientials.

@set_username - Sets the username
@set_password - Sets the password
*/
class User
{
   protected:
      uint8_t acc_init;
      uint8_t turn;
      std::pair<std::string, std::string> auth;
      permissions usr_perm = NOT_ROOT;

   public:
      User() { acc_init = 0; turn = 0; }
      virtual ~User();


      User& operator=(const User&);

      virtual void set_username(const std::string &);
      virtual void set_password(const std::string &);
      std::string get_username() const;
      std::string get_password() const;
      uint8_t is_root() const;

      std::string send_request();
      void set_turn(uint8_t);
      uint8_t get_turn() const;
};

// Is the user a root user or not.
uint8_t User::is_root() const
{
   return usr_perm == IS_ROOT;
}

// Returns the username.
std::string User::get_username() const
{
   return auth.first;
}
// Returns the password
std::string User::get_password() const
{
   return auth.second;
}

// Copies the authorization of an account
// to another.
User& User::operator=(const User& rhs)
{
   if (this != &rhs)
   {
      this->acc_init = rhs.acc_init;
      this->turn = rhs.turn;
      this->auth = rhs.auth;
   }
   return *this;
}

// Send request
std::string User::send_request()
{
   std::string request;
   getline(std::cin, request);
   return request;
}

// Sets the username
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

// Sets the password
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

void User::set_turn(uint8_t t)
{
   turn = t;
}

uint8_t User::get_turn() const
{
   return turn;
}

User::~User()
{
   std::cout << "Logging out of account '" + auth.first + "'..." << std::endl;
}

#endif

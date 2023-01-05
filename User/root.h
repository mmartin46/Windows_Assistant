// John 3:5
#ifndef ROOT_H
#define ROOT_H
#include "user.h"

// Creates a root
// Has the same permissions as the user
// but can make further requests to the
// ai.
class RootUser : public User
{
   public:
      void root_init(const std::string&, const std::string &);
      void remove_root();
      ~RootUser();
};

// Intializes the permissions of the root user.
void RootUser::root_init(const std::string &usrn, const std::string &pssc)
{
   usr_perm = IS_ROOT;

   auth.first = usrn;
   auth.second = pssc;
   std::cout << "Root user initialized for '" + auth.first + "'" << std::endl;
   std::cout << "********** ROOT MODE ************" << std::endl;
}

// Removes root permissions from the user.
void RootUser::remove_root()
{
   usr_perm = NOT_ROOT;
}

RootUser::~RootUser()
{
   std::cout << "(ROOT) Logging out of account '" + auth.first + "'..." << std::endl;
}

#endif
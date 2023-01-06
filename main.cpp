// Matthew 5:27
#include "math.h"
#include "game.h"
#include "robot.h"
#include "User/root.h"

#define PRIME_CONST 31
#define DONT_EXECUTE 0
#define DO_EXECUTE 1


unsigned int str_hash(std::string str)
{
    int hC = 0;
	for (int i = 0; i < str.length(); ++i)
    {
        hC += static_cast<int>(str[i]) % 20;
    }
    return (hC << 1);
}

// Allows the user to login
void login(User &usr, std::string &usrn, std::string &pssc);

int main()
{
	// Initialization
	Game *game = NULL;
	User *usr = NULL;

	try
	{
		game = new(std::nothrow) Game;
		usr = new(std::nothrow) User;
	}
	catch (std::bad_alloc &ex)
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
	std::cout << "*********This is the AI Program **********" << std::endl;


	// Game loop
	while (game->get_status())
	{
		ai.printGreeting();
		ai.set_turn(1);

		response = usr->send_request();
		// DEBUG: Executes a request 2 times.
		switch(str_hash(ai.evaluate_response(response, *usr, DO_EXECUTE)))
		{
			case 194:
				ai.evaluate_response(response, *usr, DONT_EXECUTE);
				if (!usr->is_root())
				{
					std::cout << "**************************" << std::endl;
					login(*usr, usrn, pssc);
					usr = new RootUser();
					static_cast<RootUser*> (usr)->root_init(usrn, pssc);
				}
				else
				{
					std::cout << "You are already a root user." << std::endl;
				}
				break;
			case 468:
				ai.evaluate_response(response, *usr, DONT_EXECUTE);
				game->set_status(0);
				break;
			case 266:
				ai.evaluate_response(response, *usr, DONT_EXECUTE);
				usr->logout_call();
				static_cast<RootUser*> (usr)->remove_root();
				login(*usr, usrn, pssc);
				break;
			default:
			if (ai.evaluate_response(response, *usr, DO_EXECUTE) != "\n")
				std::cout << ai.evaluate_response(response, *usr, DONT_EXECUTE) << std::endl;
		}


		ai.set_turn(0);
	}

	delete usr;
	delete game;

	// Game End
	std::cout << "*********Ending the AI Program **********" << std::endl;

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

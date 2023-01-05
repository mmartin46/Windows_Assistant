// Proverbs 3:5
#ifndef ROBOT_H
#define ROBOT_H
#include "User/user.h"

class Robot
{
	private:
		// Variables
		uint8_t greet_sent;
	   uint8_t turn;
	   // Greetings
	   std::vector<std::string > greeting_responses = { "Hi", "Hey", "What's up?", "Hey there!", "Yo!", "Hi!" };

   	std::vector<std::string > quest_greet_responses = { "I'm a robot, how are you?", "Nothing much, what about you?", "I'm running, how about you?", "I'm running", "I'm a program." };

	   // General Responses
	   std::vector<std::string > positive_responses = { "Nice.", "Cool.", "Awesome!", "Great!", "Neat!" };

      // Compliment Responses
      std::vector<std::string > compliment_responses = { "Appreciate it!", "No problem!", "Thank you!", "Don't mention it.", "My duty!" };

	   // Settings
	   std::vector<std::string > settings = { "root", "quit", "logout" };

      std::vector<std::vector<std::string> > responses = { greeting_responses, quest_greet_responses, positive_responses, compliment_responses };


	public:
		Robot();
	   void set_turn(uint8_t);
	   uint8_t get_turn() const;
	   void printGreeting();
	   bool check_greeting() const;


		// Responses
	   void root_response(const std::string &, std::string &, const User &);
		void generate_all(const std::vector<std::vector<std::string> > &, const std::vector<std::vector<std::string> > &, std::string &, std::string, int);
	   void generate(const std::vector<std::string > &, const std::vector<std::string > &, std::string &, std::string, int);

	   void terminal_response(const std::string &, std::string &);
	   void setting_response(std::string &, std::string &);

	   std::string evaluate_response(const std::string &, const User &);
};

// Responses only accessable by the root.
void Robot::root_response(const std::string &resp, std::string &result, const User &usr)
{
	if (usr.is_root())
	{
		std::unordered_map<std::string, std::string > root_resp = {
		   { 	"drivers", "driverquery" },
			{ 	"system", "systeminfo" },
			{ 	"account", "wmic useraccount" },
         {  "mac", "getmac" }
		};

		// Checks if the maps contain a key which is
		// also contained in the response.
		for (auto it: root_resp)
		{
			if (resp.find(it.first) != std::string::npos)
			{
				std::system(it.second.c_str());
				result = "Process executed = '" + static_cast<std::string > (it.second) + "'";
				break;
			}
		}
	}
}

// Checks if the user has requested to configure
// any user settings.
void Robot::setting_response(std::string &result, std::string &copy)
{
	std::string usrnme;
	std::string passwd;
	for (auto it: settings)
	{
		if (copy.find(it) != std::string::npos)
		{
			if (it == "root")
			{
				result = "Root Login";
			}

			if (it == "quit")
			{
				result = "Quitting the AI Program...";
			}

			if (it == "logout")
			{
				result = "Logging Out...";
			}
		}
	}
}

// Sets the robot's turn to respond on or off.
// 0 - Not the robot's turn
// 1 - The robot's turn
void Robot::set_turn(uint8_t num)
{
	turn = num;
}

// Checks if it is the robot's current turn.
// 0 - Not the robot's turn
// 1 - The robot's turn
uint8_t Robot::get_turn() const
{
	return turn;
}

// Generates a general response to
// a general answer.
// ans - A vector of strings that holds the possible user's requests.
// res - A vector of strings that holds the possible bot responses.
void Robot::generate(const std::vector<std::string > &ans, const std::vector<std::string > &resp, std::string &result, std::string copy, int rand_idx)
{
	std::vector<std::string>::const_iterator start, end = ans.end();
	// If the result is a greeting.
	for (start = ans.begin(); start < end; ++start)
	{
		if (copy.find(*start) != std::string::npos)
		{
			result = resp[rand_idx];
		}
	}
}

// Uses the generate() function on each vector of responses and answers.
// ans - A matrix of strings that holds the possible user's requests.
// res - A matrix of strings that holds the possible bot responses.
void Robot::generate_all(const std::vector<std::vector<std::string> > &ans, const std::vector<std::vector<std::string> > &resp, std::string &result, std::string copy, int rand_idx)
{
	std::vector<std::vector<std::string> >::const_iterator ans_start, ans_end = ans.end();
	std::vector<std::vector<std::string> >::const_iterator resp_start, resp_end = resp.end();

	for ( ans_start = ans.begin(), resp_start = resp.begin(); ans_start < ans_end; ++ans_start, ++resp_start )
	{
		generate(*resp_start, *resp_end, result, copy, rand_idx);
	}

}


// If the user wants to use commands using
// the terminal command prompt the
// terminal_response() function will be called.
void Robot::terminal_response(const std::string &response, std::string &result)
{
	// Application Management
	std::unordered_map< std::string, const char*> application_map = {
		{ 	"chrome", "start chrome" },
			{ 	"edge", "start msedge" },
			{ 	"task", "taskmgr" },
			{ 	"explore", "explorer" },
			{ 	"calculator", "calc" },
			{ 	"calendar", "cal" },
			{ 	"date", "cal" },
			{ 	"green", "color 2" }
		};

	// File Management
	std::unordered_map< std::string, const char*> file_map = {
		{ 	"files", "ls -l" },
			{ 	"where", "pwd" },
			{ 	"text", "find . -type f -name '*.txt'" },
			{ 	"cpp", "find . -type f -name '*.cpp'" },
			{ 	"processes", "ps" },
			{ 	"environment", "printenv" },
		};

	// Checks if the maps contain a key which is
	// also contained in the response.
	for (auto it: application_map)
	{
		if (response.find(it.first) != std::string::npos)
		{
			std::system(it.second);
			result = "Process executed = '" + static_cast<std::string > (it.second) + "'";
			break;
		}
	}

	for (auto it: file_map)
	{
		if (response.find(it.first) != std::string::npos)
		{
			std::system(it.second);
			result = "Process executed = '" + static_cast<std::string > (it.second) + "'";
			break;
		}
	}
}

// Evaluates the user's response and returns
// a string based off what the user requested.
std::string Robot::evaluate_response(const std::string &response, const User &usr)
{
	if (this->get_turn())
	{
		// Generating a Random Number
		int rand_idx;
		srand(time(NULL));

		// General Greetings
		std::vector<std::string > greeting_answer = { "hey", "hi", "hii", "hello", "heyy", "heythere" };

		std::vector<std::string > greet_resp_answer = { "howareyou", "howhaveyoubeen", "whatsnew", "whatsup", "whatsgoingon", "howsitgoing" };

		std::vector<std::string > positive_answer = { "alright", "fine", "good", "yeah", "great", "yes" };

      std::vector<std::string > compliment_answer = { "thankyou", "thanks", "thank", "awesome", "useful" };

		std::vector<std::vector<std::string > > answers = { greeting_answer, greet_resp_answer, positive_answer, compliment_answer };

		rand_idx = rand() % 5 + 0;

		// Remove all punctuation, spaces, and convert each character to lowercase.
		std::string result = "I don't have a solid response.";
		std::string copy = response;
		// Lowercase
		std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char ch)
		{
			return std::tolower(ch);
	});

		// Removes punctuation
		for (int i = 0; i < copy.size(); ++i)
		{
			if (ispunct(copy[i]) || isspace(copy[i]))
			{
				copy.erase(i, 1);
				i--;
			}
		}

		// Todo Later: Refactor

		this->root_response(response, copy, usr);
		this->setting_response(result, copy);
		this->terminal_response(response, result);
		this->generate_all(answers, responses, result, copy, rand_idx);

		return result;
	}
}

// Intitalizes the Robot
Robot::Robot()
{
	set_turn(1);
	greet_sent = 0;
}

// Checks if a greeting has already
// been sent.
bool Robot::check_greeting() const
{
	if (greet_sent)
	{
		return true;
	}

	return false;
}

// Prints a special greeting.
void Robot::printGreeting()
{
	if (!check_greeting())
	{
		sleep(1);
		std::cout << "Hello I am the AI, how may I help you?\n";
		greet_sent = 1;
		turn = 0;
	}

	return;
}


#endif

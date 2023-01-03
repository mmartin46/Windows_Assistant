// Proverbs 3:5
#ifndef ROBOT_H
#define ROBOT_H

#include "libraries.cpp"


class Robot
{
    private:
        uint8_t greet_sent;
        uint8_t turn;

        std::vector<std::string> greeting_responses = { "Hi", "Hey", "What's up?", "Hey there!", "Yo!", "Hi!" };
        std::vector<std::string> quest_greet_responses = { "I'm a robot, how are you?", "Nothing much, what about you?", "I'm running, how about you?", "I'm running", "I'm a program." };

        std::vector<std::string> positive_response = { "Nice.", "Cool.", "Awesome!", "Great!", "Neat!" };

    public:
        Robot();
        void set_turn(uint8_t);
        uint8_t get_turn();
        void printGreeting();
        bool check_greeting();
        void generate(std::vector<std::string>, std::vector<std::string>, std::string &, std::string, int);
        std::string evaluate_response(const std::string &);

};

void Robot::set_turn(uint8_t num)
{
   turn = num;
}

uint8_t Robot::get_turn()
{
    return turn;
}

void Robot::generate(std::vector<std::string> ans, std::vector<std::string> resp, std::string &result, std::string copy, int rand_idx)
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

std::string Robot::evaluate_response(const std::string &response)
{
    if (get_turn())
    {
       int rand_idx;
       srand (time(NULL));
       std::vector<std::string> greeting_answer =
       {
          "hey", "hi", "hii", "hello", "heyy", "heythere"
       };

      std::vector<std::string> greet_resp_answer =
      {
         "howareyou", "howhaveyoubeen","whatsnew","whatsup","whatsgoingon", "howsitgoing"
      };

      std::vector<std::string> positive_answer =
      {
         "alright", "fine", "good", "solid", "well", "decent"
      };

       rand_idx = rand() % 5 + 0;

       // Remove all punctuation, spaces, and convert each character to lowercase.
       std::string result = "I don't understand.";
       std::string copy = response;
       // Lowercase
       std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char ch) { return std::tolower(ch); });


       // Removes punctuation
       for (int i = 0; i < copy.size(); ++i)
       {
         if (ispunct(copy[i]) || isspace(copy[i]))
         {
            copy.erase(i, 1);
            i--;
         }
       }

      std::vector<std::string>::const_iterator start, end = greeting_answer.end();
       // If the result is a greeting.
       for (start = greeting_answer.begin(); start < end; ++start)
       {
          if (copy.find(*start) != std::string::npos)
          {
             result = greeting_responses[rand_idx];
          }
       }

       end = greet_resp_answer.end();

       for (start = greet_resp_answer.begin(); start < end; ++start)
       {
         if (copy.find(*start) != std::string::npos)
         {
            result = quest_greet_responses[rand_idx];
         }
       }

       end = positive_answer.end();

       for (start = positive_answer.begin(); start < end; ++start)
       {
         if (copy.find(*start) != std::string::npos)
         {
            result = positive_response[rand_idx];
         }
       }

       generate(greeting_answer, greeting_responses, result, copy, rand_idx);
       generate(greet_resp_answer, quest_greet_responses, result, copy, rand_idx);
       generate(positive_answer, positive_response, result, copy, rand_idx);

       return result;
    }
}

// Intitalizes the Robot
Robot::Robot()
{
   set_turn(1);
   greet_sent = 0;
}

bool Robot::check_greeting()
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

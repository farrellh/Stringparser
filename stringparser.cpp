#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <stdio.h>
#include <cctype>
#include "stackstr.h"

using namespace std;

// Function for - operator
std::string subtract(std::string str1, std::string str2)
{
    size_t startpos = 0;
 
    startpos = str1.find(str2);
    if (startpos != std::string::npos)
    {
        str1 = str1.erase(startpos, str2.length());
        return str1;
    }
    else
    {
        return str1;
    }
}

// Function for < operator
std::string removeend(std::string str)
{
    str = str.substr(0, str.length()-1);
    return str;
}

// Function for > operator
std::string removestart(std::string str)
{
    str = str.substr(1, str.length());
    return str;
}

// Dealing with > and < operators
void carrotfunc(StackStr &stack, stringstream &ss, char &curr_char, 
    ofstream &output)
{
    // Store the word into stackstring
    std::string stackstring = stack.top();

    // Pop the word
    stack.pop();

    // Performing the remove operation if the string is not one character
    while(stack.top() == ">" || stack.top() == "<")
    {
        if(stack.top() == ">")
        {
            // Remove from start until the string is at one length
            if(stackstring.length() != 1)
            {
                stackstring = removestart(stackstring);
                stack.pop();
            }

            // Otherwise remove the operator
            else
            {
                stack.pop();
            }
        }

        else
        {
            // Remove from end until the string is at one length
            if(stackstring.length() != 1)
            {
                stackstring = removeend(stackstring);
                stack.pop();
            }

            // Otherwise remove the operator
            else
            {
                stack.pop();
            }
        }
    }

    // Pushing the string to the stack
    stack.push(stackstring);

    return;
}

// Group chars into words
void groupletters(StackStr &stack, stringstream &ss, ofstream &output, 
    char &curr_char, int &malformchecker)
{
    std::string stackstring = string(1, curr_char);

    // Takes care of cases where words are separated only by whitespace
    if(ss.peek() == ' ')
    {
        ss >> curr_char;
        if(islower(curr_char))
        {
            output << "Malformed\n";
            malformchecker = 1;
            return;
        }
        else
        {
         ss.seekg(-1, ios_base::cur);
        }
    }

    // Keep reading in letters
    while(ss >> curr_char)
    {
        if(islower(curr_char))
        {
            stackstring += curr_char;
        }

        else
        {
            break;
        }
        if(ss.peek() == ' ')
        {
            ss >> curr_char;
            if(islower(curr_char))
            {
                output << "Malformed\n";
                malformchecker = 1;
                return;
            }
            else
            {
             ss.seekg(-1, ios_base::cur);
            }
        }
    }

    stack.push(stackstring);
    
    // When the remove operators come after the word
    if(curr_char == '<' || curr_char == '>')
    {
        output << "Malformed\n";
        malformchecker = 1;
        return;
    }
    
    else
    {
        ss.seekg(-1, ios_base::cur);
        return;
    }
}

// Function to evaluate the two strings and add them (testing validity 
//of the addition)
void evaladd(StackStr &stack, ofstream &output, std::string &string1, 
    int &malformchecker)
{
     // Pop the operator
    stack.pop();

    // If the next operator is another operator, malformed
    if(stack.top() == "+" || stack.top() == "-")
    {
        output << "Malformed\n";
        malformchecker = 1;
        return;
    }

    // Add the string to the string now on top of the stack
    else
    {
        std::string concatstring = stack.top() + string1;
        stack.pop();
        stack.push(concatstring);
    }

    return;
}

// Function to evaluate the two strings and subtract them (testing validity 
//of the subtraction)
void evalsub(StackStr &stack, ofstream &output, std::string &string1, 
    int &malformchecker)
{
     // Pop the operator
    stack.pop();

    // If the next operator is another operator, malformed
    if(stack.top() == "+" || stack.top() == "-")
    {
        output << "Malformed\n";
        malformchecker = 1;
        return;
    }

    // Add the string to the string now on top of the stack
    else
    {
        std::string string2 = stack.top();
        
        if(subtract(string2, string1) == "")
        {
            output << "Malformed\n";
            malformchecker = 1;
            return;
        }
        else
        {
            // Pop the string
            stack.pop();

            // Push the operated string to the stack
            stack.push(subtract(string2, string1));
        }
    }

    return;
}

// Make sure there aren't mixed addition and subraction operators
void addsubcount(int &minuscount, int &pluscount, ofstream &output, 
    int &malformchecker)
{
    // If minus count is greater than 0, plus count must be 0
    if(minuscount > 0)
    {
        if(pluscount != 0)
        {
            output << "Malformed\n";
            malformchecker = 1;
            return;
        }
    }

    // If plus count is greater than 0, minus count must be 0
    else if(pluscount > 0)
    {
        if(minuscount != 0)
        {
            output << "Malformed\n";
            malformchecker = 1;
            return;
        }
    }

    return;
}

// Function to check if there was a malformation
bool malform(int &malformchecker)
{
    if(malformchecker != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to clear the stack
void clearstack(StackStr &stack)
{
    while(!stack.empty())
    {
        stack.pop();
    }
    return;
}

int main(int argc, char* argv[])
{
    // Error message 
    if (argc < 3) 
    {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }
    // Reading in arguments
    ifstream input(argv[1]);
    ofstream output(argv[2]);

    StackStr stack;
    string curr_expr;
    char curr_char;

    // Reading in the first expression
    while(getline(input, curr_expr))
    {
        stringstream ss; 
        ss << curr_expr;
        if(curr_expr == "")
        {
            output << "Malformed\n";
            continue;
        }
        int malformchecker = 0;
        int closedparen = 0;
        int openparen = 0;

        // Reading in the first character of the first expression
        while(ss >> curr_char)
        {
            // Check if characters are all appropriate 
            if(islower(curr_char) || curr_char == '+' || curr_char == '-' || 
                curr_char == '>' || curr_char == '<' || curr_char == '(' || 
                curr_char == ')')
            {

                if(curr_char != ')')
                {
                    if(curr_char == '>'|| curr_char == '<')
                    {
                        // Checks if add or subtract operators come after < or >
                        if(ss.peek() == '+' || ss.peek() == '-')
                        {
                            output << "Malformed\n";
                            malformchecker = 1;
                            if(malform(malformchecker))
                            {
                                break;
                            }
                        }

                        stack.push(string(1,curr_char));
                    }

                    else if(curr_char == '(')
                    {
                        stack.push(string(1,curr_char));
                    }

                    else if(islower(curr_char))
                    {
                        // String to store the word so I can check the 
                        //operators before it
                        std::string checkop;
                        groupletters(stack, ss, output, curr_char, 
                            malformchecker);
                        if(malform(malformchecker))
                        {
                            break;
                        }
                        checkop = stack.top();

                        // Pop the word
                        stack.pop();
                        if(stack.top() == "<" || stack.top() == ">")
                        {
                            // Put word back on the stack
                            stack.push(checkop);
                            carrotfunc(stack, ss, curr_char, output);
                        }

                        else if(stack.top() == ")")
                        {
                            output << "Malformed\n";
                            malformchecker = 1;
                            if(malform(malformchecker))
                            {
                                break;
                            }
                        }

                        else
                        {
                            stack.push(checkop);
                        }
                    }

                    // If the char is + or -
                    else
                    {
                        // For cases like (+
                        if(stack.top() == "(")
                        {
                            output << "Malformed\n";
                            malformchecker = 1;
                            if(malform(malformchecker))
                            {
                                break;
                            }
                        }
                        stack.push(string(1, curr_char));
                    }
                }

            // Check to make sure there aren't any malformed operands like +)
                else if(stack.top() == "+" || stack.top() == "-" || stack.top() 
                    == "<" || stack.top() == ">" || stack.top() == "(")
                {
                    output << "Malformed\n";
                    malformchecker = 1;
                    if(malform(malformchecker))
                    {
                        break;
                    }
                }

                // Takes care of case like )abc
                else if(islower(ss.peek()))
                {
                    output << "Malformed\n";
                    malformchecker = 1;
                    if(malform(malformchecker))
                    {
                        break;
                    }
                }
                
                else
                {
                    closedparen++;
                    std::string totalstring;
                    int minuscount = 0;
                    int pluscount = 0;
                    int addsubop = 0;
                    // Until you hit the open parentheses
                    while(stack.top() != "(")
                    {
                        // Checking for mixed operators
                        if(stack.top() == "+" || stack.top() == "-")
                        {
                            if(stack.top() == "+")
                            {
                                pluscount++;
                            }
                            else
                            {
                                minuscount++;
                            }

                            addsubcount(minuscount, pluscount, output, 
                                malformchecker);
                            if(malform(malformchecker))
                            {
                                break;
                            }
                        }
                        // Put the top string into a string variable
                        std::string string1 = stack.top();

                        if(stack.top() == "")
                        {
                            output << "Malformed\n";
                            malformchecker++;
                            break;
                        }

                        // Pop the string
                        stack.pop();

                        // If you find an addition operator 
                        if(stack.top() == "+")
                        {
                            addsubop++;
                            pluscount++;
                            addsubcount(minuscount, pluscount, output, 
                                malformchecker);
                            if(malform(malformchecker))
                            {
                                break;
                            }

                            while(stack.top() == "+")
                            {
                                // Add the words
                                evaladd(stack, output, string1, malformchecker);

                                // Call the addition function with the new word
                                string1 = stack.top();

                                // Store the word into totalstring
                                totalstring = stack.top();

                                // Pop the word
                                stack.pop();
                            }
                        }

                        // If you find a subtraction operator
                        if(stack.top() == "-")
                        {
                            addsubop++;
                            minuscount++;
                            addsubcount(minuscount, pluscount, output, 
                                malformchecker);
                            if(malform(malformchecker))
                            {
                                break;
                            }
                            
                            evalsub(stack, output, string1, malformchecker);
                            string1 = stack.top();
                            totalstring = stack.top();
                            stack.pop();
                            if(stack.top() == "-")
                            {
                                output << "Malformed\n";
                                malformchecker++;
                                break;
                            } 
                        }
                    }
                    if(malform(malformchecker))
                    {
                        break;
                    }

                    if(addsubop == 0)
                    {
                        output << "Malformed\n";
                        malformchecker++;
                        break;
                    }

                    // Update open parenthesis counter
                    openparen++;

                    // Push the open parenthesis
                    stack.pop();

                    // If there are more operators outside parenthesis
                    if(stack.top() == "<" || stack.top() == ">")
                    {
                        stack.push(totalstring);
                        carrotfunc(stack, ss, curr_char, output);
                    }
                    else
                    {
                        stack.push(totalstring);
                    }
                }
            }

            // If its whitespace
            else if(curr_char == ' ')
            {
                continue;
            }

            else
            {
                output << "Malformed\n";
                malformchecker = 1;
                if(malform(malformchecker))
                {
                    break;
                }
            }
        }

        if(malform(malformchecker))
        {
            clearstack(stack);
            continue;
        }

        // Checking to see if there are any extraneous operators after word
        if(stack.top() == "+" || stack.top() == "-" || stack.top() == "<" || 
            stack.top() == ">")
        {
            clearstack(stack);
            output << "Malformed\n";
            continue;
        }
        std::string finalword = stack.top();
        stack.pop();

        // Evaluate what's left in the stack
        if(!stack.empty())
        {
            if(stack.top() == "(")
            {
                openparen++;
            }
            else if(stack.top() == ")")
            {
                closedparen++;
            }

            if(openparen != closedparen)
            {
                clearstack(stack);
                output << "Malformed\n";
            }

            if(stack.top() == "-" || stack.top() == "+")
            {
                clearstack(stack);
                output << "Malformed\n";
            }
        }
        else
        {
            stack.push(finalword);
            if(!islower(stack.top().at(0)))
            {
                clearstack(stack);
                output << "Malformed\n";
                continue;
            }

            // Write the end statement into the output file
            output << stack.top() << endl;
            stack.pop();
            stack.pop();
        }
    }
  

    return 0;
}

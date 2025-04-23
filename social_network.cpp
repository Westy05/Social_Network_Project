#include "user.h"
#include "network.h"
#include <iostream>
#include <sstream>

std::string findFullName(std::stringstream &stream);
void printUserOptions();

int main(int argc, char const *argv[]) {    
    Network net;
    net.readUsers(const_cast<char*>(argv[1])); // casts argument (assumed to be exact file name) as a non-const so code works

    printUserOptions();

    // first input of program's runtime and stores entire input in userInput
    std::string userInput;
    std::cout << "> ";
    std::getline(std::cin, userInput);
    
    // initializes string stream that will tokenize each and every user input for the program to process
    std::stringstream inputTokenizer(userInput);
    
    int option;
    inputTokenizer >> option;
    bool firstTime = true;
    
    // while loop ends if user inputs any number outside the range of 1-4 at the start
    // the loop will also end if the command doesn't start with a number because option will default to 0 making it out of range
    while (option < 5 && option > 0) {
        if (!firstTime) {
            printUserOptions();

            std::cout << "> ";
            std::getline(std::cin, userInput);
            
            // resets string stream for new input
            inputTokenizer.clear();
            inputTokenizer.str(userInput);
            inputTokenizer >> option;
        } else {
            firstTime = false;
        }

        if (option == 1) { // ---add a new user---
            // i should mention i noticed that you can add an empty user (user with fields not filled out)
            // but there was no mention to add a check so i didn't
            int userId = net.numUsers();
            std::string fullName;
            int birthYear, zipCode;

            fullName = findFullName(inputTokenizer);
            inputTokenizer >> birthYear;
            inputTokenizer >> zipCode;

            User* tempUser = new User(userId, fullName, birthYear, zipCode, std::set<int>());
            net.addUser(tempUser);
        } else if (option == 2) { // ---add a friend connection---
            std::string username1 = findFullName(inputTokenizer);
            std::string username2 = findFullName(inputTokenizer);
            
            // checks for errors
            if (net.addConnection(username1, username2) == -1) {
                std::cerr << "Error: Command incorrectly formatted and/or user(s) do not exist." << std::endl;
            }
        } else if (option == 3) { // ---delete a friend connection---
            std::string username1 = findFullName(inputTokenizer);
            std::string username2 = findFullName(inputTokenizer);

            if (net.deleteConnection(username1, username2) == -1) {
                // not going to include "users not being friends already" part in the message
                // because my code is designed where nothing will happen if such a case arises (thank set's erase function).
                // therefore it is unnecessary to include. omg i shouldn't have spent all this time writing just this short explanation.
                std::cerr << "Error: Command incorrectly formatted and/or user(s) do not exist." << std::endl;
            }
        } else if (option == 4) { // ---write to a file (save current users stored in memory)---
            std::string fileName;
            inputTokenizer >> fileName;

            // gets the c string version of the string fileName and then casts as a non const
            if (net.writeUsers(const_cast<char*>(fileName.c_str())) == -1) {
                std::cerr << "Error: Failed to open file." << std::endl;
            } else {
                std::cout << "Number of users written: " << net.numUsers() << std::endl;
            }
        }
    }

    std::cout << "Exiting program..." << std::endl;

    return 0;
}

// pre: next token in string stream must be the first name of a user followed by their last name, separated by a whitespace
// post: returns a whole string containing both the first and last name of a user such as "John Smith"
std::string findFullName(std::stringstream &stream) {
    std::string fullName;
    std::string secondName;

    stream >> fullName;
    stream >> secondName;
    fullName += " " + secondName;

    return fullName;
}

// pre: none
// post: prints out available options for user
void printUserOptions() {
    std::cout << std::endl << "List of available options:" << std::endl;
    std::cout << "Option 1: Add a new user." << std::endl;
    std::cout << "Option 2: Add a friend connection." << std::endl;
    std::cout << "Option 3: Delete a friend connection." << std::endl;
    std::cout << "Option 4: Write current network to file." << std::endl << std::endl;
}
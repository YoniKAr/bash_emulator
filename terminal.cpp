#include "f_sys.h"
#include "terminal.h"
//#include "text_editor.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <iterator>

void terminal::welcome_screen() {
    std::cout<< "Welcome to mTerminal v0.01\n"<<"Lightweight "<<"Written in C++ by Hirdae.\n";
   // std::cout <<"Here's a Rotating Donut for Showoff\n"<< "Type Clear To Continue" << "\n \n \n";
    //file_sys_.rotating_donut();
}

terminal::terminal() {
    commands_ = {"help", "cd", "mkdir", "touch", "ls", "cat", "rm", "rmdir", /*"cp", "mv",*/ "useradd", "userdel", "su", "passwd","exit","edit","whoami","donut","echo","lim"}; //"browser", "python", "exit"};
   // curr_user_ = "guest"; //fix later
    welcome_screen(); // call welcome_screen method
}

void terminal::print_prompt() {
       // Get the current working directory
   // Get the current working directory
    std::string curr_dir = file_sys_.get_curr_dir();

    // Print the prompt with the current user and directory in green color
    std::cout << "\033[0;32m" << file_sys_.current_user << "@linux-emulator:" << curr_dir << "$\033[0m ";

    // Print the blinking cursor
    std::cout << "\033[5m\033[0m";

    // Read the user input
    std::string input;
    std::getline(std::cin, input);

    // Tokenize the input
    std::istringstream iss(input);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());

    // If no input, print the prompt again
    if (tokens.empty()) {
       print_prompt();
        return;
    }

    // Highlight the command in red
    //std::cout <<" ---> "<<"\033[0;31m" << tokens[0] << "\033[0m";

    // Highlight the arguments in orange
    //for (size_t i = 1; i < tokens.size(); i++) {
      //  std::cout << "\033[0;33m" << tokens[i] << "\033[0m \n";
    //}

    // Process the command
    process_command(input);
}

//void terminal::process_command(const std::string& command)

void terminal::run() {
   // std::string command;
    while (true) {
        print_prompt();
        //std::getline(std::cin, command);
        //if (command.empty()) {
          //  continue;
        //}
        //else if(command=="exit") break;
    }
}



void terminal::process_command(const std::string& command) {
      // Split the command into tokens using space as delimiter
    //std::istringstream iss(command);
    file_sys_.op(command);
//    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});

    // Check if the command is empty
//    if (tokens.empty()) {
  //      return;
    //}

   /*// Get the command name and arguments
    std::string cmd_name = tokens[0];
    std::string args = tokens.size() > 1 ? tokens[1] : "";

    // Map the command name to the corresponding function
    if (cmd_name == "help") {
        list_commands();
    } else if (cmd_name == "cd") {
        change_directory(args);
    } else if (cmd_name == "mkdir") {
        file_sys_.op(command);
    } else if (cmd_name == "touch") {
        create_file(args);
    } else if (cmd_name == "ls") {
        list_directory(args);
    } else if (cmd_name == "edit") {
        edit_file(args);
    } else if (cmd_name == "rm") {
        file_sys_.op(command);
    } else if (cmd_name == "rmdir") {
        file_sys_.op(command);
    } //else if (cmd_name == "cp") {
      //  copy_file(args);} 
    //else if (cmd_name == "mv") {
       // move_file(args);} 
       //else if (cmd_name == "users") {
        //manage_users(args);}
    // else if (cmd_name == "surf") {
       // surf_internet(args);}
    //else if (cmd_name == "python") {
        //run_python(args);}
    else if (cmd_name=="donut"){
        file_sys_.rotating_donut();
    }
    else if (cmd_name=="whoami"){
        cout<<curr_user_<<endl;
    }
    else if(cmd_name=="su")
    else if (cmd_name == "exit") {
        exit_terminal();
    } else {
        std::cout << "Command not found. Type 'help' for a list of commands." << std::endl;
    }*/
}
void terminal::list_commands() {
    std::cout << "Available commands:\n";
    for (const auto& command : commands_) {
        std::cout << "- " << command << "\n";
    }
}
void terminal::change_directory(const std::string& args){
        file_sys_.change_directory(args);
}

void terminal::create_file(const std::string& args){

    if (file_sys_.file_exists(args)){
        std::cout<< "File " << args << "Already Exists.";
    }
    else file_sys_.current->add_file(args,"");
}


void terminal::list_directory(const std::string& args){
    file_sys_.current->print_dir_contents();
}

void terminal::copy_file(const std::string& args){}


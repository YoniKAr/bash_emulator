#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <unordered_set>
#include "f_sys.h"
//#include "browser.h"
//#include "python_interpreter.h"


using namespace std;

class terminal {
public:
    terminal();

    void run();

private:
    void welcome_screen();
    void print_prompt();
    void process_command(const std::string& command);
    void list_commands();
    void change_directory(const std::string& args);
    void create_directory(const std::string& args);
    void create_file(const std::string& args);
    void list_directory(const std::string& args);
    void edit_file(const std::string& args);
    void delete_file(const std::string& args);
    void delete_directory(const std::string& args);
    void copy_file(const std::string& args);
    void move_file(const std::string& args);
    void manage_users(const std::string& args);
    void surf_internet(const std::string& args);
    void run_python(const std::string& args);
    void exit_terminal();

    std::unordered_set<std::string> commands_;
    f_sys file_sys_;
    //std::set<std::string> history;
    //std::set<std::string>::iterator current;
   // browser browser_;
  // python_interpreter python_;

    std::string curr_user_;
};

#endif // TERMINAL_H
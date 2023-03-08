#ifndef BASH_FILES_H
#define BASH_FILES_H // Guards


#include <iostream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <fstream>
#include <vector>

using namespace std;

class directory
{
public:
    // Constructor for sub_directories
    directory(std::string thisname, directory* upper);
    // Constructor for initial directory
    directory(std::string thisname);

    void add(std::string item, std::string type); // Method to Add File or Directory to curr Dir
    std::string get_name() const;
    void add_file(std::string filename, std::string content);
    void remove(std::string filename,std::string type);
    void print_dir_contents();
    friend class f_sys;

private:
    std::string name; // Name of Directory
    std::string pathname;
    std::map<std::string,std::string> files; // Files in Directory (<name,content>)
    std::map<std::string, directory*> sub_dir; // Sub_Directories in Directory
    directory* parent; // Parent Directory
    directory* self; // Self Id
    // Permission attributes
    std::map<std::string, std::map<std::string, std::pair<bool, bool>>> file_permissions; // File-level permissions
    std::map<std::string, std::map<std::string, std::pair<bool, bool>>> directory_permissions; // Directory-level permissions
};

class f_sys
{
public:
    f_sys();
    ~f_sys();
    void op(std::string cmd);
    string get_curr_dir(); //get current directory
    void add(std::string item);
    friend class terminal;
    // File and directory manipulation methods
   // void copy_file(std::string filename, std::string dest_dir);
    //void delete_file(std::string filename);
    //void create_directory(std::string dir_name);
    //void delete_directory(std::string dir_name);

    // Permission methods
    void add_user(std::string username);
    void remove_user(std::string username);
    void set_permission(std::string item, std::string username, bool read_permission, bool write_permission);
    void rotating_donut(); 
    bool check_for_input();
    void clear_console();
private:
    directory* root = new directory("/"); // Initialize root dir
    directory* current = root; // Set Curr directory to root
    std::unordered_set<std::string> commands; // Command List
    std::set<std::string> users;
    std::string current_user;

     // Text editor
    std::vector<std::string> text_buffer;
    bool in_text_editor = false;
    std::string text_editor_file;

    // Helper methods
    std::vector<std::string> split(std::string str, char delimiter);
    bool file_exists(std::string filename);
    bool directory_exists(std::string dirname);
    bool is_file(std::string item);
    bool is_directory(std::string item);
    void print_permissions(std::string item);
    std::string get_permission_string(std::string item, std::string username);
    void make_directory(const std::string& dirname);
    void list_directory();
    void remove_directory(const std::string& dirname);
    void remove_file(const std::string& filename);
    void open_file(const std::string& filename);
    void change_directory(const std::string& dirname);

};

#endif
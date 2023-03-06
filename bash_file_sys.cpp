#include "bash_files.h"
#include "text_editor.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

/* Directory Methods */

// Contructor for sub_directories
directory::directory(std::string thisname, directory *upper)
    : name(thisname), parent(upper), self(this) {}
// Constructor for initial directory
directory::directory(std::string thisname)
    : name(thisname)
{
    // Initializing
    self = this;
    parent = this;
}

void directory::add(std::string item, std::string type)
{
    // Check if item already exists in directory
    if (files.count(item) || sub_dir.count(item))
    {
        std::cout << "Item with name \"" << item << "\" already exists in directory \"" << name << "\".\n";
        return;
    }
    // Add new file to directory
    if (type == "file")
    {
        files[item] = "";
        std::cout << "Added new file \"" << item << "\" to directory \"" << name << "\".\n";
    }
    // Add new sub-directory to directory
    else if (type == "directory")
    {
        sub_dir[item] = new directory(item, this);
        std::cout << "Added new sub-directory \"" << item << "\" to directory \"" << name << "\".\n";
    }
    // Invalid item type
    else
    {
        std::cout << "Invalid item type \"" << type << "\". Item not added to directory \"" << name << "\".\n";
    }
}
string directory::get_name() const { return this->name; }
// Method to Add File to curr Dir
void directory::add_file(std::string filename, std::string content)
{
    files[filename] = content;
}

// Method to Remove File from curr Dir
void directory::remove(std::string item, std::string type)
{
    // Remove file from directory
    if (type == "file")
    {
        if (files.count(item))
        {
            files.erase(item);
            std::cout << "Removed file \"" << item << "\" from directory \"" << name << "\".\n";
        }
        else
        {
            std::cout << "File with name \"" << item << "\" does not exist in directory \"" << name << "\".\n";
        }
    }
    // Remove sub-directory from directory
    else if (type == "directory")
    {
        if (sub_dir.count(item))
        {
            delete sub_dir[item];
            sub_dir.erase(item);
            std::cout << "Removed sub-directory \"" << item << "\" from directory \"" << name << "\".\n";
        }
        else
        {
            std::cout << "Sub-directory with name \"" << item << "\" does not exist in directory \"" << name << "\".\n";
        }
    }
    // Invalid item type
    else
    {
        std::cout << "Invalid item type \"" << type << "\". Item not removed from directory \"" << name << "\".\n";
    }
}

// Method to Print Contents of Directory
void directory::print_dir_contents()
{
    std::cout << "Contents of directory " << name << ":\n";
    std::cout << "Directories:\n";
    for (auto dir_it = sub_dir.begin(); dir_it != sub_dir.end(); ++dir_it)
    {
        std::cout << " - " << dir_it->first << "\n";
    }
    std::cout << "Files:\n";
    for (auto file_it = files.begin(); file_it != files.end(); ++file_it)
    {
        std::cout << " - " << file_it->first << "\n";
    }
}

/* File System Methods */

// Constructor
f_sys::f_sys()
{
    // Initialize command list
    commands.insert("mkdir");
    commands.insert("ls");
    commands.insert("rmdir");
    commands.insert("rm");
    commands.insert("lim");
    commands.insert("cd");
    commands.insert("help");
    commands.insert("clear");
    commands.insert("su");
    commands.insert("help");
    commands.insert("au");
    commands.insert("whoami");
    commands.insert("echo");
    // commands.insert("");

    // Add default user
    add_user("guest");
    current_user = "guest";
}
// Destructor
f_sys::~f_sys()
{
    // Free memory used by directories
    delete root;
}

void f_sys::add(std::string item)
{
    (this->current->add(item, "file")); // Add file to current directory
}
void f_sys::op(std::string cmd)
{
    std::vector<std::string> tokens = split(cmd, ' ');

    if (commands.find(tokens[0]) != commands.end())
    {
        if (tokens[0] == "mkdir")
        {
            if (tokens.size() == 2)
            {
                current->add(tokens[1], "directory");
            }
            else
            {
                std::cout << "Invalid arguments. Usage: mkdir <dir_name>" << std::endl;
            }
        }
        else if (tokens[0] == "ls")
        {
            current->print_dir_contents();
        }
        else if (tokens[0] == "rmdir")
        {
            if (tokens.size() == 2)
            {
                current->remove(tokens[1], "directory");
            }
            else
            {
                std::cout << "Invalid arguments. Usage: rmdir <dir_name>" << std::endl;
            }
        }
        else if (tokens[0] == "rm")
        {
            if (tokens.size() == 2)
            {
                current->remove(tokens[1], "file");
            }
            else
            {
                std::cout << "Invalid arguments. Usage: rm <file_name>" << std::endl;
            }
        }
        else if (tokens[0] == "lim")
        {
            if (tokens.size() == 2)
            {
                std::string filename = tokens[1];
                std::cout << "Enter text for file '" << filename << "'. Press Esc to finish." << std::endl;
                std::string content;
                char c;
                bool end_writing = false;
                while (std::cin.get(c))
                {
                    if (c == 0x1B) // Esc key
                    {
                        end_writing = true;
                        break;
                    }
                    content += c;
                }
                if (end_writing)
                {
                    current->add_file(filename, content);
                }
            }
            else
            {
                std::cout << "Invalid arguments. Usage: lim <file_name>" << std::endl;
            }
        }
        else if (tokens[0] == "cd")

        {
            if (tokens.size() == 2)
            {
                if (tokens[1] == "..")
                {
                    if (current->get_name() != "/")
                    {
                        current = current->parent;
                    }
                }
                else
                {
                    directory *next_dir = current->sub_dir[tokens[1]];
                    if (next_dir != nullptr)
                    {
                        current = next_dir;
                    }
                    else
                    {
                        std::cout << "Directory '" << tokens[1] << "' does not exist." << std::endl;
                    }
                }
            }

            else
            {
                std::cout << "Invalid arguments. Usage: cd <dir_name> or cd .." << std::endl;
            }
        }
    else if (tokens[0] == "cat")
    {
        if (tokens.size() == 2)
        {
            std::string filename = tokens[1];
            std::map<std::string, std::string>::iterator it = current->files.find(filename);
            if (it != current->files.end())
            {
                std::cout << it->second << std::endl;
            }
            else
            {
                std::cout << "File '" << filename << "' does not exist." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid arguments. Usage: cat <filename>" << endl;
        }
    }
    else if (tokens[0] == "clear")
    {
        // Clear console output
        std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
    }
    else if (tokens[0] == "su")
    {
        if (tokens.size() == 2)
        {
            // Switch to specified user
            std::string new_username = tokens[1];
            if (users.find(new_username) != users.end())
            {
                current_user = new_username;
                std::cout << "Switched to user '" << current_user << "'" << std::endl;
            }
            else
            {
                std::cout << "User '" << new_username << "' does not exist." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid arguments. Usage: su <username>" << std::endl;
        }
    }

    else if (tokens[0] == "help")
    {
        std::cout << "List of available commands:" << std::endl;
        for (const auto &command : commands)
        {
            std::cout << "- " << command << std::endl;
        }
    }

    else if (tokens[0] == "echo")
    {
        if (tokens.size() > 1)
        {
            for (size_t i = 1; i < tokens.size(); i++)
            {
                std::cout << tokens[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << std::endl;
        }
    }
    else if (tokens[0] == "au")
    {
        if (tokens.size() == 2)
        {
            std::string username = tokens[1];
            this->add_user(username);
        }
        else
        {
            std::cout << "Invalid arguments. Usage: au <username>" << std::endl;
        }
    }
    else if (tokens[0] == "whoami")
    {

        std::cout << current_user << endl;
    }
    }
    else
    {
        std::cout << "Invalid command. Type 'help' for a list of commands." << std::endl;
    }

}
// For Debugging
// Set_Permissions
void f_sys::set_permission(std::string item, std::string user, bool read, bool write)
{
    // Check if item is a file or directory
    bool is_file = current->files.count(item);
    bool is_directory = current->sub_dir.count(item);

    // If item exists, add or modify permissions
    if (is_file || is_directory)
    {
        // Modify file permissions
        if (is_file)
        {
            // Create a new entry if user does not have permissions for file yet
            if (!current->file_permissions.count(item))
            {
                current->file_permissions[item] = std::map<std::string, std::pair<bool, bool>>();
            }

            // Add or modify permissions for user
            current->file_permissions[item][user] = std::make_pair(read, write);
        }
        // Modify directory permissions
        else
        {
            // Create a new entry if directory does not have permissions for user yet
            if (!current->directory_permissions.count(item))
            {
                current->directory_permissions[item] = std::map<std::string, std::pair<bool, bool>>();
            }

            // Add or modify permissions for user
            current->directory_permissions[item][user] = std::make_pair(read, write);
        }
    }
}
// Add a user to the file system
void f_sys::add_user(std::string username)
{
    // Check if user already exists
    if (users.find(username) != users.end())
    {
        std::cout << "User already exists.\n";
    }
    else
    {
        // Add user to the set of users
        users.insert(username);
        std::cout << "User " << username << " has been added.\n";
    }
}

// Remove a user from the file system
void f_sys::remove_user(std::string username)
{
    // Check if user exists
    if (users.find(username) != users.end())
    {
        // Remove user from the set of users
        users.erase(username);
        std::cout << "User " << username << " has been removed.\n";
    }
    else
    {
        std::cout << "User does not exist.\n";
    }
}

// Method to split a string by a delimiter
std::vector<std::string> f_sys::split(std::string str, char delimiter)
{

    std::vector<std::string> tokens;
    std::istringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

// Method to check if a file exists
bool f_sys::file_exists(std::string filename)
{
    return current->files.count(filename);
}

// Method to check if a directory exists
bool f_sys::directory_exists(std::string dirname)
{
    return current->sub_dir.count(dirname);
}

// Method to check if an item is a file
bool f_sys::is_file(std::string item)
{
    return current->files.count(item);
}

// Method to check if an item is a directory
bool f_sys::is_directory(std::string item)
{
    return current->sub_dir.count(item);
}

void f_sys::print_permissions(std::string item)
{
    if (current->file_permissions.count(item))
    {
        std::cout << "File-level permissions for " << item << ":" << std::endl;
        for (const auto &permission : current->file_permissions[item])
        {
            std::cout << permission.first << " - read: " << permission.second.first << " write: " << permission.second.second << std::endl;
        }
    }
    if (current->directory_permissions.count(item))
    {
        std::cout << "Directory-level permissions for " << item << ":" << std::endl;
        for (const auto &permission : current->directory_permissions[item])
        {
            std::cout << permission.first << " - read: " << permission.second.first << " write: " << permission.second.second << std::endl;
        }
    }
    if (!current->file_permissions.count(item) && !current->directory_permissions.count(item))
    {
        std::cout << "No permissions found for " << item << std::endl;
    }
    return;
}

std::string f_sys::get_permission_string(std::string item, std::string username)
{
    if (current->file_permissions.count(item) == 0 || current->file_permissions[item].count(username) == 0)
    {
        // If the item or the user is not found in the permission map, return "None"
        return "None";
    }
    else
    {
        // Otherwise, get the permission pair for the user and item, and construct the permission string
        std::pair<bool, bool> permission_pair = current->file_permissions[item][username];
        std::string permission_string = string((permission_pair.first ? "r" : "-")) + string((permission_pair.second ? "w" : "-"));
        return permission_string;
    }
}

// Create a new directory
void f_sys::make_directory(const std::string &dirname)
{
    if (current->sub_dir.find(dirname) != current->sub_dir.end())
    {
        std::cout << "Directory " << dirname << " already exists." << std::endl;
        return;
    }
    directory *new_dir = new directory(dirname, current);
    current->sub_dir[dirname] = new_dir;
}

// List the contents of the current directory
void f_sys::list_directory()
{
    std::cout << "Contents of " << current->get_name() << ":" << std::endl;
    std::cout << "Directories:" << std::endl;
    for (const auto &sub : current->sub_dir)
    {
        std::cout << " " << sub.first << std::endl;
    }
    std::cout << "Files:" << std::endl;
    for (const auto &file : current->files)
    {
        std::cout << " " << file.first << std::endl;
    }
}

// Remove a directory
void f_sys::remove_directory(const std::string &dirname)
{
    if (current->sub_dir.find(dirname) == current->sub_dir.end())
    {
        std::cout << "Directory " << dirname << " does not exist." << std::endl;
        return;
    }
    directory *dir = current->sub_dir[dirname];
    if (!dir->files.empty() || !dir->sub_dir.empty())
    {
        std::cout << "Directory " << dirname << " is not empty." << std::endl;
        return;
    }
    current->sub_dir.erase(dirname);
    delete dir;
}

// Remove a file
void f_sys::remove_file(const std::string &filename)
{
    if (current->files.find(filename) == current->files.end())
    {
        std::cout << "File " << filename << " does not exist." << std::endl;
        return;
    }
    current->files.erase(filename);
}

// Create a new file and open it for editing
void f_sys::open_file(const std::string &filename)
{
    if (current->files.find(filename) != current->files.end())
    {
        std::cout << "File " << filename << " already exists." << std::endl;
        return;
    }
    std::ofstream new_file(filename);
    if (!new_file.is_open())
    {
        std::cout << "Failed to create file " << filename << "." << std::endl;
        return;
    }
    new_file.close();
    current->add(filename, "file");
    // editor.open_file(filename);
}

// Change the current directory
void f_sys::change_directory(const std::string &dirname)
{
    if (dirname == "..")
    {
        if (current == root)
        {
            std::cout << "Already at root directory." << std::endl;
            return;
        }
        current = current->parent;
    }
    else
    {
        if (current->sub_dir.find(dirname) == current->sub_dir.end())
        {
            std::cout << "Directory " << dirname << " does not exist." << std::endl;
            return;
        }
        current = current->sub_dir[dirname];
    }
}

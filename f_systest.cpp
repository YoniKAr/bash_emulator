#include <iostream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <sstream>
#include "bash_files.h"



int 
main()
{

    f_sys my_sys;
    //int a=10;
    string command="";
    while(true){
        getline(cin,command);
        if(command!=""){
        my_sys.op(command);}
        else{
            continue;
        }
        
    }    




    /*my_sys.op("mkdir dir1");
    my_sys.op("ls");
    my_sys.op("cd dir1");
    my_sys.op("lim file1.txt");
    my_sys.op("cat file1.txt");
    my_sys.op("cd ..");
    my_sys.op("rmdir dir1");
    my_sys.op("ls");*/
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>
using namespace std;

vector<char *> parse(char *cstr){               //parse function

    vector<char *> parsed_cmd;                  //vector of char pointers
    char * single_cmd = strtok (cstr, " ");     //break up string into 
                                                    //tokens with space as
                                                    //delimiter
    parsed_cmd.push_back(single_cmd);           //push back tokens into
                                                    //vector
    single_cmd = strtok(NULL, " ");             //end vector with null
    parsed_cmd.push_back(NULL);

    return parsed_cmd;
}

void execute(vector<char*>){                    //execute function
                                                    //(incomplete)

    int counter=0;
    pid_t pid = fork();

    if(pid==0){
       // if(execvp();
    }

    return;    

} 
        


int main(){
    string cmd;                                 //create string var
    cout << "$ ";                               //prompt for input
    cin >> cmd;                                 //store in cmd var
    char *ccmd = new char[cmd.length()+1];      //make char array 
    strcpy(ccmd, cmd.c_str());                  //copy string into char
                                                    //array

    parse(ccmd);                                //parse string
    return 0;
}

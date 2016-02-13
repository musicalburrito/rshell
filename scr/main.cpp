#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;


void parse(char **parsed_cmd, char cstr[]){         //parse function 

    char *single_cmd = strtok(cstr, " ");           //break up cstr using " " as delimiter
    int i = 0;                                      //counter             
    while(single_cmd != NULL) {                     //push back tokens into array
        parsed_cmd[i] = single_cmd;
        i++;
        single_cmd = strtok(NULL, " ");
    }
      parsed_cmd[i] = NULL;                         //end array with null 
    
    return;
}

bool execute(char **cstr){
    int status = 0;    //execute function
    int arg_num = 0;
    pid_t pid = fork();
    
    while (cstr[arg_num] != NULL){
    if(pid < 0){
       perror("fork error");
       return false;  
       exit(-1);
    }
    else if(pid == 0){        
        	    //for child
        //status += 1;
        //status -= 1;
        wait(&status);

    }
    else{
       cout << cstr[arg_num] << endl;
       if( execvp(cstr[arg_num], cstr) == -1){
           return false;
           perror("exec failed");
       }
      // exit(1);
    }
    ++arg_num;
    }
    return true;
} 


int main(){

    //char **commands = new char* [256];
    char token[256];

    while(true){
        if(getlogin() != NULL){
                cout << getlogin() << "@";
        }
        char name[256];
        if(gethostname(name,256) != -1){
            cout <<name << " ";
        }

        cout << "$ ";                   
        cin.getline(token,256);
        cin.clear(); 
        string ex(token);
        //cout << ex << endl; 
        string str_exit = "exit";
        vector<string> parsed_string;

        if(ex.find(str_exit) != string::npos){
            cout << "Exiting shell" << endl;
            break;
        }

        char **parsed = new char*[256];
        vector<int> connector_index;  
        parse(parsed,token); 
        //execute(parsed);
 
        for(unsigned int i = 0; parsed[i] != NULL; ++i){
            
            parsed_string.push_back(parsed[i]);
            
            if(parsed_string.at(i) == ";"){
                connector_index.push_back(i);
                cout << "; connector at " << i << endl;
            }
            else if(parsed_string.at(i) == "&&"){
                connector_index.push_back(i);
                cout << "&& connector at " << i << endl;
            }
            else if(parsed_string.at(i) == "||"){
                connector_index.push_back(i);
                cout << "|| connector at " << i << endl;
            }
            else if(parsed_string.at(i) == "#"){
                connector_index.push_back(i);
                cout << "# commend at " << i << endl;
           }
        }

        //delete []parsed;

        int curr_index_cmds = 0;
        int curr_index = 0;
        //char **commands = new char* [256];
        //char *temp = new char[50];
        string temp3 = "";

        for(unsigned int a = 0; a < connector_index.size(); ++a){
            char **commands = new char* [256];
            //if(connector_index.size() > 1){
                if(parsed_string.at(connector_index.at(a)) == ";"){
                    for(int b = curr_index; b < connector_index.at(a); ++b){
                        commands[curr_index_cmds]  = parsed[curr_index];
                        ++curr_index_cmds;
                        ++curr_index;
                    }
                    commands[curr_index_cmds + 1] = NULL;
                    execute(commands);
                }
                else if(parsed_string.at(connector_index.at(a)) == "&&"){
                    for(int b = curr_index; b < connector_index.at(a); ++b){
                        commands[curr_index_cmds] = parsed[curr_index];
                        ++curr_index_cmds;
                        ++curr_index;
                    }
                    commands[curr_index_cmds + 1] = NULL;
                    execute(commands);
                    commands = NULL;
                    delete []commands;
                    curr_index_cmds = 0;
                    if (a + 1 >= connector_index.size()){
                        //cout << curr_index << " ";
                        //++curr_index;
                        ++curr_index;
                        ++a;
                        break;
                    }

                    //+curr_index;
                    char **commands = new char*[256];
                   if (a + 1 < connector_index.size()){
                        //++a;
                    for(int b = curr_index; b < connector_index.at(a); ++b){
                        commands[curr_index_cmds] = parsed[curr_index];
                        ++curr_index_cmds;
                        cout << " here " << endl;
                        ++curr_index;
                        }
                    }
                    //commands[curr_index_cmds + 1] = NULL;
                    //execute(commands);
                                   
                }
                else if(parsed_string.at(connector_index.at(a)) == "||"){               //get || to work 
                    for(int b = curr_index; b < connector_index.at(a); ++b){
                        cout << " here " << endl;
                        commands[curr_index_cmds] = parsed[curr_index];
                        ++curr_index_cmds;
                        ++curr_index;
                    }
                    commands[curr_index_cmds + 1] = NULL;
                    if(execute(commands) == false){
                        commands = NULL;
                        delete[]commands;
                        curr_index_cmds = 0;
                        if(a + 1 >= connector_index.size()){
                        ++a;
                        break;
                        }
                        ++curr_index;
                        char **commands = new char* [256];
                        for(int b = curr_index; b < connector_index.at(a); ++b){
                            commands[curr_index_cmds] = parsed[curr_index];
                            ++curr_index_cmds;
                            ++curr_index;
                        }
                        
                        execute(commands);
                    }
                    
                    else{
                        commands = NULL;
                        delete []commands;
                        curr_index_cmds = 0;
                        if(a + 1 < connector_index.size()){
                            ++a;
                            if(curr_index < connector_index.at(a)){ ++curr_index; }
                        }
                 }
                    
            }
               
            else if(parsed_string.at(connector_index.at(a)) == "#"){
                for(int b = curr_index; b < connector_index.at(a); ++b){
                    commands[curr_index_cmds] = parsed[curr_index];
                    ++curr_index_cmds;
                    ++curr_index;
                }
                commands[curr_index_cmds + 1] = NULL;
                execute(commands);
                delete[] commands;
                break;
            }
            
            if(connector_index.size() > 1){ 
                ++curr_index;
            }
            commands = NULL;
            delete []commands;
            curr_index_cmds = 0;
        } 
        if(parsed[curr_index] != NULL){
            char **commands = new char* [256];
            for(unsigned int b = curr_index; parsed[curr_index] != NULL; ++b){
               commands[curr_index_cmds] = parsed[curr_index];
              ++curr_index_cmds;
             ++curr_index;
            }
            commands[curr_index_cmds + 1] = NULL;
            execute(commands);
            delete []commands;
            
        }
        break;
        //delete []commands;
        delete []parsed;
    }

    //delete []commands;
    return 0;
}

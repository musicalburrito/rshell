#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>
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

void execute(char **cstr){                    //execute function

    int status=0;                               
    pid_t pid = fork();                        

    if(pid < 0){                                 //for fork error
       perror("fork error");                        //output error
       exit(-1);
    }
    else if(pid == 0){                          //for child
        wait(status);                               //wait for process
    }
    else{                                       //for parent
        execvp(cstr[0], cstr);                      //execute command
    }

    return;    

} 


int main(){
    char token[256];                        //array to input command line
    cout << "$ ";                           //command prompt                  
    cin.getline(token,256);                 //get user input

    string ex(token);                       //checks if exit
    if(ex == "exit"){
        cout << "Exiting shell" << endl;
    }

    char **parsed = new char*[256];         //create new array for parsed cmd  
    parse(parsed,token);                    //commence parsing

    execute(parsed);                        //execute what's in the array
    /*                                      //for checking what's in the array
    for(int j = 0; j < 256; ++j){
        cout << parsed[j] << ' ';
    }
    */

   
    return 0;
}

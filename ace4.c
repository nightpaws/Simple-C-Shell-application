/*
  main.c
  ACE4

  Created by Nightpaws on 03/02/2014.
  Copyright (c) 2014 Nightpaws. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ace4.h"

bool input_handler() {
    bool response = false;
    
    char input[inputval];
    printf(">");
    fgets(input, in_size, stdin);

    printf("User Input: %s\n",input);
    if(strcmp("exit\n",input)){
        response = true;
        printf("\n response is %d",response);
    }
    
    return response;
}



int main(int argc, char *argv[])
{
    printf("Simple Shell\n");
    printf("Created by Nightpaws on 03/02/2014\n");
    printf("Copyright (c) 2014 Nightpaws. All rights reserved.\n\n");
    
    
    while (input_handler()==true){}
    
        
    printf("\n\nTerminated Execution.\n\n");
    
    return 0;
    
    
    
//    char *get_line (char *string, size_t n, FILE *f);
//    {
//        char *p = fgets (string, n, f); //p = fgets (line, BUFFER_LENGTH, stdin);
//        
//        if (p != NULL) {
//            size_t last = strlen(string) - 1;
//            
//            if (string[last] == '\n') string[last] = '\0';
//        }
//        return p;
//    }
//    Find user home directory from the environment
//    Set current working directory to user home directory
//    Keep original path
//    Load
//    aliases
//    Load history
//    Do while shell has not terminated
//        Display prompt
//        Read and parse user input
//        If input is a history invocation then retrieve command from history
//        Else add command to history
//        If input is an alias then replace the alias with the origin
//        al command
//        If command is built
//        -
//        in invoke appropriate function
//        Else execute command as an external process
//        End while
//            Save history
//            Save aliases
//            Restore original path
//            Exit
    

}


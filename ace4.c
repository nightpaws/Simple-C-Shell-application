/* Version History =====================================================================
 * V0.1  07/02/2014 This is the first version of our program. Currently, we can take an
 *                  input, we have an indicator icon “>” and can exit the program with
 *                  “exit”.
 *                  Ctrl+d exit remains to be implemented, as does strtok() tokenising, and
 *                  input validation.
 *
 * v0.2 13/02/2014 The structure of the input handler function has been altered to now
 *                  use a while loop. Copyright has been changed from default values from
 *                  Xcode to reflecting the group name. Initially this while loop used
 *                  multiple if>else if statements, however it now descends with break
 *                  lines when an exit command is triggered. The boolean value for response
 *                  has been renamed terminate to improve readability. If terminate is true,
 *                  then the input handler function begins termination.
 *
 * v0.3 19/02/2014 This version has a functional tokenizer and accounts for all the required
 *                  token types. It can handle up to 512 characters however it behaves in
 *                  a strange way after 512 characters and outputs a second \n output if the
 *                  512 boundary is exceeded.
 * ====================================================================================*/

/*
 main.c
 ACE4 v0.3
 
 Created by Group 6 on 19/02/2014.
 Copyright (c) 2014 Group 6. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ace4.h"


void command_selecter(char input){
    
    return;
}

void tokenizer(char* input){
    char array[512];
    printf("\nLENGTH: %lu\n",strlen(input));

    if(strlen(input)<=512){
        strcpy(array, input);
        strncpy(array, input, (sizeof(array) -1));
        char *token = array;
        char *pointr = input;
    
        while ((token = strtok(pointr, "<>| \t")) != NULL)
        {
            printf("token: '%s'\n", token);
            pointr = NULL;
        }
	return;
    }
    else
        printf("Invalid Input\n");
    return;
}



bool input_handler() {
    bool terminate = false;
    char input[inputval];
    
    while(terminate==false){
        printf(">");
        
        if((fgets(input, in_size, stdin)!=NULL)){
            /**remove the trailing newline*/
            printf("User untokenised input is: '%s'\n",input);
            /*If user enters "exit" then jump out */
            if(strcmp("exit",input)==false){
                break;
            }
            else{

            tokenizer(strtok(input,"\n"));
                
            }
            }
    else
        /*Jump out of while loop*/
            break;
    }
    terminate = true;
    return terminate;
}



int main(int argc, char *argv[])
{
    printf("Simple Shell v0.3\n");
    printf("Created by CS210 Group 6 on 19/02/2014\n");
    printf("Copyright (c) 2014 CS210 Group 6, Strathclyde University. All rights reserved.\n\n");
    
    
    while (input_handler()==false){}
    
    
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


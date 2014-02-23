/* Version History =====================================================================
* V0.1 07/02/2014 This is the first version of our program. Currently, we can take an
* input, we have an indicator icon “>” and can exit the program with
* “exit”.
* Ctrl+d exit remains to be implemented, as does strtok() tokenising, and
* input validation.
*
* v0.2 13/02/2014 The structure of the input handler function has been altered to now
* use a while loop. Copyright has been changed from default values from
* Xcode to reflecting the group name. Initially this while loop used
* multiple if>else if statements, however it now descends with break
* lines when an exit command is triggered. The boolean value for response
* has been renamed terminate to improve readability. If terminate is true,
* then the input handler function begins termination.
*
* v0.3 19/02/2014 This version has a functional tokenizer and accounts for all the required
* token types. It can handle up to 512 characters however it behaves in
* a strange way after 512 characters and outputs a second \n output if the
* 512 boundary is exceeded.
* 
*
* v0.4 23/02/2014 Tokenizer now stores values into an array rather
* than simply printing them out, command_selector now contains a simple 
* while loop showing the values being printer out so we can be sure 
* that the values are being stored in the correct locations. It 
* currently ontains commented out code showing how we plan to implement 
* command selection but this doesn't work currently.
* ====================================================================================*/

/*
main.c
ACE4 v0.4
Created by Group 6 on 19/02/2014.
Copyright (c) 2014 Group 6. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ace4.h"
char *array[max_args][max_chars];
int ntokens;
/*
void cd(char tokens[max_args]){
    printf("cd has been selected\n");
    return;
}

void pwd(char tokens[max_args]){
    printf("pwd has been selected\n");
    return;
}

void getpath(char tokens[max_args]){
    printf("getpath has been selected\n");
    return;
}

void setpath(char tokens[max_args]){
    printf("setpath has been selected\n");
    return;
}

void history(char tokens[max_args]){
    printf("history has been selected\n");
    return;
}

void runlast(char tokens[max_args]){
    // TODO add in special case for !! commands
    printf("runlast has been selected\n");
    return;
}

void alias(char tokens[max_args]){
    printf("alias has been selected\n");
    return;
}

void printalias(){
    printf("printalias has been selected\n");
    return;
}

void unalias(char tokens[max_args]){
    printf("unalias has been selected\n");
    return;
}
*/




void command_selecter(){
   /* if(strcmp("cd",array[0])==true)
    {
        cd(array[1]);
    }
    else if(strcmp("pwd",array[0])==true)
    {
        pwd(array[1]);
    }
    else if(strcmp("getpath",array[0])==true)
    {
        getpath(array[0]);
    }
    else if(strcmp("setpath",array[0])==true)
    {
        setpath(array[0]);
    }
    else if(strcmp("history",array[0])==true)
    {
        history(array[0]);
    }
    else if(strcmp("!",array[0])==true)
    {
        runlast(array[0]);
    }
    else if(strcmp("alias",array[0])==true)
    {
        if(array[0] != NULL){
            alias(*array);
        } else {
            printalias();
        }
    }
    else if(strcmp("unalias",array[0])==true)
    {
        unalias(array[0]);
    }
    else {
         Just run the command and catch the error 
        
    }
*/


    int i = 0;
    while(i<ntokens){
    printf("Token: '%s', counter is %d\n",array[i], i);
    i = i+1;
	}
    return;
}

void tokenizer(char *input){
    printf("\nLENGTH: %lu\n",strlen(input));
    strtok(input,"\n");
    char *token;
    char *pointr = input;
    int i = 0;
    while ((token = strtok(pointr, "<>| \t")) != NULL)
    {
	strcpy(array[i], token);
        pointr = NULL;
	ntokens = ntokens + 1;
	i = i + 1;
        }
    return;
}



bool input_handler() {
    bool terminate = false;
    char input[inputval];
    
    while(terminate==false){
        printf(">");
        
        if((fgets(input, in_size, stdin)!=NULL)){
            strtok(input,"\n");
            printf("User untokenised input is: '%s'\n",input);
            /*If user enters "exit" then jump out */
            if(strcmp("exit",input)==false){
                break;
            }
            else{
                /**remove the trailing newline*/
	    ntokens = 0;
            tokenizer(input);
            command_selecter();
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
    
    
    
// char *get_line (char *string, size_t n, FILE *f);
// {
// char *p = fgets (string, n, f); //p = fgets (line, BUFFER_LENGTH, stdin);
//
// if (p != NULL) {
// size_t last = strlen(string) - 1;
//
// if (string[last] == '\n') string[last] = '\0';
// }
// return p;
// }
// Find user home directory from the environment
// Set current working directory to user home directory
// Keep original path
// Load
// aliases
// Load history
// Do while shell has not terminated
// Display prompt
// Read and parse user input
// If input is a history invocation then retrieve command from history
// Else add command to history
// If input is an alias then replace the alias with the origin
// al command
// If command is built
// -
// in invoke appropriate function
// Else execute command as an external process
// End while
// Save history
// Save aliases
// Restore original path
// Exit
    

}

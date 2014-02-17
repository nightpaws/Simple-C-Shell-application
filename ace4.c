/*
  main.c
  ACE4
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
 * ====================================================================================*/

  Created by Me, Myself and I on 03/02/2014.
  Copyright (c) 2014 Me, Myself and I. All rights reserved.
*/
/*
 main.c
 ACE4 v0.2
 
 Created by Group 6 on 03/02/2014.
 Copyright (c) 2014 Group 6. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ace4.h"
void command_selecter(char input){

return;
}

void tokenizer(char* input){
    char array[256];
	strcpy(array, input);
	strncpy(array, input, (sizeof(array) +1));
    char *token = array;
    char *pointr = input;

    while ((token = strtok(pointr, " ")) != NULL)
    {
        printf("%s\n", token);
        pointr = NULL;
    }
	return;
}

bool input_handler() {
    bool response = false;
    char input[inputval];
    printf(">");
    fgets(input, in_size, stdin);
	tokenizer(input);
	printf("User Input: %s\n",input);
	if(strcmp("exit\n",input)){
		response = true;
		printf("\n response is printing strange here for some reason %d",response);
	}
    
    return response;
}



int main(int argc, char *argv[])
{
    printf("Simple Shell\n");
    printf("Simple Shell v0.2\n");
    printf("Created by CS210 Group 6 on 03/02/2014\n");
    printf("Copyright (c) 2014 CS210 Group 6, Strathclyde University. All rights reserved.\n\n");
    
    
    while (input_handler()==true){}
    
        
    printf("\n\nTerminated Execution.\n\n");
    
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


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
*
* v0.5 06/03/2014 In this version we have refactored our code substantially. The main
* method now contains the entirety of the input handler class which has been removed.
* The global array we were using has now been moved into the main function, and parameter
* passing has been completely redone to allow methods to pass parameters in and out of the
* main function rather than through a complicated heirarchy of processes that was causing
* confusion and unexpected outputs. Fork() has been added and the ability to handle
* external commands has been put in place by using the execvp() function.
* 
* v0.5.1 06/03/2014 Quick fix to handle empty inputs. If statement surrounding command
* selector to resolve (lldb) error. Added input to "Command not found" message.
*
* ====================================================================================*/

/*
main.c
ACE4 v0.6.1
Created by Group 6 on 06/03/2014.
Copyright (c) 2014 Group 6. All rights reserved.
*/
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <stdio.h> /* printf, perror */
#include <string.h>
#include <stdlib.h> /* exit */
#include <unistd.h> /* _exit, fork */
#include <errno.h>

#include "ace4.h" /*Our custom file*/

/* Avoid Global Variables*/


/*Functions to be called when called by the users
 input matching the name of the function. These will
 contain the code. */
void cd(char input[inputval],char *tokens[]){
//    char cwd[256]; /*current working directory*/
    if(tokens[1] == NULL){
	/*change directory to home*/
    	if(chdir(getenv("HOME")) == 0){}
        else{
		perror(getenv("HOME"));
        }
    }
    else if (tokens[2]!= NULL){
        printf("Too many parameters supplied\n");
    }
    else {
	/*change directory to user specified location*/
        if(chdir(tokens[1]) == 0){
//            printf("Successfully changed directory\n");
        }
        else
        {
            perror(input);
        }
    }
    
}

void pwd(char *tokens[]){
        char cwd[256]; /*current working directory*/
    if (getcwd(cwd, sizeof(cwd)) == NULL){
            perror("getcwd() error");
    }
    else if (tokens[1]!= NULL){
        printf("Cannot use parameters\n");
    }
    else
        printf("current working directory is: %s\n", cwd);
    return;
}

void getpath(char *tokens[]){
    
    if (tokens[1]!= NULL){
        printf("getpath does not take parameters\n");
    }
    else
    printf("The current path is: %s\n",getenv("PATH"));
    

    
    
    return;
}

void setpath(char *tokens[]){
    if(tokens[1] != NULL){
	if(tokens[2] == NULL){
	    	printf("New path will be : %s\n",tokens[1]);
                if(setenv("PATH",tokens[1],1) == 0){
			printf("Successfully changed path\n");
			}
                else{
			printf("Invalid path specified\n");
			}
	}
	else{
	printf("Error: You have too many parameters\n");
	}
    }
    else{
	printf("Error: You need to include a path\n");
    }
    return;
}

void history(char *tokens[], char *history[]){
    int i = 0;
    if(history[i] == 0){
	printf("History is empty\n");
    }
    else{
	    while(history[i] != 0){
		printf("%d. %s\n",(i+1),history[i]);
		i = i + 1;
		if(i == max_hist){
			break;
		}
    	}
    }
    return;
}

void runlast(char *tokens[max_args], char *history[max_hist]){
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

void command_selecter(char input[inputval], char *tokenArray[max_args], char *histArray[max_hist]){

    if(strcmp("cd",tokenArray[0])==true)
    {
        cd(input,tokenArray);
    }
    else if(strcmp("pwd",tokenArray[0])==true)
    {
        pwd(tokenArray);
    }
    else if(strcmp("getpath",tokenArray[0])==true)
    {
        getpath(tokenArray);
    }
    else if(strcmp("setpath",tokenArray[0])==true)
    {
        setpath(tokenArray);
    }
    else if(strcmp("history",tokenArray[0])==true)
    {
        history(tokenArray,histArray);
    }
    else if(strcmp("!!",tokenArray[0])==true)
    {
        runlast(tokenArray,histArray);
    }
    else if(strcmp("alias",tokenArray[0])==true)
    {
        /*Code is non functional */
        /* if(array[0] != NULL){
            alias(tokenArray);
        } else {
            printalias();
        } */
    }
    else if(strcmp("unalias",tokenArray[0])==true)
    {
        unalias(tokenArray[0]);
    }
    else {
        pid_t pid;
        pid = fork();
        
        if (pid == -1) {
            /* If the fork() returns -1, an error has occurred. */
            perror("Failed to fork process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            /* If fork() returns 0, we are in the child process. */
            if(execvp(tokenArray[0],tokenArray) == -1 ){
                printf("%s: Command not found\n",tokenArray[0]);
            }
            exit(2);	/* execl() failed */
        }
        else {
           /* When fork() is positive. We're in the parent process */
            int status;
            (void)waitpid(pid, &status, 0);
            /* return value is PID of new child process */
        }
    }
}

    
char** tokenizer(char input[inputval], char *array[max_args]){
       char *inputstrings; /*current value to be tokenised*/
       int i = 0; /*tokeniser*/
        
        /*take in the input, tokenise and store first 
         tokenised value in the array*/
        inputstrings = strtok(input, "<>| \n\t");
        array[0] = inputstrings;
        
        /*Whilst not the end of the file and input isn't null, take
         in the input, tokenise and store first tokenised value
         in the array*/
        while(inputstrings != NULL && !feof(stdin)){
            i++;
            inputstrings = strtok(NULL,"<>| \n\t");
            array[i] = inputstrings;
        }
        return array;
}

int main(int argc, char *argv[])
{
    printf("Simple Shell v0.5.2\n");
    printf("Created by CS210 Group 6 on 06/03/2014\n");
    printf("Copyright (c) 2014 CS210 Group 6, Strathclyde University. All rights reserved.\n\n");
    char *history[max_hist] = {0}; /* History array */
    int histcounter = 0;
    char *array[max_args];/* Size 50 */
    bool terminate = false; /* Always false */
    char input[inputval];    /* Size 512 */
    char *originalPath; /* To hold current directory at beginning of execution */
    char cwd[256];
    
    /* Store the original path*/
    originalPath = getenv("PATH");
    
    /* Set working directory to the home folder*/
    chdir(getenv("HOME"));
    
    
    /* Infinite Loop until highest break is reached*/
    do {
        printf("%s >",getcwd(cwd, sizeof(cwd)));
        
        /* get the input and if it is not null tokenise it */
        if((fgets(input, in_size, stdin)!=NULL)){
            strtok(input,"\n");
            
            char inputunchanged[inputval];
	    int i;
            for (i=0;i<sizeof(input);i++){
                inputunchanged[i] = input[i];
            }
           
            /* If the input from the user is "exit" then
             begin termination of the program */
            if(strcmp("exit",input)==true){
                break;
            }
            else{
                if(strncmp("!", input, 1) != 0 && strncmp("history", input, 512) != 0 ){ 
		/* If this returns 0, the first char in the input is a ! or the input is "history" */
			history[histcounter] = strdup(input);
			histcounter = histcounter + 1;
			if(histcounter%20==0){
				histcounter = 0;
			}
		}
                else{
			if(strncmp("history", input, 512) != 0){
				int length = strlen(input);
				char *locstr = (char *) malloc(2);
				if (length > 1){
					strcat(locstr, &input[1]);
					int location = atoi(locstr);
					if(location>0 && location <21){
						location = location - 1;
						if(history[location] != NULL){
							strcpy(input,history[location]);
							printf("History command is: %s\n",input);
						}
						else{
							printf("There is no command in this array location\n");
						}
					}
					else{
						printf("The number following ! must be between 0 and 19\n");
					}
				}
				else{
					printf("Enter a number after ! to show the command you wish to run\n");
				}

			}			
                }
		tokenizer(input, array);
		if(array[0] !=NULL){
                	command_selecter(inputunchanged,array,history);
                }
            }
        }
        else
        /* Jump out of while loop*/
            break;
        
    } while (terminate ==false);
    /**getsetenv here and on exit*/
    setenv("PATH",originalPath,1);
    printf("Path on leaving program: %s\n",getenv("PATH"));
    printf("\n\nTerminated Execution.\n\n");
    return 0;
}

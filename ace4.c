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
ACE4 v0.6.5
Created by Group 6 on 02/04/2014.
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

struct alias{
    char alias;
    char command[inputval];
};

/*Functions to be called when called by the users
 input matching the name of the function. These will
 contain the code. */
void cd(char input[inputval],char *tokens[]){
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
                else{			printf("Invalid path specified\n");
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

void history(char *tokens[], char *history[], int histcounter){
    int j = 0;
    if(tokens[1] == 0){
    	if(history[0] == 0){
            printf("History is empty\n");
	    }
    	else{
            /* this for loop finds out where the latest addition to the array is */
		    int k = 0;
		    while(history[k] != 0){
                k++;
                if(k == (max_hist)){
                    break;
                }
		    }
		    
		    /*Prints out the recent history, prints most recent command as 1. least recent as higher number*/
		    while(history[j] != 0){
                printf("%d. %s\n",(k),history[j]);
                j++;
                k--;
                if(j == max_hist){
                    break;
                }
    		}
    	}
    }
    else{
        printf("History does not take parameters\n");
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

void command_selecter(char input[inputval], char *tokenArray[max_args], char *histArray[max_hist], int histcounter){

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
        history(tokenArray,histArray,histcounter);
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
    
    /*Restore history from file*/
    char *filename = strcat(getcwd(cwd,sizeof(cwd)),"/.hist_list");  /*Set history file to be from home directory*/
    
    FILE *fileread = fopen ( filename, "r" );
    if (!fileread==true)
    {
        char line [512];
        while ( (fgets ( line, sizeof line, fileread ) != NULL) && (histcounter < 20)) /* read a line */
        {
            history[histcounter] = strdup(strtok(line,"\n"));
            histcounter = (histcounter +1)%20;
        }
    }
    else
    {
        printf("No previous history exists, a new history will be created upon exit.");
    }
//    int j;
//    for (j = 0; j < 5; j++){
//        printf("%d %s \n", j, history[j]);
//    }
    fclose ( fileread );
    
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
                if(strstr(input,"\n")){
                }
                else{
                    /* If this returns 0, the first char in the input is a ! or the input is "history" */
                    if(strncmp("!", input, 1) != 0 && strncmp("history", input, 512) != 0 ){
                        
                        /*When array is full, moves everything in array one location down */
                        if(histcounter == max_hist){
                            int i = 0;
                            while(i<(histcounter-1)){
                                history[i] = history[i+1];
                                i++;
                            }
                            history[(max_hist-1)] = strdup(input);
                        }
                        else{
                            history[histcounter] = strdup(input);
                            histcounter = histcounter + 1;
                        }
                    }
                    else{
                        /*Checks if input is to run last command */
                        if(strncmp("!!", input, 512) == 0){
                            if(history[0] != 0){
                                if(histcounter == 0){
                                    strcpy(input,history[19]);
                                }
                                else{
                                    strcpy(input,history[histcounter-1]);
                                }
                            }
                            else{
                                printf("There is no history to run\n");
                            }
                        }
                        else{
                            long length = strlen(input);
                            char *locstr = (char *) malloc(2);
                            if (length > 1){
                                strcat(locstr, &input[1]); /*Removes ! from input to get command number */
                                int location = atoi(locstr); /*Converts char to int */
                                if(location>0 && location <21){
                                    location = location - 1;
                                    if(history[location] != NULL){
                                        /*Because the history command prints out from most to last recent, this converts the users 
                                         input into an array location, as !1 would be location in an full array */
                                        if((histcounter-location) < 0){
                                            location = (max_hist - (histcounter-(location+1)));
                                        }
                                        else{
                                            location = (histcounter-(location+1));
                                        }
                                        strcpy(input,history[location]);
                                        printf("History command is: %s\n",input);
                                    }
                                    else{
                                        printf("There is no command in this array location\n");
                                    }
                                }
                                else{
                                    printf("The character following ! must be a number between 1 and 20\n");
                                }
                            }
                        }
                    }
                }
                tokenizer(input, array);
                if(array[0] !=NULL){
                	command_selecter(inputunchanged,array,history,histcounter);
                }
            }
        }
        else
        /* Jump out of while loop*/
            break;
        
    } while (terminate ==false);
    
    /*Write out history to file*/
    filename = strcat(filename,"/.hist_list");
    FILE *filewrite = fopen ( filename, "w" );
    if (filewrite == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    int i = 0;
    while(history[i] != 0){
        fprintf(filewrite,"%s\n",history[i]);
        i = (i + 1)%20;
        if(i == max_hist){
            break;
        }
    }
    fclose ( filewrite );
    
    /**getsetenv here and on exit*/
    setenv("PATH",originalPath,1);
    printf("\n\nPath on leaving program: %s\n",getenv("PATH"));
    printf("\n\nTerminated Execution.\n\n");
    return 0;
}

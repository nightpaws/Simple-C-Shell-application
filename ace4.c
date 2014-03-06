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
ACE4 v0.5.2
Created by Group 6 on 06/03/2014.
Copyright (c) 2014 Group 6. All rights reserved.
*/
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <stdio.h> /* printf, perror */
#include <string.h>
#include <stdlib.h> /* exit */
#include <unistd.h> /* _exit, fork */

#include "ace4.h" /*Our custom file*/

/* Avoid Global Variables*/


/*Functions to be called when called by the users
 input matching the name of the function. These will
 contain the code. */
void cd(char tokens[max_args]){
    printf("cd has been selected\n");
}

void pwd(char tokens[max_args]){
    char cwd[256]; /*current working directory*/
        if (getcwd(cwd, sizeof(cwd)) == NULL)
            perror("getcwd() error");
        else
            printf("current working directory is: %s\n", cwd);
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

void command_selecter(char *tokenArray[max_args]){

    if(strcmp("cd",tokenArray[0])==true)
    {
        cd(tokenArray[0]);
    }
    else if(strcmp("pwd",tokenArray[0])==true)
    {
        pwd(tokenArray[0]);
    }
    else if(strcmp("getpath",tokenArray[0])==true)
    {
        getpath(tokenArray[0]);
    }
    else if(strcmp("setpath",tokenArray[0])==true)
    {
        setpath(tokenArray[0]);
    }
    else if(strcmp("history",tokenArray[0])==true)
    {
        history(tokenArray[0]);
    }
    else if(strcmp("!",tokenArray[0])==true)
    {
        runlast(tokenArray[0]);
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
    char *array[max_args];/* size 50 */
    bool terminate = false; /* Always false */
    char input[inputval];/* size 512 */
    char *originalPath; /* to hold current directory at beginning of execution */
    
    /* Store the original path*/
    originalPath = getenv("PATH");
    printf("Original path is: %s\n",originalPath); /*testing line. Delete when done*/
    
    /* Set working directory to the home folder*/
    chdir(getenv("HOME"));
    
    
    /* Infinite Loop until highest break is reached*/
    do {
        printf(">");
        
        /* get the input and if it is not null tokenise it */
        if((fgets(input, in_size, stdin)!=NULL)){
            strtok(input,"\n");
            /* If the input from the user is "exit" then
             begin termination of the program */
            if(strcmp("exit",input)==true){
                break;
            }
            else{
                tokenizer(input, array);
                if(array[0] !=NULL){
                command_selecter(array);
                }
            }
        }
        else
        /* Jump out of while loop*/
            break;

    } while (terminate ==false);
/**getsetenv here and on exit*/
    setenv("HOME",originalPath,1);
    printf("\n\nTerminated Execution.\n\n");
    return 0;
}

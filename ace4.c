/***************************************************************************************************************
 *
 * Filename: ace4.c
 *
 * Synopsis: Simple Shell Application
 *
 * This is an implementation of ACE 4, a Simple Linux Shell application which
 * allows the user to perform various built in tasks whilst also allowing the execution of external
 * system commands where none have been coded in the application. The program prompts the user for
 * an input, then checks the history to see if they are invoking a previous command. It is then
 * compared against the list of aliases to check if the command should execute a different command.
 * After this, the command is tokenised and passed to the command selector which either executes
 * the internal command if one exists, or fork a process to run the command externally. The program
 * then loops around to prompt for further input until the user types 'exit' or presses ctrl+d.
 *
 * GitHub Repository: https://github.com/adamus1red/scaling-octo-avenger
 * 
 * Authors:
 *      Craig Morrison, Reg no: 201247913
 *      Stewart Key, Reg no: 201240385
 *      Adam McGhie, Reg no: 201240207
 *      Liam Diamond, Reg no: 201210681
 *
 * Group:
 *      Group 6
 *
 * Promise: I confirm that this submission is all my own work.
 *
 *            (Craig Morrison)	__________________________________________
 *               (Stewart Key)	__________________________________________
 *               (Adam McGhie)	__________________________________________
 *              (Liam Diamond)	__________________________________________
 *
 * Version: See VERSION below
 *
 **************************************************************************************************************/

/* Version History =============================================================================================
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
* v0.2.1 19/02/2014 This version has a functional tokenizer and accounts for all the required
* token types. It can handle up to 512 characters however it behaves in
* a strange way after 512 characters and outputs a second \n output if the
* 512 boundary is exceeded.
*
* v0.2.2 23/02/2014 Tokenizer now stores values into an array rather
* than simply printing them out, command_selector now contains a simple 
* while loop showing the values being printer out so we can be sure 
* that the values are being stored in the correct locations. It 
* currently ontains commented out code showing how we plan to implement 
* command selection but this doesn't work currently.
*
* v0.2.3 26/02/2014 Our boolean definition has been reversed in order to comply with the
* logic of /most/ C functions and return values. We also rectified the mistype of max_chars
* which had been given the value of 513 instead of 512. the tokenArray was incorrectly
* initialised as an array of pointers which has been fixed and all references have also been rectified.
*
* v0.2.4 06/03/2014 In this version we have refactored our code substantially. The main
* method now contains the entirety of the input handler class which has been removed.
* The global array we were using has now been moved into the main function, and parameter
* passing has been completely redone to allow methods to pass parameters in and out of the
* main function rather than through a complicated heirarchy of processes that was causing
* confusion and unexpected outputs. Fork() has been added and the ability to handle
* external commands has been put in place by using the execvp() function.
* 
* v0.2.5 06/03/2014 Quick fix to handle empty inputs. If statement surrounding command
* selector to resolve (lldb) debugger error. Added input to "Command not found" message. The parameters
* used to tokenise have been readded as they were removed earlier in error. ("<>| \n \t"). Handling
* of NULL Strings has also been included in the Command Selector.
* 
* v0.2.6 06/03/2014 Internal command pwd has been introduced along with the ability to store the
* original path.
*
* v0.2.6.5 06/03/2014 Reversion of incorrect GitHub commit. Introduced lots of conflicting information,
* duplicate code and compilation errors due to user error. Rectified by reuploading v0.2.5 then
* manually transferring changes from v0.2.6 into this code.
*
* v0.3 6/03/2014 Setenv() is now used to set and restore the users path variable upon
* launch and exit of the application.
*
* v0.3.1 12/03/2014 Change Directory is now operational although code is preventing '.' and '..'
* from working. pwd, setpath and getpath have been tidied up and now work properly. The code was
* almost the same as the initial get and closing set.
*
* v0.3.5 13/03/2014 Stage 3's basic functionality is now all in place and pwd has been altered
* to refuse additional parameters.
*
* v0.4.0 13/03/2014 A quick change has been made to return errors to the user when too many/few
* parameters are supplied to setpath/getpath/cd and pwd.
*
* v0.4.5 18/04/2014 cd has been altered in order to better handle the array. The function now
* takes the whole array as input in order to prevent extraneous input, resulting in less unneeded code.
*
* v0.5 20/03/2014 perror() has been used to replace errors where the system encounters an error rather than
* us wanting to restrict the user. Unnecessary debug code and commentary has been removed and the main
* method has been rewritten from scratch to allow for the history to be implemented. History size has been added
* to the header file. The '>' input prompt now includes the users current working directory to look more like a
* standard Console Shell.
*
* v0.6 27/03/2014 History now stores the list of commands in an array and allows execution of these.
* A bug #27 has been identified where 8 entries in console are needed before the history will begin
* to allow execution however. This will be addressed in the next commit. Array is currently circular
* with content being replaced from element 0 when it is full.
*
* v0.7.0 31/03/2014 Removed lots of unneeded commentary and added a struct for alias to use. History
* has been altered to include a counter of positions in history, and the ability to load and
* save from a hidden file called .hist_list has been implemented. This file is currently
* stored in the /tmp directory.
*
* v0.7.3 02/04/2014 .hist_list is now stored in the users home directory instead of /tmp .
* this change allows for the history to be permanently preserved and not deleted when /tmp is
* purged.
*
* v0.8 09/04/2014 alias struct has been removed as we have decided to use a 2 dimensional array.
* alias #22 and unalias #20 have been implemented and are now functional allowing adding and removing
* of aliases. Invoking results in a Segmentation fault. Testing of full array has been done by pre-populating
* alias list. 
*
* v0.8.5 09/04/2014 Parameters of aliasing have been altered to better fit the requirements of the specification.
* Bug #27 had been resolve but has recurred in this version. Bug #28 (Segmentation Fault) in history has been
* rectified. Excess spacing between functions was found to be the cause. Aliases can now be invoked and listed.
* Test array code has been removed. Spelling misakes have also been addressed. Counters have been tided to be
* easier to read. (Counter = counter +1 changed to counter++ etc).
*
* v0.8.8 14/04/2014 Refactored code to remove all non C90 -Wpedantic code and commentary. History and aliasing
* now have their own functions with necessary parameters passed to them. Save history has also been moved
* to a separate function and runlast has been removed from the code altogether as it is already implemented in
* history. Version history has been updated and internal commentary is now up-to-date. 
*
* ==============================================================================================================*/

/*
main.c
ACE4 v0.8.8
Created by Group 6 on 14/04/2014.
Copyright (c) 2014 Group 6. All rights reserved.
*/

/*Included files which are required for the Simple Shell program to be able to run */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <stdio.h> /* printf, perror */
#include <string.h>
#include <stdlib.h> /* exit */
#include <unistd.h> /* _exit, fork */
#include <errno.h> /* perror */
#include "ace4.h" /*ACE4 header file with system critical values.*/


/* On termination of the program the history is written out to a specified text file.
 This function performs the write operation. */
void writehistory(char* filename, char *history[max_hist]){
    /* Initialise local variables and open the file in purge & write mode. */
    FILE *filewrite;
    int i;
    filename = strcat(filename,"/.hist_list");
    filewrite = fopen ( filename, "w" );
    if (filewrite == NULL)
    {
        /* Inform the user if the file failed to open
         (due to permission errors or otherwise), and terminate. */
        printf("Error opening file!\n");
        exit(1);
    }
    /*Initialise counter */
    i = 0;
    
    while(history[i] != 0){
        /*Print each line of history into the text file, then 
         close the reader when done */
        fprintf(filewrite,"%s\n",history[i]);
        i++;
        if(i == max_hist){
            break;
        }
    }
    fclose ( filewrite );
}

/*This function is used to check input against the history and handles input such as '!!' and
 '!<no>' which are required to re-run previously executed commands from history.*/
int historycheck(char input[inputval], int histcounter, char *history[max_hist]){
    /* This if statement prevents inputs which are line breaks being entered into the history. */
    if(strstr(input,"\n")){
    }
    else{
        /* If the program passes this if statement, the first char in the input is a ! or the input is "history" */
        if(strncmp("!", input, 1) != 0 && strncmp("history", input, 512) != 0 ){
            
            /* When array is full, move each element in the array down one location. */
            if(histcounter == max_hist){
                int i = 0;
                while(i<(histcounter-1)){
                    history[i] = history[i+1];
                    i++;
                }
                /* Add the new element to history. */
                history[(max_hist-1)] = strdup(input);
            }
            else{
                /* Add the new element to history straight away. Then increment counter */
                history[histcounter] = strdup(input);
                histcounter = histcounter + 1;
            }
        }
        else{
            /* Checks if input is to run the last command. (!!) If so, then execute it,
             or display an error if there is no history to run. */
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
                if (length > 1){
                    int location = atoi(&input[1]); /* Converts char to int. */
                    if(location>0 && location <21){
                        location = location - 1;
                        if(history[location] != NULL){
                            /* Because the history command prints out from most to last recent, this converts the users
                             input into an array location, as !1 would be location in an full array. */
                            if((histcounter-location) < 0){
                                location = (max_hist - (histcounter-(location+1)));
                            }
                            else{
                                location = (histcounter-(location+1));
                            }
                            /* The command from history is copied into input overwriting the previous command.
                             The command is displayed before it runs. */
                            strcpy(input,history[location]);
                            printf("%s\n",input);
                        }
                    }
                    else{
                        if(location != 0){
                            /*If the user enters a number outwith the range then they are
                              prompted to change their number */
                            printf("The character following ! must be a number between 1 and 20 to invoke a history command\n");
                        }
                    }
                }
            }
        }
    }
    
    return histcounter;
}


/* The following functions will be called by the internal command selector. Each will execute accordingly and return to the main method once completed */

/* This function checks to see if the input value it is provided with is containted within the list of aliases
 stored in the program. If they exist then the provided input is replaced with the alias value.*/
void checkalias(char input[inputval],char *alias[max_alias][2]){
    int i;
    for(i = 0;i<10;i++){
        if(alias[i][0]!=NULL){
            if(strcmp(input,alias[i][0])==0){
                /* If the command is found in aliases then copy
                 the aliased command in place of the input. */
                strcpy(input, alias[i][1]);
                break;
            }
        }
    }
}


/* Change Directory allows naviagtion of the computer system by providing the function with folder names and
 a select few additional commands such as cd with no parameters and 'cd ..' to navigate up one layer in the system. */
void cd(char input[inputval],char *tokens[]){
    if(tokens[1] == NULL){
	/* Change directory to the users Home directory, or display an error if this fails.*/
    	if(chdir(getenv("HOME")) == 0){}
        else{
		perror(getenv("HOME"));
        }
    }
    else if (tokens[2]!= NULL){ /*Warn the user if too many parameters are given and stop executing the cd command*/
        printf("Too many parameters supplied\n");
    }
    else {
	/* Change directory to user specified location. Display an error if this does not succeed. */
        if(chdir(tokens[1]) == 0){
        }
        else
        {
            perror(input);
        }
    }
    
}


/*Attempts to obtain the current working directory from the system and stores it in a character array. This
 function does not take parameters and informs the user should they attempt to use them. When invoked
 it displays the current working directory. */
void pwd(char *tokens[]){
        char cwd[256]; /* Current working directory. */
    if (getcwd(cwd, sizeof(cwd)) == NULL){ /* If unable to get cwd display an error */
            perror("getcwd() error");
    }
    else if (tokens[1]!= NULL){
        printf("Cannot use parameters\n");
    }
    else
        printf("current working directory is: %s\n", cwd);
    return;
}


/* A short method to get and display the current environment to the user with a check 
 to prevent use of unnecessary parameters. */
void getpath(char *tokens[]){
    
    if (tokens[1]!= NULL){
        printf("getpath does not take parameters\n");
    }
    else
    printf("The current path is: %s\n",getenv("PATH"));
    return;
}


/* This function sets a new environment for the application to use. It includes checks to prevent excessive
 parameter usage and requires a single path name to be input. */
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


/* History displays to the user the last 20 commands they entered with numbering next to each element.
 By typing ! and the number in the form !<no> the user can execute these commands. This function 
 however exists solely to display those commands to the user. */
void history(char *tokens[], char *history[], int histcounter){
    int j = 0;
    if(tokens[1] == 0){
    	if(history[0] == 0){
            printf("History is empty\n");
	    }
    	else{
            /* This for loop finds out where the latest addition to the array is. */
		    int k = 0;
		    while(history[k] != 0){
                k++;
                if(k == (max_hist)){
                    break;
                }
		    }
		    
		    /* Prints out the recent history, with the most recent command as element 1. Less recent as incrementations of 1. */
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
        /*If history is given parameters it will not execute 
         and instead the user is prompted not to give such input */
        printf("History does not take parameters\n");
    }	
    return;
}


/* The alias function allows the user to assign command names of their own to operations to make
 them less time consuming when used repeatedly. This is especially useful when dealing with long commands
 with lots of parameters which can be shortened to a single word. This function takes two inputs but an unlimited
 number of parameters may be applied to the second parameter up to the character limit specified in the ace4.h file. */

void alias(char *tokens[max_args], char *alias[max_alias][2]){
    /* Partially initialise local variables. */
	int i;
	int nullCounter = 0;
    char* command;
    char command2[512] = "";
    int tokensCounter;
    int index;
    bool exists;
    
    /* Works out the number of null elements in the alias array. */
	for (i = 0; i < max_alias; i++){
		if(alias[i][0] == NULL){
			nullCounter = nullCounter + 1;
		}
	}
    
    /* If only 'alias' is entered the program responds with a list of aliases, or outputs a message explianing no aliases exist yet. */
	if (tokens[1] == NULL){
		if(nullCounter == max_alias){
			printf("There are no aliases to list\n");
		}
		else{
			for (i = 0; (i < (max_alias-nullCounter)); i++){
				printf("%s\t%s \n", alias[i][0], alias[i][1]);
			}
		}
		return;
	}
	else{
        /* If no command to alias is given then a message is shown to the user prompting for the additional paramater of a command */
		if(tokens[2] == NULL){
			printf("Error: Incorrect parameters provided to alias. Specify <command2>\n");
			return;
		}
        
        /* Variables are now fully initialised for use in processing. */
		command = tokens[1];
		tokensCounter = 0;
		index = 0;
		i = 0;
		exists = false;
		
        /* The number of tokens in the array is counted. */
		while (tokens[tokensCounter] != NULL){
			tokensCounter ++;
		}
		
        /* Concatenates all the tokens (except 'alias' and <command1>) to construct the command to be stored. */
		for (index = 2; index < tokensCounter; index++){
			strcat(command2, tokens[index]);
			strcat(command2, " ");
		}
        
        /* Appends a null character to the end of the string to allow chosen commands to
         appear the same as a normal command when called. */
		strcat(command2, "\0");
		
        /*Check the list of existing aliases. If the alias already exists, then overwrite it. */
		for (i = 0; (i < (max_alias-nullCounter)); i++){
				if(strcmp(command, alias[i][0]) == true){
					printf("Alias already exists. Overwriting.\n");
					alias[i][1] =strdup(command2);
					exists = true;
				}
		}
        
        /* If the alias does not exist and there is no room to add one, then inform the user of the failure. */
		if((nullCounter == 0) && (exists == false)){
			printf("No more aliases can be added \n");
		}
		else{
            /* Otherwise add the new alias to the Array if it does not already exist. */
			if ((exists == false)&&(nullCounter != 0)){
				alias[max_alias-nullCounter][0] =strdup(command);
				alias[max_alias-nullCounter][1] =strdup(command2);
			}
		}
	}
    return;
}


/* Unalias attempts to remove the alias passed to it from the list of aliases. It rejects excessive
 parameters or notifies if too few are provided. A correct command should be of the form 'unalias <alias> */
void unalias(char *tokens[max_args], char *alias[max_alias][2]){
    int i;
	int index;
    char* command;
    bool found;
    
    /* Perform simple validation of parameters. */
	if (tokens[1] == NULL){
		printf("Error: No alias provided. \n");
		return;
	}
	
    if(tokens[2]!=NULL){
        printf("Error: Too many values provided. \n");
		return;
    }
    
    /* The command that is to be unaliased is assigned a to the command value.
     The boolean value found is also initialised here. */
	command = tokens[1];
	found = false;
    
    /* The program searches throguh the array to find the alias stated. If it is found then both
     the alias and it's target are reset to NULL values and the found indicator is set to true with
     a pointer to the, now empty, alias stored in memory as 'i'. */
	for (i = 0; i < max_alias; i++){
		if (alias[i][0] != NULL){
			if(strcmp(command, alias[i][0]) == true){
				alias[i][0] = NULL;
				alias[i][1] = NULL;
				index = i;
				found = true;
			}
		}

	}
    
    /*If the found indicator has not been triggered then the user is informed that their alias was not found,
     and returned to the main program, otherwise the alias list needs to be updated to remove the space
     created by the removed element. */
	if (found == false){
		printf("Error: The alias does not exist. \n");
		return;
	}
	else{
		while(index<(max_alias-1)){					
			alias[index][0] = alias[index+1][0];		/* shift array so there are no gaps */
			alias[index][1] = alias[index+1][1];
			index++;
		}
		alias[max_alias-1][0] = NULL;					
		alias[max_alias-1][1] = NULL;
	}
    return;
}

/*The following two functions, Command_Selector and tokenizer are two critical functions required for any and all functionality */

/* The Command Selector exists to direct tokenised inputs to their designated function. This function allows
 for System commands to be executed by the application and for internal commands such as changing directory to
 be possible through use of if statements and forking to execute external commands (Which would otherwise terminate
 the program on execution). This implementation ensures that only the forked programs are terminated.*/

void command_selecter(char input[inputval], char *tokenArray[max_args], char *histArray[max_hist], int histcounter, char *aliasArray[max_alias][2]){

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
    else if(strcmp("alias",tokenArray[0])==true)
    {
		alias(tokenArray,aliasArray);
    }
    else if(strcmp("unalias",tokenArray[0])==true)
    {
        unalias(tokenArray,aliasArray);
    }
    else {
        /* If the input does not comply with the structure of a system command, then
        treat it as a system command and fork a new thread. Invalid commands are treated
         in this manner too. After execution the threads terminate and return to
         the control to the main thread. */
        pid_t pid;
        pid = fork();
        
        if (pid == -1) {
            /* If the fork() returns -1 then an error has occurred and the user is informed. */
            perror("Failed to fork process");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            /* If fork() returns 0, we are in the child process and can execute the system command. */
            if(execvp(tokenArray[0],tokenArray) == -1 ){
                printf("%s: Command not found\n",tokenArray[0]);
            }
            exit(2); /*Terminate the fork */
        }
        else {
           /* When the fork() is positive. We are in the parent process. */
            int status;
            (void)waitpid(pid, &status, 0);
            /* return value is Process ID of the child process. */
        }
    }
}


/* Tokenizer takes the user input and converts that into an array of tokens which
 are used by the command selector to execute the actions specified by the user. It
 splits the user input into individual strings whenever specific symbols are used
 and returns the updated array. */
char** tokenizer(char input[inputval], char *array[max_args]){
    char *inputstrings; /* Current value to be tokenised. */
    int i = 0; /* Tokenizer counter. */

    /* Take in the input, tokenise it and store first
     tokenised value in the array. */
    inputstrings = strtok(input, "<>| \n\t");

    array[0] = inputstrings;
    
    /* Whilst not at the end of the file and while the input
     is not NULL, take in the input, tokenise and store the
     current tokenised value in the array*/
    while(inputstrings != NULL && !feof(stdin)){
        i++;
        inputstrings = strtok(NULL,"<>| \n\t");
        array[i] = inputstrings;
    }
    
    /*Return the resulting tokenised array*/
    return array;
}


int main(int argc, char *argv[])
{
    /* Declaring, and where necessary, initialising of main variables which will be used repeatedly throughout the program.
     These will hold important values such as user inputs, the initial path. The name and location of the history file,
     and any aliases that are used during execution. */
    
    char *history[max_hist] = {0};
    int histcounter = 0;
    char *array[max_args];
    bool terminate = false;
    char input[inputval];
    char *originalPath;
    char cwd[256];
	char *alias[max_alias][2] = {{0}};
    char *filename;
    FILE *fileread;
    char inputunchanged[inputval];
    int i;
    
    /* Store the original path for retrieval at the end of the program. */
    originalPath = getenv("PATH");

    
    /* Set the current working directory to be the home folder defined by the Operating System. */
    chdir(getenv("HOME"));
    
    /* This part of the program opens the history containted in a hidden text file named .hist_list which is located
     in the host computers home directory. If the filed does not exist then it is created during the applications
     termination sequence. The contents of the history file are loaded into the 'history' array which is able to
     hold the last 20 commands entered by the user. */
    
    filename = strcat(getcwd(cwd,sizeof(cwd)),"/.hist_list");
    fileread = fopen ( filename, "r" );
    if (!fileread==true) /* If there is a file called .hist_list present. */
    {
        char line [512];
        while ( (fgets ( line, sizeof line, fileread ) != NULL) && (histcounter < 20)) /* Read line from history. */
        {
            history[histcounter] = strdup(strtok(line,"\n")); /* Remove the line break and add line to history array. */
            histcounter++;
        }
    	fclose ( fileread ); /* Close the file reader. */
    }
    else
    {
    /* If no file is found, informs the user accordingly. */
	printf("No previous history exists, a new history will be created upon exit.\n\n");

    }
    
    /* After an attempt has been made to load the history, execution of the main program commences. The terminal
     information is displayed and a loop prompts the user for input whilst persistently displaying their current
     working directory in the format of '/User/username >' and awaits user input. */
    
    printf("Simple Shell v0.8.8\n");
    printf("Created by CS210 Group 6 on 14/04/2014\n");
    printf("Copyright (c) 2014 CS210 Group 6, Strathclyde University.\n All rights reserved.\n\n");
    
    /* Infinite Loop until highest break is reached. */
    do {
        printf("%s >",getcwd(cwd, sizeof(cwd)));
        
        /* If the current input is not NULL then the user input is tokenised
         to remove the trailing newline character. */
        if((fgets(input, in_size, stdin)!=NULL)){
            strtok(input,"\n");
            
            /* The current value of input is stored in a new character array titled
             inputunchanged for use later when changing directory. */
            for (i=0;i<sizeof(input);i++){
                inputunchanged[i] = input[i];
            }
            
            /* If the input from the user is "exit" then begin termination
             of the program by breaking out of the do-while loop. */
            if(strcmp("exit",input)==true){
                break;
            }
            else{
                /* Process the users input by firstly checking to see whether it corresponds to a command which can
                 be executed from the history. The resulting value of this check is then compared against aliases,
                 and finally tokenised. The result of these three functions is a command which can be understood and
                 handled by the command selector. */
                
                histcounter = historycheck(input, histcounter, history);
                checkalias(input, alias);
                tokenizer(input, array);
                
                /* If the command passed on after tokenizing is a NULL value then it is not
                  passed to the command selector and is instead disregarded. */
                if(array[0] !=NULL){
                	command_selecter(inputunchanged,array,history,histcounter,alias);
                }
            }
        }
        else
            break; /* Exit the while loop and begin termination sequence. */
    } while (terminate ==false);
    
    /* Write out history to text file.*/
    writehistory(filename,history);
    
    /* Restore the original path for the user when exiting the program
     and display the change to the user showing their new path.*/
    setenv("PATH",originalPath,1);
    printf("\n\nPath on leaving program: %s\n",getenv("PATH"));
    printf("\n\nTerminated Execution.\n\n");
    return 0;
}

// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/limits.h>
#include <errno.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define HISTORY_DEPTH 10
char history[HISTORY_DEPTH][COMMAND_LENGTH];
int count=1;


/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */
void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);

	if (length < 0) {
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(-1);
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}

void addHistory(char *tokens[], bool background) {
    char command[COMMAND_LENGTH];
    command[0] = '\0';
	char count1[COMMAND_LENGTH];
	sprintf(count1, "%d\t", count);

	strcat(command, count1);
    for (int i = 0; tokens[i] != NULL; i++) {
        strcat(command, tokens[i]);
        strcat(command, " ");
    }

    if (background) {
        strcat(command, "& ");
    }

    if (strlen(command) > 0) {
        command[strlen(command) - 1] = '\0';
    }

    if (count < HISTORY_DEPTH) {
        strcpy(history[count], command);
    } else {
        for (int i = 1; i < HISTORY_DEPTH; i++) {
            strcpy(history[i - 1], history[i]);
        }
        strcpy(history[HISTORY_DEPTH - 1], command);
    }
    count++;
}

void printHistory() {
	int num;
	if (count>HISTORY_DEPTH){
		num=HISTORY_DEPTH;
	}
	else {
		num=count;
	}
    for (int i = num; i > 0; i--) {
		write(STDOUT_FILENO, history[i], strlen(history[i]));
		write(STDOUT_FILENO, "\n", strlen("\n"));
    }
}

/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];
	char cwd[PATH_MAX];
	char path[100];

	char* user=getenv("USER");
	char* home=getenv("HOME");

	strcpy(path, "/");
	strcpy(path, user);
	strcpy(path, "/");
	strcpy(path, home);

	if (chdir(path)!=0){
		perror("failed to enter home directory");
		exit(1);
	}
	while (true) {
		if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            exit(1);
        }

        char prompt[PATH_MAX + 3];
        snprintf(prompt, sizeof(prompt), "%s $ ", cwd);
		
		write(STDOUT_FILENO, prompt, strlen(prompt));
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);

		if (tokens[0]==NULL)
		{
			continue;
		}
		else if (strcmp(tokens[0], "history")==0) {
			printHistory();
			addHistory(tokens, false);
			continue;
		}
		else if (strcmp(tokens[0], "exit")==0){
			if (tokens[1]!=NULL){
				perror("Command not executed due to input");
				continue;
			}
			exit(1);
		}
		else if(strcmp(tokens[0], "pwd")==0){
			if (tokens[1]!=NULL)
			{
				perror("Command not executed due to input");
				continue;
			}
			getcwd(cwd, sizeof(cwd));
			write(STDOUT_FILENO, cwd, strlen(cwd));
			write(STDOUT_FILENO, "\n", strlen("\n"));
			addHistory(tokens, false);
			continue;
		}
		else if (strcmp(tokens[0],"cd")==0)
		{
			if (tokens[1] == NULL) {
                tokens[1] = path;
            }
			if (tokens[2]!=NULL)
			{
				perror("Unnecessary input");
				continue;
			}
			
			if(chdir(tokens[1])!=0){
				perror("Failed to cd");
			}
			addHistory(tokens, false);
			continue;
		}
		else if (strcmp(tokens[0], "help")==0)
		{
			if (tokens[1]==NULL){
				perror("Input error");
				continue;
			}
			if (tokens[2]!=NULL)
			{
				perror("Too many inputs");
				continue;
			}
			
			if (strcmp(tokens[1], "cd")==0)
			{
				char* output="'cd' is a built in command for changing the current working directory \n";
				write(STDOUT_FILENO, output, strlen(output));
				
			}
			else if (strcmp(tokens[1], "history")==0)
			{
				char* output="'history' is a built in command for outputting the last ten commands executed \n";
				write(STDOUT_FILENO, output, strlen(output));
				
			}
			else if (strcmp(tokens[1], "pwd")==0)
			{
				char* output="'pwd' is a built in command for outputting the current directory \n";
				write(STDOUT_FILENO, output, strlen(output));
				
			}
			else if (strcmp(tokens[1], "exit")==0)
			{
				char* output="'exit' is a built in command for exiting the shell \n";
				write(STDOUT_FILENO, output, strlen(output));
				
			}
			else if (strcmp(tokens[1], "help")==0)
			{
				char* output="'help' is a built in command for giving information on commands \n";
				write(STDOUT_FILENO, output, strlen(output));
				
			}
			else{
				char str[700];
				strcpy(str, tokens[1]);
				strcat(str, " is a built in command for giving information on commands \n");
				write(STDOUT_FILENO, str, strlen(str));
				
			}
			addHistory(tokens, false);
			continue;

		}
		
		

		pid_t p=fork();
		if (p<0){
            perror("fork fail");
            exit(1);
        }
		else if (p==0){
			execvp(tokens[0], tokens);
			perror("Execvp failed");
			exit(1);
		}
		else {
			if (!in_background)
			{
				waitpid(p, NULL, 0);
			}
			else{
				addHistory(tokens, true);
			}
			addHistory(tokens, false);
		}
		while (waitpid(-1, NULL, WNOHANG)>0){
					;
				}

		// DEBUG: Dump out arguments:
		for (int i = 0; tokens[i] != NULL; i++) {
			write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
			write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
			write(STDOUT_FILENO, "\n", strlen("\n"));
		}
		if (in_background) {
			write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
		}
		/**
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for
		 *    child to finish. Otherwise, parent loops back to
		 *    read_command() again immediately.
		 */
        
	}
	return 0;
}
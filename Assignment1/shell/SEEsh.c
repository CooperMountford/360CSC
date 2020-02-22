/***************************************************************************//**
   @file         main.c
   @author       Stephen Brennan
   @date         Thursday,  8 January 2015
   @brief        LSH (Libstephen SHell)
*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
   Function Declarations for builtin shell commands:
 */
int cd(char **args);
int pwd(char **args);
int help(char **args);
int exitShell(char **args);
int set(char **args);
int unset(char **args);

/*
   List of builtin commands, followed by their corresponding functions.
 */
char *builtinStr[] = {
        "cd",
        "pwd",
        "help",
        "exit",
        "set",
        "unset"
};

char *builtinDesc[] = {
        "Usage: cd [dir]\nChange SEEsh working directory to dir or HOME if no dir is given\n",
        "Usage: pwd\nPrint full filename of the current working directory\n",
        "Usage: help\nDisplay information about builtin commands\n",
        "Usage: exit\tor\tCtrl+D\nSEEsh will exit\n",
        "Usage: set var [value]\nIf an envirnment variable with name var does not already exist, it will be created with value given.\nIf no value is given, it will be set to the empty string\nIf both var and value are not given, all environment variables and their values will be displayed\n",
        "Usage: unset var\nSEEsh will destroy environment variable specified\n"
};

int (*builtinFunc[]) (char **) = {
        &cd,
        &pwd,
        &help,
        &exitShell,
        &set,
        &unset
};

int numBuiltins() {
        return sizeof(builtinStr) / sizeof(char *);
}

/*
   Builtin function implementations.
 */

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int cd(char **args)
{
        if (args[1] == NULL) {
                fprintf(stderr, "Expected Argument of \"cd\"\n");
        } else {
                if (chdir(args[1]) != 0) {
                        perror("SEEsh");
                }
        }
        return 1;
}

int pwd(char **args)
{
        char cwd[512];
        printf("\t%s\n", getcwd(cwd, sizeof(cwd)));
        return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int help(char **args)
{
        int i;
        printf("\n***********************************************************\n");
        printf("SEEshell adapted from Stephen Brennan's LSH\n");
        printf("Type program names and arguments, and hit enter.\n");
        printf("The following are built in:\n");

        for (i = 0; i < numBuiltins(); i++) {
                printf("  %s - %s\n", builtinStr[i], builtinDesc[i]);
        }

        printf("Use the man command for information on other programs.\n");
        printf("***********************************************************\n\n");
        return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int exitShell(char **args)
{
        exit(0);
}

int set(char **args)
{
        int env = 0;
        if(env == 0) {
                if(args[2] == NULL) {
                        env = setenv(args[1], " ", 1);
                }
                if(args[1] == NULL && args[2] == NULL) {
                        printf("Env Vars: ");

                }
                else {
                        env = setenv(args[2], args[2], 1);
                }
        }
        return 1;
}

int unset(char **args)
{
        int env = unsetenv(args[1]);
        if(env == 0)
         return 1;
        return 1;
}



/**
   @brief Launch a program and wait for it to terminate.
   @param args Null terminated list of arguments (including program).
   @return Always returns 1, to continue execution.
 */
int launch(char **args)
{
        pid_t pid;

        pid = fork();
        if (pid == 0) {
                // Child process
                if (execvp(args[0], args) == -1) {
                        perror("SEEsh");
                }
                exit(EXIT_FAILURE);

        } else if (pid < 0) {
                // Error forking
                perror("SEEsh");
        }

        return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int execute(char **args)
{
        int i;

        if (args[0] == NULL) {
                // An empty command was entered.
                return 1;
        }

        for (i = 0; i < numBuiltins(); i++) {
                if (strcmp(args[0], builtinStr[i]) == 0) {
                        return (*builtinFunc[i])(args);
                }
        }

        return launch(args);
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *readLine(void)
{
        char *line = NULL;
        size_t bufferSize = 0;
        getline(&line, &bufferSize, stdin);
        return line;
}


#define SEE_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **splitLine(char *line)
{
        int bufferSize = 64;
        int position = 0;
        char **tokens = malloc(bufferSize * sizeof(char*));
        char *token;

        // If no tokens are found
        if (!tokens) {
                fprintf(stderr, "Memory Allocation Error\n");
                exit(EXIT_FAILURE);
        }


        token = strtok(line, SEE_TOK_DELIM);
        while (token != NULL) {
                tokens[position] = token;
                position++;

                if (position >= bufferSize) {
                        bufferSize += 64;
                        tokens = realloc(tokens, bufferSize * sizeof(char*));
                        if (!tokens) {
                                fprintf(stderr, "Memory Allocation Error\n");
                                exit(EXIT_FAILURE);
                        }
                }

                token = strtok(NULL, SEE_TOK_DELIM);
        }
        tokens[position] = NULL;
        return tokens;
}


void rcopen(char* name) {
        FILE *rcfile;
        char file[512];
        char line[512];
        char *home = getcwd(file, sizeof(file));
        strcat(home, name);

        rcfile = fopen(file, "r");
        while(fgets(line, sizeof(line), rcfile)) {
                execute(splitLine(line));
        }

        fclose(rcfile);
}

/**
   @brief Loop getting input and executing it.
 */
void loop(void)
{
        char *line;
        char **args;
        int status;
        //int x = 0;

        do {
                printf("? ");
                line = readLine();
                //    x = line;
                args = splitLine(line);
                status = execute(args);

                // if(x == EOF) {
                //   printf("^D\n");
                //   exit(0);
                // }

                free(line);
                free(args);
        } while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
        // Load config files, if any.
        rcopen("/SEEshrc");
        // Run command loop.
        loop();

        // Perform any shutdown/cleanup.

        return EXIT_SUCCESS;
}

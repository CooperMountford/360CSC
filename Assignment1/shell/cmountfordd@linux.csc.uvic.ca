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
int help(char **args);
int exitShell(char **args);

/*
   List of builtin commands, followed by their corresponding functions.
 */
char *builtinStr[] = {
        "cd",
        "help",
        "exit"
};

int (*builtinFunc[]) (char **) = {
        &cd,
        &help,
        &exitShell
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

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int help(char **args)
{
        int i;
        printf("SEEshell adapted from Stephen Brennan's LSH\n");
        printf("Type program names and arguments, and hit enter.\n");
        printf("The following are built in:\n");

        for (i = 0; i < numBuiltins(); i++) {
                printf("  %s\n", builtinStr[i]);
        }

        printf("Use the man command for information on other programs.\n");
        return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int exitShell(char **args)
{
        return 0;
}

/**
   @brief Launch a program and wait for it to terminate.
   @param args Null terminated list of arguments (including program).
   @return Always returns 1, to continue execution.
 */
int launch(char **args)
{
        pid_t pid, wpid;
        int status;

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

        } else {
                // Parent process
                do {
                        wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
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
        ssize_t bufferSize = 0;
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

/**
   @brief Loop getting input and executing it.
 */
void loop(void)
{
        char *line;
        char **args;
        int status;

        do {
                printf("? ");
                line = readLine();
                args = splitLine(line);
                status = execute(args);

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

        // Run command loop.
        loop();

        // Perform any shutdown/cleanup.

        return EXIT_SUCCESS;
}

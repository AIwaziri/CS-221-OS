#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

void print_prompt()
{
    printf("phase1-shell> ");
}

void print_help()
{
    printf("Available commands:\n");
    printf("  help\n");
    printf("  ls\n");
    printf("  ps\n");
    printf("  pwd\n");
    printf("  date\n");
    printf("  whoami\n");
    printf("  uname\n");
    printf("  df\n");
}

int is_command_supported(char *command)
{
    const char *supported_commands[] = {
        "help", "ls", "ps", "pwd", "date", "whoami", "uname", "df"};
    for (int i = 0; i < sizeof(supported_commands) / sizeof(supported_commands[0]); i++)
    {
        if (strcmp(command, supported_commands[i]) == 0)
        {
            return 1; // Command is supported
        }
    }
    return 0; // Command is not supported
}

int main()
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    pid_t pid;
    int status;

    while (1)
    {
        print_prompt();
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        {
            perror("fgets failed");
            continue;
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Tokenize input into arguments
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARG_SIZE - 1)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Handle exit command
        if (args[0] != NULL && strcmp(args[0], "exit") == 0)
        {
            printf("exiting...\n");
            break;
        }

        // Handle help command
        if (args[0] != NULL && strcmp(args[0], "help") == 0)
        {
            print_help();
            continue;
        }

        // Check if the command is supported
        if (args[0] == NULL || !is_command_supported(args[0]))
        {
            printf("Error: Command '%s' is not supported.\n", args[0] ? args[0] : "NULL");
            continue;
        }

        // Fork a child process
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            continue;
        }

        if (pid == 0)
        {
            // Child process
            if (execvp(args[0], args) < 0)
            {
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            wait(&status);
        }
    }

    return 0;
}
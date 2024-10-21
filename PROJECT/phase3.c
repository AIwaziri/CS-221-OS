#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100
#define MAX_HISTORY_SIZE 100

pthread_mutex_t history_mutex;

void print_prompt()
{
    printf("phase3-shell> ");
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
    printf("  history\n");
    printf("  clearhistory\n");
    printf("  join\n");
}

void print_history(char history[][MAX_INPUT_SIZE], int history_count)
{
    pthread_mutex_lock(&history_mutex);
    printf("Command History:\n");
    for (int i = 0; i < history_count; i++)
    {
        printf("%d: %s\n", i + 1, history[i]);
    }
    pthread_mutex_unlock(&history_mutex);
}

void clear_history(char history[][MAX_INPUT_SIZE], int *history_count)
{
    pthread_mutex_lock(&history_mutex);
    *history_count = 0;
    printf("Command history cleared.\n");
    pthread_mutex_unlock(&history_mutex);
}

void *run_command(void *arg)
{
    char **args = (char **)arg;
    if (execvp(args[0], args) < 0)
    {
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

void get_command(char *prompt, char *input)
{
    printf("%s", prompt);
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
    {
        perror("fgets failed");
        exit(EXIT_FAILURE);
    }
    input[strcspn(input, "\n")] = 0; // Remove newline character
}

int main()
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    char history[MAX_HISTORY_SIZE][MAX_INPUT_SIZE];
    int history_count = 0;
    pid_t pid;
    int status;

    pthread_mutex_init(&history_mutex, NULL);

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

        // Save command to history
        pthread_mutex_lock(&history_mutex);
        if (history_count < MAX_HISTORY_SIZE)
        {
            strcpy(history[history_count], input);
            history_count++;
        }
        pthread_mutex_unlock(&history_mutex);

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

        // Handle history command
        if (args[0] != NULL && strcmp(args[0], "history") == 0)
        {
            print_history(history, history_count);
            continue;
        }

        // Handle clearhistory command
        if (args[0] != NULL && strcmp(args[0], "clearhistory") == 0)
        {
            clear_history(history, &history_count);
            continue;
        }

        // Handle join command
        if (args[0] != NULL && strcmp(args[0], "join") == 0)
        {
            char cmd1_input[MAX_INPUT_SIZE];
            char cmd2_input[MAX_INPUT_SIZE];
            char *cmd1[MAX_ARG_SIZE], *cmd2[MAX_ARG_SIZE];

            // Get first command
            get_command("Enter your first command: ", cmd1_input);

            // Get second command
            get_command("Enter your second command: ", cmd2_input);

            // Tokenize first command
            int j = 0;
            cmd1[j] = strtok(cmd1_input, " ");
            while (cmd1[j] != NULL && j < MAX_ARG_SIZE - 1)
            {
                j++;
                cmd1[j] = strtok(NULL, " ");
            }
            cmd1[j] = NULL;

            // Tokenize second command
            j = 0;
            cmd2[j] = strtok(cmd2_input, " ");
            while (cmd2[j] != NULL && j < MAX_ARG_SIZE - 1)
            {
                j++;
                cmd2[j] = strtok(NULL, " ");
            }
            cmd2[j] = NULL;

            // Create threads
            pthread_t thread1, thread2;
            char *cmd1_copy[MAX_ARG_SIZE], *cmd2_copy[MAX_ARG_SIZE];

            // Copy cmd1 arguments
            for (int k = 0; cmd1[k] != NULL; k++)
            {
                cmd1_copy[k] = strdup(cmd1[k]);
            }
            cmd1_copy[j] = NULL;

            // Copy cmd2 arguments
            for (int k = 0; cmd2[k] != NULL; k++)
            {
                cmd2_copy[k] = strdup(cmd2[k]);
            }
            cmd2_copy[j] = NULL;

            if (pthread_create(&thread1, NULL, run_command, (void *)cmd1_copy) != 0)
            {
                perror("pthread_create failed");
                continue;
            }
            if (pthread_create(&thread2, NULL, run_command, (void *)cmd2_copy) != 0)
            {
                perror("pthread_create failed");
                continue;
            }

            // Wait for threads to finish
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);

            // Free allocated memory
            for (int k = 0; cmd1_copy[k] != NULL; k++)
            {
                free(cmd1_copy[k]);
            }
            for (int k = 0; cmd2_copy[k] != NULL; k++)
            {
                free(cmd2_copy[k]);
            }

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

    pthread_mutex_destroy(&history_mutex);
    return 0;
}
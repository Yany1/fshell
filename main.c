/**
 * Copyright (c) 2019 Yanyi Hu, under the MIT License
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORMAT_CLEAR    "\033[0m"    // default output format
#define FORMAT_TRASH    "\033[1;34m" // output format for shell prompt
#define FORMAT_WARNING  "\033[1;31m" // output format for WARNING prompt
#define MAX_LINE_LENGTH 512          // max length of command line including '\0'
#define MAX_ARG_LENGTH  256          // max length of an argument
#define MAX_ARG_NUM     16           // max number of arguments

// int tokenize(const char* str, char* data, size_t length)
// {
//     static int i = 0;

//     // if str != NULL
//     if (str)
//     {
//         i = 0;
//     }

//     for (i; str[i] != '\0'; i++)
//     {
//         //
//     }
//     return -1;
// }

/**
 * struct command - data type to hold a single command
 * @arg_count: count of arguments
 * @args:      the arguments
 */
typedef struct command *command_ptr_t;
struct command
{
    int    arg_count;
    char** args;
};

/**
 * command_create - create a new command struct object
 * 
 * return: the newly created command object
 */
command_ptr_t command_create()
{
    command_ptr_t new_cmd = malloc(sizeof(struct command));
    new_cmd->arg_count = 0;
    // +1 to include the trailing NULL ptr
    new_cmd->args = malloc((MAX_ARG_NUM + 1) * sizeof(char*));

    return new_cmd;
}

void command_destroy(command_ptr_t cmd)
{
    while (cmd->arg_count != 0)
    {
        free(cmd->args[cmd->arg_count - 1]);
        cmd->arg_count--;
    }
    free(cmd->args);
    free(cmd);
}

command_ptr_t command_parse(const char* cmd_line)
{
    // if (strnlen(cmd_line, MAX_LINE_LENGTH) == 0)
    //     return NULL;

    // copy the incoming line
    char copied_line[MAX_LINE_LENGTH];
    memset(copied_line, 0, MAX_LINE_LENGTH);
    strncpy(copied_line, cmd_line, MAX_LINE_LENGTH);

    // parse the arguments
    char *token = strtok(copied_line, " \t");
    // if the parsed string is empty
    if (!token)
        return NULL;

    command_ptr_t new_cmd = command_create();

    // memset(new_cmd->program, 0, MAX_ARG_LENGTH);
    // if (!token || strnlen(token, MAX_ARG_LENGTH) == MAX_ARG_LENGTH)
    // {
    //     free(new_cmd);
    //     return NULL;
    // }
    // else
    //     strncpy(new_cmd->program, token, MAX_ARG_LENGTH);
    
    int i = 0;
    for (i = 0; i < MAX_ARG_NUM && token; i++)
    {
        if (strnlen(token, MAX_ARG_LENGTH) == MAX_ARG_LENGTH)
        {
            command_destroy(new_cmd);
            return NULL;
        }
        else
        {
            new_cmd->args[i] = malloc(sizeof(char[MAX_ARG_LENGTH]));
            memset(new_cmd->args[i], 0, MAX_ARG_LENGTH);
            strncpy(new_cmd->args[i], token, MAX_ARG_LENGTH);
        }

        token = strtok(NULL, " \t");
    }

    // if there's more than 16 arguments
    if (strtok(NULL, " \t"))
    {
        command_destroy(new_cmd);
        return NULL;
    }
    else
    {
        new_cmd->arg_count = i;
        new_cmd->args[i] = NULL; // add the trailing NULL ptr
    }

    return new_cmd;
}

void command_print(command_ptr_t cmd)
{
    assert(cmd->arg_count > 0);
    printf("program: \'%s\'; args:", cmd->args[0]);

    int i = 0;
    for (i = 1; i < cmd->arg_count; i++)
    {
        printf(" \'%s\',", cmd->args[i]);
    }

    assert(cmd->args[i] == NULL);
    printf("\b \b\n"); // eat the last ','
}

/**
 * read_line - read a single line of input
 * @buffer: to hold the string
 * 
 * undefined for cases like no '\n' or no '\0'
 * 
 * return: -1 if failed; otherwise 0
 */
int read_line(char* buffer)
{
    char c = 0;
    int i = 0;
    while ((c = getchar()) && c != '\n')
    {
        buffer[i] = c;
        i++;
    }

    buffer[i] = '\0'; // make sure NULL terminated
    // if exceeded max length
    if (i >= MAX_LINE_LENGTH)
        return -1;
    
    return 0;
}

int main(void)
{
    while (1)
    {
        char buffer[MAX_LINE_LENGTH]; // hold the line
        memset(buffer, 0, MAX_LINE_LENGTH);

        printf("%straSH%s$ ", FORMAT_TRASH, FORMAT_CLEAR);
        if (read_line(buffer))
        {
            printf("%sInput exceeded max length%s\n", FORMAT_WARNING, FORMAT_CLEAR);
            continue;
        }

        command_ptr_t new_cmd = command_parse(buffer);
        if (new_cmd)
        {
            command_print(new_cmd);
            if (!strncmp(new_cmd->args[0], "exit", MAX_ARG_LENGTH) && new_cmd->arg_count == 1)
            {
                printf("Exit traSH\n");
                exit(0);
            }

            command_destroy(new_cmd);
            new_cmd = NULL;
        }
        // // FIXME: better ways?
        // if(buffer[0] != '\0')
        //     printf("%s\n", buffer);
    }

    return 0;
}
/* Copyright (c) 2019 Yanyi Hu, under the MIT License */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512 // max length of command line including '\0'

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

        printf("\033[1;34mfshell\033[0m$ ");
        if (read_line(buffer))
        {
            printf("\033[1;31mInput exceeded max length\033[0m\n");
            continue;
        }

        if (!strncmp(buffer, "exit", MAX_LINE_LENGTH))
        {
            printf("Exit fshell\n");
            exit(0);
        }
        // FIXME: better ways?
        else if(buffer[0] != '\0')
            printf("%s\n", buffer);
    }

    return 0;
}
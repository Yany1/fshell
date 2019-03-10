/* Copyright (c) 2019 Yanyi Hu, under the MIT License */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FORMAT_CLEAR "\033[0m" // default output format
#define FORMAT_TRASH "\033[1;34m" // output format for shell prompt
#define FORMAT_WARNING "\033[1;31m" // output format for WARNING prompt
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

        printf("%straSH%s$ ", FORMAT_TRASH, FORMAT_CLEAR);
        if (read_line(buffer))
        {
            printf("%sInput exceeded max length%s\n", FORMAT_WARNING, FORMAT_CLEAR);
            continue;
        }

        if (!strncmp(buffer, "exit", MAX_LINE_LENGTH))
        {
            printf("Exit traSH\n");
            exit(0);
        }
        // FIXME: better ways?
        else if(buffer[0] != '\0')
            printf("%s\n", buffer);
    }

    return 0;
}
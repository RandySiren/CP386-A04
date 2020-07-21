/**
 *
 * Mandeep Sran
 * 150368680
 * July 15, 2020
 * CP386 - Operating Systems Assignment 4
 *
 **/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

#define FILE_NAME "sample4_in.txt"
#define CUSTOMER_COUNT 5

int maximum[5][4];

void readFile(char *fileName);
int getCustomerCount(int **data);

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Not enough input parameters!\n");
        return -1;
    }
    readFile(FILE_NAME);
    for (int i = 0; i < CUSTOMER_COUNT; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d", maximum[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void readFile(char *fileName)
{
    FILE *in = fopen(fileName, "r");
    if (!in)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return;
    }

    struct stat st;
    fstat(fileno(in), &st);
    char *fileContent = (char *)malloc(((int)st.st_size + 1) * sizeof(char));
    fileContent[0] = '\0';
    while (!feof(in))
    {
        char line[100];
        if (fgets(line, 100, in) != NULL)
        {
            strncat(fileContent, line, strlen(line));
        }
    }
    fclose(in);
    char *lines[CUSTOMER_COUNT];
    char *command = NULL;
    int i = 0;
    char *fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
    strcpy(fileCopy, fileContent);
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        lines[i] = malloc(sizeof(command) * sizeof(char));
        strcpy(lines[i], command);
        i++;
        command = strtok(NULL, "\r\n");
    }
    for (int j = 0; j < CUSTOMER_COUNT; j++)
    {
        char *token = NULL;
        int k = 0;
        token = strtok(lines[j], ",");
        while (token != NULL)
        {
            maximum[j][k] = atoi(token);
            k++;
            token = strtok(NULL, ",");
        }
    }
}

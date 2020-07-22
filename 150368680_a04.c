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

#define MAX_INPUT_SIZE 256
#define FILE_NAME "sample4_in.txt"

int customerCount;
int resourceCount;
int **maximum;
int **allocation;
int *available;

void readFile(char *fileName);
void printMaximum();

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Not enough input parameters!\n");
        return -1;
    }
    resourceCount = argc - 1;
    available = malloc(sizeof(int) * resourceCount);
    for (int i = 1; i < argc; i++)
    {
        available[i - 1] = atoi(argv[i]);
    }

    readFile(FILE_NAME);
    allocation = malloc(sizeof(int *) * customerCount);

    // START OF PROGRAM
    char *userCommand = malloc(sizeof(char) * MAX_INPUT_SIZE);

    printf("Number of Customers: %d\n", customerCount);
    printf("Currently Available resources: ");
    for (int i = 0; i < resourceCount; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");
    printf("Maximum resources from file:\n");
    printMaximum();
    while (1)
    {
        printf("Enter Command: ");
        fgets(userCommand, MAX_INPUT_SIZE, stdin);
        if (strlen(userCommand) > 0 && userCommand[strlen(userCommand) - 1] == '\n')
        {
            userCommand[strlen(userCommand) - 1] = '\0';
        }
        // HANDLE USER INPUTTED PROGRAM HERE
        if (strcmp(userCommand, "RQ") == 0)
        {
        }
        else if (strcmp(userCommand, "RL") == 0)
        {
        }
        else if (strcmp(userCommand, "*") == 0)
        {
        }
        else if (strcmp(userCommand, "exit") == 0)
        {
            return 0;
        }
        {
            printf("\"%s\" is not a valid input, enter one of [\"RQ\",\"RL\",\"*\"].\n", userCommand);
        }
    }
    return 0;
}

void printMaximum()
{

    for (int i = 0; i < customerCount; i++)
    {
        for (int j = 0; j < resourceCount; j++)
        {
            printf("%d", maximum[i][j]);
            if (j < resourceCount - 1)
                printf(",");
        }
        printf("\n");
    }
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
    char *command = NULL;
    char *fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
    strcpy(fileCopy, fileContent);
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        customerCount++;
        command = strtok(NULL, "\r\n");
    }
    strcpy(fileCopy, fileContent);
    char *lines[customerCount];
    int i = 0;
    command = strtok(fileCopy, "\r\n");
    while (command != NULL)
    {
        lines[i] = malloc(sizeof(command) * sizeof(char));
        strcpy(lines[i], command);
        i++;
        command = strtok(NULL, "\r\n");
    }
    maximum = malloc(sizeof(int *) * customerCount);
    for (int j = 0; j < customerCount; j++)
    {
        int *temp = malloc(sizeof(int) * resourceCount);
        char *token = NULL;
        int k = 0;
        token = strtok(lines[j], ",");
        while (token != NULL)
        {
            temp[k] = atoi(token);
            k++;
            token = strtok(NULL, ",");
        }
        maximum[j] = temp;
    }
}

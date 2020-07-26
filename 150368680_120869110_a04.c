/**
 *
 * Mandeep Sran
 * 150368680
 * Raman Kala
 * 120869110
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
int **need;
int *available;
int *sequence;

int *getSafetySequence();
int **readFile(char *fileName);
void printDoublePointerData(int **data, int m, int n);
void printSinglePointerData(int *data, int m);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Not enough input parameters!\n");
        return -1;
    }
    resourceCount = argc - 1;

    // Initialize available array
    available = malloc(sizeof(int) * resourceCount);
    for (int i = 1; i < argc; i++)
    {
        available[i - 1] = atoi(argv[i]);
    }

    // Initialize maximum array by reading file and assigning values
    maximum = readFile(FILE_NAME);

    // Initialize allocation array and need array
    allocation = malloc(sizeof(int *) * customerCount);
    need = malloc(sizeof(int *) * customerCount);
    for (int i = 0; i < customerCount; i++)
    {
        allocation[i] = malloc(sizeof(int) * resourceCount);
        need[i] = malloc(sizeof(int) * resourceCount);
    }

    /**
     * 
     * START OF PROGRAM
     * 
     * */
    char *userCommand = malloc(sizeof(char) * MAX_INPUT_SIZE);

    printf("Number of Customers: %d\n", customerCount);
    printf("Currently Available resources: ");
    printSinglePointerData(available, resourceCount);
    printf("Maximum resources from file:\n");
    printDoublePointerData(maximum, customerCount, resourceCount);

    // Loop to continue running until "exit" is inputted
    while (1)
    {
        printf("Enter Command: ");
        fgets(userCommand, MAX_INPUT_SIZE, stdin);
        // Replace new line character with end of line character
        if (strlen(userCommand) > 0 && userCommand[strlen(userCommand) - 1] == '\n')
        {
            userCommand[strlen(userCommand) - 1] = '\0';
        }
        /**
         * 
         * HANDLE USER INPUT CASES BELOW
         * 
         * */
        if (strstr(userCommand, "RQ"))
        {
            // Split tokens by space to insert into allocation array
            int count = 0;
            int *inputArray = malloc(sizeof(int) * (resourceCount + 1));
            char *token = NULL;
            token = strtok(userCommand, " ");
            while (token != NULL)
            {
                if (count > 0)
                {
                    inputArray[count - 1] = atoi(token);
                }
                token = strtok(NULL, " ");
                count++;
            }

            // Insert into allocation array
            int customerToAllocate = inputArray[0];
            if (customerToAllocate < customerCount && count == resourceCount + 2)
            {
                for (int i = 0; i < resourceCount; i++)
                {
                    allocation[customerToAllocate][i] = inputArray[i + 1];
                    need[customerToAllocate][i] = maximum[customerToAllocate][i] - allocation[customerToAllocate][i];
                    // Don't let need values become negative
                    if (need[customerToAllocate][i] < 0)
                    {
                        need[customerToAllocate][i] = 0;
                    }
                }
            }
            else
            {
                if (customerToAllocate >= customerCount)
                {
                    printf("Thread out of bounds, please try again.\n");
                }
                else
                {
                    printf("Incorrect parameter count, please try again.\n");
                }
            }
            free(inputArray);
            // Determine if request would be satisfied or denied with safety algorithm
        }
        else if (strstr(userCommand, "RL"))
        {
            sequence = getSafetySequence();
            printSinglePointerData(sequence, customerCount);
        }
        else if (strstr(userCommand, "*"))
        {
            printf("Available Resources:\n");
            printSinglePointerData(available, resourceCount);
            printf("Maxmium Resources:\n");
            printDoublePointerData(maximum, customerCount, resourceCount);
            printf("Allocated Resources:\n");
            printDoublePointerData(allocation, customerCount, resourceCount);
            printf("Need Resources:\n");
            printDoublePointerData(need, customerCount, resourceCount);
        }
        else if (strstr(userCommand, "Run"))
        {
        }
        else if (strstr(userCommand, "exit"))
        {
            free(maximum);
            free(allocation);
            free(need);
            free(available);
            free(sequence);
            return 0;
        }
        else
        {
            printf("\"%s\" is not a valid input, enter one of [\"RQ\",\"RL\",\"*\",\"Run\",\"exit\"].\n", userCommand);
        }
    }
    return 0;
}

int *getSafetySequence()
{
    // Safety sequence we will be returning, all -1 if unsafe
    int *sequence = malloc(sizeof(int) * customerCount);
    int *work = malloc(sizeof(int) * resourceCount);
    int *finished = malloc(sizeof(int) * customerCount);

    // Initialize work to what we have available
    for (int i = 0; i < resourceCount; i++)
    {
        work[i] = available[i];
    }

    // Primary safety algorithm
    int count = 0;
    while (count < customerCount)
    {
        int isSafe = 0;
        for (int i = 0; i < customerCount; i++)
        {
            if (finished[i] == 0)
            {
                int safeIteration = 1;
                for (int j = 0; j < resourceCount; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        safeIteration = 0;
                        break;
                    }
                }
                if (safeIteration == 1)
                {
                    sequence[count] = i;
                    finished[i] = 1;
                    count++;
                    isSafe = 1;
                    for (int j = 0; j < resourceCount; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                }
            }
        }
        // Set safety sequence to -1 and return if no safe sequence found
        if (isSafe == 0)
        {
            for (int k = 0; k < customerCount; k++)
            {
                sequence[k] = -1;
            }
            free(work);
            free(finished);
            return sequence;
        }
    }
    free(work);
    free(finished);
    return sequence;
}

void printDoublePointerData(int **data, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", data[i][j]);
            if (j < n - 1)
                printf(" ");
        }
        printf("\n");
    }
}

void printSinglePointerData(int *data, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%d", data[i]);
        if (i < m - 1)
            printf(" ");
    }
    printf("\n");
}

int **readFile(char *fileName)
{
    FILE *in = fopen(fileName, "r");
    if (!in)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return NULL;
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
    int **max = malloc(sizeof(int *) * customerCount);
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
        max[j] = temp;
    }
    return max;
}

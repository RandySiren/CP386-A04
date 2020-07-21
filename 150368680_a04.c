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

int customerCount;
int **maximum;

void readFile(char *fileName, int m);
int getCustomerCount(int **data);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Not enough input parameters!\n");
        return -1;
    }
    readFile(FILE_NAME, argc);
    for (int i = 0; i < customerCount; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // printf("%d", maximum[i][j]);
            printf("%d", maximum[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void readFile(char *fileName, int m)
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
    fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
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
        int *temp = malloc(sizeof(int) * m);
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

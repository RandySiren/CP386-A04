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

int readFile(char *fileName);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Input file name missing...exiting with error code -1\n");
        return -1;
    }
	int status = readFile(argv[1]);
	printf("%d", status);
	return 0;
}

int readFile(char *fileName)
{
	FILE *in = fopen(fileName, "r");
    if (!in)
    {
        printf("Child A: Error in opening input file...exiting with error code -1\n");
        return -1;
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
		printf("%s", command);
		printf("\n");
        command = strtok(NULL, "\r\n");
    }
	return 0;
}

/*
 * VSC        : Flemish Supercomputing Centre
 * Tutorial   : Introduction to HPC
 * Description: Allocate and cConsume a given amount of memory
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MB         = 1024 * 1024;
const int default_GB = 3;
const int max_GB     = 12;


int main(int argc, char *argv[])
{
    register int i;
    int tot_GB = default_GB;
    char* mem[MB];

    if (argc > 2) {
        printf("Usage: eat_mem [number]\n");
        printf("  Allocate and use [number] Gigabyte of memory.\n");
        printf("  Default is %s Gigabyte.\n", default_GB);
        exit(1);
    }

    // Calculate the amount of memory to allocate
    // Default = 5Gb
    if (argc == 2) {
        tot_GB = atoi(argv[1]);
        if (tot_GB <= 0)
            tot_GB = default_GB;
        else if (tot_GB > max_GB) {
            printf("eat_mem: Exceeded maximum, reset to %d Gigabyte.\n", max_GB);
            tot_GB = max_GB;
        }
    }
    printf("eat_mem: Consuming %d Gigabyte of memory.\n", tot_GB);

    char buffer[MB];
    // Fill up a buffer of 1 MB with random digits
    for (i = 0; i < MB; i++)
        buffer[i] = rand()%256;

    // Consume memory, 1 MB at a time
    for (i = 0; i < tot_GB*1024; i++) {
        mem[i] = (char *) malloc(MB*sizeof(char));
        if (mem[i] == NULL) {
            printf("eat_mem: ERROR: Out of memory\n");
            return 1;
        }
        else {
            memcpy(mem[i], (void *) buffer, MB);
            usleep (20000); // Wait 20 microseconds
        }
    }

    // Sleep 10 seconds, so that you have time to monitor the full memory allocation
    sleep (10);

    // Free memory, 1 MB at a time
    for (i = 0; i < tot_GB*1024; i++) {
        free(mem[i]);
    }

    // Sleep 10 seconds, so that you have time to monitor the freed-up memory
    sleep (10);

    return 0;
}


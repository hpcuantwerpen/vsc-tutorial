/*
 * VSC        : Flemish Supercomputing Centre
 * Tutorial   : Introduction to HPC
 * Description: Allocate and consume a given amount of memory
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const unsigned int KiB = 1024;
const unsigned int MiB = 1024 * KiB;
const unsigned int default_GiB = 3;
const unsigned int max_GiB = 12;
const unsigned int long_sleep = 10;
const unsigned int micro_sleep_malloc = 20000;
const unsigned int micro_sleep_free = 5000;

int main(int argc, char *argv[])
{

	unsigned int tot_GiB = default_GiB;
	char **mem;

	if (argc > 2)
	{
		printf("Usage: eat_mem [number]\n");
		printf("	Allocate and use [number] Gigabyte of memory.\n");
		printf("	Default is %u Gigabyte.\n", default_GiB);
		exit(1);
	}

	// Calculate the amount of memory to allocate
	// Default set by default_GiB
	if (argc == 2)
	{
		int arg_GiB;
		arg_GiB = atoi(argv[1]);
		if (arg_GiB <= 0)
			tot_GiB = default_GiB;
		else if (arg_GiB > max_GiB)
		{
			printf("Exceeded maximum, reset to %d Gigabyte.\n", max_GiB);
			tot_GiB = max_GiB;
		}
		else
			tot_GiB = (unsigned int)arg_GiB;
	}
	printf("Consuming %d GiB of memory.\n", tot_GiB);

	// Allocate memory for mem
	mem = (char **)calloc((size_t)MiB, sizeof(char *));
	if (mem == NULL)
	{
		printf("ERROR: Failed to allocate memory for the internal variable mem\n");
		return 1;
	}

	char *buffer;
	buffer = (char *)malloc((size_t)MiB * sizeof(char));
	if (buffer == NULL)
	{
		printf("ERROR: Failed to allocate memory for the internal variable buffer\n");
		return 1;
	}
	// Fill up a buffer of 1 Mb with random digits
	for (unsigned int i = 0; i < MiB; i++)
		buffer[i] = rand() % 256;

	// Consume memory, 1 MiB at a time
	for (unsigned int i = 0; i < tot_GiB * 1024; i++)
	{
		mem[i] = (char *)malloc(MiB * sizeof(char));
		if (mem[i] == NULL)
		{
			printf("ERROR: Out of memory after %d MiB\n", i);
			return 1;
		}
		else
		{
			memcpy(mem[i], (void *)buffer, MiB);
			usleep(micro_sleep_malloc); // Wait 20 microseconds
		}
	}

	// Sleep 10 seconds, so that you have time to monitor the full memory allocation
	printf("Filled %d GiB of memory, sleeping %u seconds.\n", tot_GiB, long_sleep);
	sleep(long_sleep);
	printf("Start freeing the memory\n");

	// Free memory, 1 Mb at a time
	for (unsigned int i = 0; i < tot_GiB * 1024; i++)
	{
		free(mem[i]);
		usleep(micro_sleep_free); // Wait 5 microseconds
	}
	// Sleep 10 seconds, so that you have time to monitor the freed-up	memory
	printf("Freed the memory, sleeping %u seconds\n", long_sleep);
	sleep(long_sleep);

	return 0;
}

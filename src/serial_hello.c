//
// Demo program part of the UAntwerp VSC tutorials.
//
// This program is used to demonstrate starting a serial program.
// It is essentially a hello world program, but with an added element that does
// make the source code more difficult: It prints information about the
// core it runs on, and that information is printed in order of OpenMP thread number,
// requiring quite a lot of synchronization.
//

#define _GNU_SOURCE   // Needed to get gethostname from unistd.h and sched_getcpu from sched.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#define HOSTNAMELENGTH 40          // Not really good practice to fix the length of strings as it can cause
                                   // buffer overflows (though not in this case), but let's not make it harder
                                   // than needed given the purpose of this program.

typedef struct {
    int  corenum;                  // Will point to an array containing the OS core number for each OpenMP thread
                                   // We'll do a dirty trick and actually start that array at the firstcore field
                                   // when we allocate memory.
    char hostname[HOSTNAMELENGTH]; // Name of the host on which this process is running
} t_rankData;

/******************************************************************************
This is a simple hello world program. Each thread prints out the rank of its
MPI process and its OpenMP thread number, and the total number of MPI ranks
and OpenMP threads per process.
******************************************************************************/

int main( int argc, char *argv[] )
{

    char my_hostname[HOSTNAMELENGTH];
    t_rankData my_rankData;

    //
    // Initializations
    //

    //
    // Gather data
    //

    // First common data
    gethostname( my_rankData.hostname, HOSTNAMELENGTH );

    // Go into the OpenMP section to get information for each OpenMP thread

    my_rankData.corenum = sched_getcpu();


    //
    // Now print all data
    //

    printf( "++ Running on cpu %d of %s\n", my_rankData.corenum, my_rankData.hostname );

    return 0;

}


//
// Demo program part of the UAntwerp VSC tutorials.
//
// This program is used to demonstrate starting a OpenMP program.
// It is essentially a hello world program, but with an added element that does
// make the source code more difficult: Every thread prints information about the
// core it runs on, and that information is printed in order of OpenMP thread number,
// requiring quite a lot of synchronization.
//

#define _GNU_SOURCE   // Needed to get gethostname from unistd.h and sched_getcpu from sched.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

#include <omp.h>

#define HOSTNAMELENGTH 40          // Not really good practice to fix the length of strings as it can cause
                                   // buffer overflows (though not in this case), but let's not make it harder
                                   // than needed given the purpose of this program.

typedef struct {
    int  *corenum;                 // Will point to an array containing the OS core number for each OpenMP thread
                                   // We'll do a dirty trick and actually start that array at the firstcore field
                                   // when we allocate memory.
    int  openmp_numthreads;        // Number of threads in the current MPI process
    char hostname[HOSTNAMELENGTH]; // Name of the host on which this process is running
    int  firstcore;                // To make sure that the end of the struct is properly aligned for integers.
} t_rankData;

/******************************************************************************
This is a simple hello world program. Each thread prints out the rank of its
MPI process and its OpenMP thread number, and the total number of MPI ranks
and OpenMP threads per process.
******************************************************************************/

int main( int argc, char *argv[] )
{

    char my_hostname[HOSTNAMELENGTH];
    int openmp_numthreads;              // Number of OpenMP threads.
    t_rankData *my_rankData;
    int my_rankData_size;

    //
    // Initializations
    //
    // Get the number of OpenMP threads
#pragma omp parallel shared( openmp_numthreads )   // The shared clause is not strictly needed as that variable will be shared by default.
    { if ( omp_get_thread_num() == 0 ) openmp_numthreads = omp_get_num_threads(); } // Must be in a parallel session to get the proper number.

    // Create the data structure.
    my_rankData_size = sizeof( t_rankData ) + (openmp_numthreads - 1) * sizeof( int );
    my_rankData = (t_rankData *) malloc( my_rankData_size );
    if ( my_rankData == NULL ) { fprintf( stderr, "ERROR: Memory allocation failed.\n" ); return 1; };
    my_rankData->corenum = &(my_rankData->firstcore);
    my_rankData->openmp_numthreads = openmp_numthreads;

    //
    // Gather data
    //

    // First common data
    gethostname( my_rankData->hostname, HOSTNAMELENGTH );

    // Go into the OpenMP section to get information for each OpenMP thread

#pragma omp parallel
    {
        int openmp_myid;
        int cpunum;

        /* Get OpenMP information. */
        openmp_myid = omp_get_thread_num();
        my_rankData->corenum[openmp_myid] = sched_getcpu();
    } // End of OpenMP parallel section.


    //
    // Now print all data
    //

    printf( "++ Output format: thread num <thread> of <#threads> on cpu <cpu> of <host>\n" );

    for ( int c1 = 0; c1 < my_rankData->openmp_numthreads; c1++ ) {
        printf( "++ OpenMP         thread num      %3d of        %3d on cpu   %3d of %s\n",
                c1, my_rankData->openmp_numthreads, my_rankData->corenum[c1], my_rankData->hostname );
    }  // end for ( c1 = ...

    return 0;

}


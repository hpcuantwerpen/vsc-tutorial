// Demo program part of the UAntwerp VSC tutorials.
//
// This program is used to demonstrate starting a MPI-program.
// It is essentially a hello world program, but with an added element that does
// make the source code more difficult: To make it easy to check that all processes
// run where we expect it, we make sure that the output is ordered according to
// MPI rank.
//

#define _GNU_SOURCE   // Needed to get gethostname from unistd.h and sched_getcpu from sched.h

#include <stdio.h>
#include <unistd.h>
#ifndef RHL5
// Red Hat Linux 5 does not yet now the functions in sched.h that we use.
#include <sched.h>
#endif

#include <mpi.h>

#define HOSTNAMELENGTH 40

typedef struct {
    int  mpi_id;                       // MPI rank of the current process
    int  corenum;                      // Number of the core
    char mpi_hostname[HOSTNAMELENGTH]; // Name of the host on which this process is running
} t_rankData;


/******************************************************************************
This is a simple hello world program. Each process prints out its rank, its
hostname and its core number.
******************************************************************************/

int main( int argc, char *argv[] )
{
    t_rankData my_rankData;
    t_rankData buf_rankData;  // Buffer for communications.
    int mpi_myid, mpi_numprocs;
    char mpi_hostname[HOSTNAMELENGTH];
    int error;
    MPI_Request request;
    MPI_Status  status;

    MPI_Init( &argc, &argv );

    // Get info on the MPI process.
    MPI_Comm_size( MPI_COMM_WORLD, &mpi_numprocs );
    MPI_Comm_rank( MPI_COMM_WORLD, &mpi_myid );

    // Print some information on the data just computed.
    if ( mpi_myid == 0 )
        printf( "Running %d MPI ranks.\n", mpi_numprocs );

    // Fill the rankData structure
    my_rankData.mpi_id = mpi_myid;
    my_rankData.corenum = sched_getcpu();
    gethostname( my_rankData.mpi_hostname, HOSTNAMELENGTH );

    // Now we'll print all information on the process with rank 0.

    // Send data to process with rank 0.
    // Just for the symmetry of the code, rank 0 does a send to itself so we
    // use a non-blocking send.
    error = MPI_Isend( &my_rankData, (int) sizeof( t_rankData ), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &request );

    if ( mpi_myid == 0 ) {

        printf( "++ Output format: <MPIrank> of <#MPIprocs> on cpu <cpu> of <host>\n" );

        for ( int c1 = 0; c1 < mpi_numprocs; c1++ ) {

            error = MPI_Recv( &buf_rankData, (int) sizeof( t_rankData ), MPI_BYTE, c1, 0, MPI_COMM_WORLD, &status );

            printf( "++ MPI rank             %03d of         %3d on cpu    %2d of %s\n",
                    buf_rankData.mpi_id, mpi_numprocs, buf_rankData.corenum, buf_rankData.mpi_hostname );

        } // end for ( int c1 = 0; c1 < mpi_numprocs; c1++ )

    } // end if ( mpi_myid == 0 )

    /* Close off properly. */

    MPI_Finalize();

    return 0;

}


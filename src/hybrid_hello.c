//
// Demo program part of the UAntwerp VSC tutorials.
//
// This program is used to demonstrate starting a hybrid OpenMP/MPI-program.
// It is essentially a hello world program, but with an added element that does
// make the source code more difficult: To make it easy to check that all processes
// and threads run where we expect it, we make sure that the output is ordered
// according to MPI rank and thread number.
//

#define _GNU_SOURCE   // Needed to get gethostname from unistd.h and sched_getcpu from sched.h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>

#include <mpi.h>
#include <omp.h>

#define EXIT_SUCCESS         0
#define EXIT_WRONG_ARGUMENT  1

#define HOSTNAMELENGTH 100             // Not really good practice to fix the length of strings as it can cause
                                       // buffer overflows (though not in this case), but let's not make it harder
                                       // than needed given the purpose of this program.
#define LABELLENGTH    20

typedef struct {
    int  *corenum;                     // Will point to an array containing the OS core number for each OpenMP thread
                                       // We'll do a dirty trick and actually start that array at the firstcore field
                                       // when we allocate memory.
    int  mpi_myrank;                   // MPI rank of the current process
    int  openmp_numthreads;            // Number of threads in the current MPI process
    char hostname[HOSTNAMELENGTH+1];   // Name of the host on which this process is running
    char label[LABELLENGTH+1];         // Label (if specified)
    int  firstcore;                    // To make sure that the end of the struct is properly aligned for integers.
} t_rankData;


//******************************************************************************
//
// print_help()
//
// Prints help information.
//

void print_help() {

	fprintf( stderr,
        "hybrid_hello\n\n"
		"Flags accepted:\n"
		" -h         produce help information and exit\n"
		" -l <label> specify a label to use in the output for this process\n"
		"            This simulates using different executable names in a\n"
		"            heterogeneous job.\n"
		"\n"
		"This program prints out usefull information ont he distribution of processes\n"
		"and threads in a hybrid MPI/OpenMP application.\n"
		"It also provides information on where each thread is running and how threads\n"
		"are bound to CPUs. It also supports MPMD startup, though you would use the\n"
		"same executable for each part of the heterogeneous job and instead use a\n"
		"different label for each part.\n\n"
    );

}


//******************************************************************************
//
// get_args( argc, argv, mpi_myrank )
//
// Prints help information and exits.
//

void get_args( int argc, char **argv, int mpi_myrank,
		       int *option_use_label, char *option_label ) {

	char *exe_name;

	// Remove the program name
	exe_name = *argv++;
	argc--;

	while ( argc-- ) {

		if ( strcmp( *argv, "-h") == 0 ) {
			if ( mpi_myrank == 0 ) print_help();
			exit( EXIT_SUCCESS );
		} else if ( strcmp( *argv, "-l") == 0 ) {
			if ( argc == 0 ) {
				fprintf( stderr, "%s: No label found for -l\n", exe_name );
				exit( EXIT_WRONG_ARGUMENT );
			}
            *option_use_label = 1;
            argv++; argc--; // Skip to the next argument which should be the label.
            strncpy( option_label, *argv, (size_t) LABELLENGTH );
            option_label[LABELLENGTH] = '\0';  // Just to be very sure that the string is null-terminated.
		} else {
			fprintf( stderr, "%s: Illegal flag found: %s\n", exe_name, *argv);
			exit( EXIT_WRONG_ARGUMENT );
		}

		argv++;

	}


	return;

}


/******************************************************************************
This is a simple hello world program. Each thread prints out the rank of its
MPI process and its OpenMP thread number, and the total number of MPI ranks
and OpenMP threads per process.
******************************************************************************/

int main( int argc, char *argv[] )
{
	int  option_use_label = 0;          // Set to nonzero value if -l is specified.
	char option_label[LABELLENGTH+1];   // Space for the label (if used)

	int label_length;
	int max_label_length;

    int mpi_myrank;                     // My MPI rank
	int mpi_numranks;                   // Total number of MPI ranks
    int openmp_numthreads;              // Number of OpenMP threads.
    int max_openmp_numthreads;          // Maximal number of threads per process over all MPI processes.
    int sum_openmp_numthreads;          // Total number of OpenMP threads over all MPI processes.
    t_rankData *my_rankData;            // Rank data for this MPI process
    t_rankData *buf_rankData;           // Buffer to receive data from another process.
    int my_rankData_size, buf_rankData_size;
    int error;
    MPI_Request request;
    MPI_Status status;

    MPI_Init( &argc, &argv );            // Standard way of initilizing a MPI program.

    //
    // Initializations
    //

    // Get basic info: Number of processes and the number of threads in this process
    MPI_Comm_size( MPI_COMM_WORLD, &mpi_numranks );
    MPI_Comm_rank( MPI_COMM_WORLD, &mpi_myrank );

#pragma omp parallel shared( openmp_numthreads )   // The shared clause is not strictly needed as that variable will be shared by default.
    { if ( omp_get_thread_num() == 0 ) openmp_numthreads = omp_get_num_threads(); } // Must be in a parallel session to get the proper number.

    MPI_Reduce( &openmp_numthreads, &max_openmp_numthreads, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD );
    MPI_Reduce( &openmp_numthreads, &sum_openmp_numthreads, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD );

    //
    // Read the command line arguments
    //
    option_label[0] = '\0'; // Make sure it is always initialised to at least the empty string.
    get_args( argc, argv, mpi_myrank,
    		  &option_use_label, option_label );

    // Compute the maximum length of the labels, and take into account that in a heterogeneous
    // job some parts may not be labeled.
    label_length = strlen( option_label ); // We can in fact always use strlen as option_label ahs been initialised ot the empty string.
    MPI_Reduce( &label_length, &max_label_length, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD );

    // Print some information on the data just computed.
    if ( mpi_myrank == 0 )
        printf( "Running a total of %d threads in %d MPI ranks (maximum %d threads per rank).\n",
                sum_openmp_numthreads, mpi_numranks, max_openmp_numthreads );

    // Now create the t_rankData data structures.

    my_rankData_size = sizeof( t_rankData ) + (openmp_numthreads - 1) * sizeof( int );
    my_rankData = (t_rankData *) malloc( my_rankData_size );
    if ( my_rankData == NULL ) { fprintf( stderr, "ERROR: Memory allocation for my_rankData failed.\n" ); return 1; };
    my_rankData->corenum = &(my_rankData->firstcore);

    if ( mpi_myrank == 0 ) {
        buf_rankData_size = sizeof( t_rankData ) + (max_openmp_numthreads - 1) * sizeof( int );
        buf_rankData = (t_rankData *) malloc( buf_rankData_size );
        if ( buf_rankData == NULL ) { fprintf( stderr, "ERROR: Memory allocation for buf_rankData failed.\n" ); return 2; };
        buf_rankData->corenum = &(buf_rankData->firstcore);
    }  // end if ( mpi_myid == 0 )

    //
    // Gather all data for the current MPI process and store in the my_rankData structure.
    //

    my_rankData->mpi_myrank = mpi_myrank;
    my_rankData->openmp_numthreads = openmp_numthreads;
    gethostname( my_rankData->hostname, (size_t) (HOSTNAMELENGTH+1) );
    strcpy( my_rankData->label, option_label );
#pragma omp parallel
    {
        int openmp_myid;

        /* Get OpenMP information. */
        openmp_myid = omp_get_thread_num();
        my_rankData->corenum[openmp_myid] = sched_getcpu();
    } // End of OpenMP parallel section.

    //
    // Finally print the results.
    // We'll do all printing on the master thread of MPI rank 0 so that
    // the output is sorted as it should.
    // To avoid having to build complex MPI datatypes, we assume a homogeneous
    // cluster in the sense that all nodes used have the same CPU family.
    //

    // Send data to process with rank 0.
    error = MPI_Isend( my_rankData, my_rankData_size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &request );

    if ( mpi_myrank == 0 ) {

    	const char *empty_string = "";
    	const char *sep_colon = ": ";

        const char *label_sep = ( ( max_label_length > 0 ) ? sep_colon : empty_string );

        printf( "++ Output format:%*s             (MPIrank,thread) of (#MPIprocs,#threads in rank) on cpu <cpu> of <host>\n",
        		(max_label_length > 0) ? max_label_length + 2 : 0, empty_string );

        for ( int c1 = 0; c1 < mpi_numranks; c1++ ) {

            error = MPI_Recv( buf_rankData, buf_rankData_size, MPI_BYTE, c1, 0, MPI_COMM_WORLD, &status );
            buf_rankData->corenum = &(buf_rankData->firstcore); // Because the pointer from the other process doesn't make sense.

            for ( int c2 = 0; c2 < buf_rankData->openmp_numthreads; c2++ ) {
                printf( "++ %-*s%sMPI rank/OpenMP thread num (    %3d,   %3d) of (      %3d,             %3d) on cpu   %3d of %s\n",
                		max_label_length, buf_rankData->label, label_sep,
                        buf_rankData->mpi_myrank, c2, mpi_numranks, buf_rankData->openmp_numthreads,
                        buf_rankData->corenum[c2], buf_rankData->hostname );

            }  // end for ( int c2...
        }  // end for ( int c1...

    } // end if ( mpi_myrank == 0 )


    // Close off properly.

    MPI_Barrier( MPI_COMM_WORLD );
    MPI_Finalize();

    return 0;

}


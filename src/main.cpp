/*******************************************************************************
Machanguitos is The Easiest Multi-Agent System in the world. Work done at The
Institute of Physics of Cantabria (IFCA).
Copyright (C) 2013  Luis Cabellos

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
//------------------------------------------------------------------------------
#include <cstdlib>
#include <cassert>
#include <iostream>

#include "config.h"
#include "configlib.h"
#include "server.h"
#include "clientlocal.h"

//------------------------------------------------------------------------------
void printHelp( const std::string & name ){
    std::cerr << name << " " << VERSION_MAJOR << "." << VERSION_MINOR
              << std::endl << std::endl;
    std::cerr << "Usage: " << name << " <config.lua>\n\n";
}

//------------------------------------------------------------------------------
int singleMain( int argc, char * argv[] ){
    if( argc != 2 ){
        assert( argc > 0 && "Error in command args" );
        printHelp( argv[0] );
        return EXIT_FAILURE;
    }

    if( !Config::load( argv[1] ) ){
        return EXIT_FAILURE;
    }

    auto server = Engine::Server::instance();

    Engine::Client * client = new Engine::ClientLocal();

    server->addClient( client );
    server->createAgents();
    server->run();

    return EXIT_SUCCESS;
}

#if defined(HAVE_MPI)
#include "mpi.h"
#include "clientremote.h"
#include "mpiworker.h"

//------------------------------------------------------------------------------
int multiMain( int argc, char * argv[] ){
    int nprocs, rank;

    MPI_Comm_size( MPI_COMM_WORLD, &nprocs );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    if( rank == 0 ){
        if( argc != 2 ){
            assert( argc > 0 && "Error in command args" );
            printHelp( argv[0] );
            return EXIT_FAILURE;
        }

        if( !Config::load( argv[1] ) ){
            return EXIT_FAILURE;
        }

        auto server = Engine::Server::instance();

        for( int i = 1 ; i < nprocs ; ++i ){
            Engine::Client * client = new Engine::ClientRemote( i );
            server->addClient( client );
        }

        server->createAgents();
        server->run();

    }else{
        if( argc != 2 ){
            return EXIT_FAILURE;
        }

        if( !Config::setDataDir( argv[1] ) ){
            return EXIT_FAILURE;
        }

        Engine::MPIWorker worker(rank);

        worker.run();
    }

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
int main( int argc, char * argv[] ){
    static_assert( sizeof(double) == sizeof(int64_t), 
                   "Double type isn't 64 bits" );
    MPI_Init( &argc, &argv );

    int nprocs;
    MPI_Comm_size( MPI_COMM_WORLD, &nprocs );

    int ret{ EXIT_SUCCESS };
    if( nprocs == 1 ){
        ret = singleMain( argc, argv );
    }else{
        ret = multiMain( argc, argv );
    }

    MPI_Finalize();

    return ret;
}

#else//!HAVE_MPI

//------------------------------------------------------------------------------
int main( int argc, char * argv[] ){
    return singleMain( argc, argv );
}

#endif//HAVE_MPI

//------------------------------------------------------------------------------

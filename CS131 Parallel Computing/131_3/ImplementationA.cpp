#include <omp.h>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <mpi.h>
 
int input_data(int argc, char* argv[]);
int output_data(int argc, char* argv[]);

// mpic++ -std=c++11 ImplementationA.cpp -o ImplementationA
// mpirun -np 4 ./ImplementationA test1.pgm adj1.txt output1.txt

/* Global variables, Look at their usage in main() */
int image_height;
int image_width;
int size_Of_Cluster;
int image_maxShades;
int inputImage[25000000];
int adjMatrix[25000000];
int outputImage[256];

/* **************** Change the function below if you need to ***************** */

int main(int argc, char* argv[])
{
    int process_Rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    int sizes;
    if (process_Rank == 0)
    {
        if (input_data(argc, argv) == 0)
        {
            MPI_Finalize();
            return 0;
        }
        sizes = (image_height*image_width)/size_Of_Cluster;
        for (int i = 1; i < size_Of_Cluster; ++i) {
            MPI_Send(&sizes, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&sizes, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int buf[sizes];
    int adj_buf[size_Of_Cluster];
    MPI_Scatter(inputImage, sizes, MPI_INT, buf, sizes, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(adjMatrix, size_Of_Cluster, MPI_INT, adj_buf, size_Of_Cluster, MPI_INT, 0, MPI_COMM_WORLD);

    int parent = process_Rank;
    int rec_value = process_Rank;
    int counts[256];
    int total_counts[256];
    for (int i=0; i < 256; ++i) {
        counts[i] = 0;
        total_counts[i] = 0;
    }

    if (process_Rank != 1) {
        MPI_Recv(&rec_value, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(counts, 256, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (parent == process_Rank) {
            parent = rec_value;
            adj_buf[parent] = 0;
        } 
    }
    
    for (int i = 0; i < size_Of_Cluster; ++i) {
        if (adj_buf[i] == 1) {
            MPI_Send(&process_Rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(counts, 256, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&rec_value, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(counts, 256, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int i=0; i < 256; ++i) {
                total_counts[i] += counts[i];
                counts[i] = 0;
            }
        }
    }
    
    for (int i=0; i < sizes; ++i) {
            total_counts[buf[i]] += 1;
    }

    if (process_Rank != 1) {
        MPI_Send(&process_Rank, 1, MPI_INT, parent, 0, MPI_COMM_WORLD);
        MPI_Send(total_counts, 256, MPI_INT, parent, 0, MPI_COMM_WORLD);
    }
    else {
        for (int i=0; i < 256; ++i) {
                outputImage[i] = total_counts[i];
        }
    }
    
    if (process_Rank == 1) {
        output_data(argc, argv);
    }

    MPI_Finalize();
    return 0;
}


int input_data(int argc, char* argv[]){
    if(argc != 4)
    {
        std::cout << "ERROR: Incorrect number of arguments. Format is: <Grayscale PGM image> <path to text file with the adjacency matrix> <output file name>" << std::endl;
        return 0;
    }
 
    std::ifstream file(argv[1]);
    if(!file.is_open())
    {
        std::cout << "ERROR: Could not open file " << argv[1] << std::endl;
        return 0;
    }


    /* ******Reading image into 2-D array below******** */

    std::string workString;
    /* Remove comments '#' and check image format */ 
    while(std::getline(file,workString))
    {
        if( workString.at(0) != '#' ){
            if( workString.at(1) != '2' ){
                std::cout << "Input image is not a valid PGM image" << std::endl;
                return 0;
            } else {
                break;
            }       
        } else {
            continue;
        }
    }
    /* Check image size */ 
    while(std::getline(file,workString))
    {
        if( workString.at(0) != '#' ){
            std::stringstream stream(workString);
            int n;
            stream >> n;
            image_width = n;
            stream >> n;
            image_height = n;
            break;
        } else {
            continue;
        }
    }

    /* Check image max shades */ 
    while(std::getline(file,workString))
    {
        if( workString.at(0) != '#' ){
            std::stringstream stream(workString);
            stream >> image_maxShades;
            break;
        } else {
            continue;
        }
    }
    /* Fill input image matrix */ 
    int pixel_val;
    for( int i = 0; i < image_height; i++ )
    {
        if( std::getline(file,workString) && workString.at(0) != '#' ){
            std::stringstream stream(workString);
            for( int j = 0; j < image_width; j++ ){
                if( !stream )
                    break;
                stream >> pixel_val;
                
                inputImage[(i*image_width) + j] = pixel_val;
            }
        } else {
            continue;
        }
    }

    /******Getting Adjacent Matrix******/
    std::ifstream file2(argv[2]);
    if(!file2.is_open())
    {
        std::cout << "ERROR: Could not open file " << argv[2] << std::endl;
        return 0;
    }

    /* ******Reading adjacent matrix into 2-D array below******** */
    /* Fill adjacency matrix */ 
    for( int i = 0; i < size_Of_Cluster; i++ )
    {
        if( std::getline(file2,workString) && workString.at(0) != '#' ){
            std::stringstream stream(workString);
            for( int j = 0; j < size_Of_Cluster; j++ ){
                if( !stream )
                    break;
                stream >> pixel_val;
                adjMatrix[(i*size_Of_Cluster) + j] = pixel_val;
            }
        } else {
            continue;
        }
    }
    return 1;
}

int output_data(int argc, char* argv[]){
    /* ********Start writing output to your file************ */
    std::ofstream ofile(argv[3]);
    if( ofile.is_open() )
    {
        for( int i = 0; i < 256; i++ )
        {
            ofile << outputImage[i] << "\n";
        }
    } else {
        std::cout << "ERROR: Could not open output file " << argv[3] << std::endl;
        return 0;
    }
    return 1;
}
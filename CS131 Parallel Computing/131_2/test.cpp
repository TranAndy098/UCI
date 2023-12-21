#include <omp.h>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>


int inputImage1[10000][10000];
int inputImage2[10000][10000];
int inputImage3[10000][10000];


int main(int argc, char* argv[]){
    int image_height = 460;
    int image_width = 475;

    std::ifstream file1("test5_answer.pgm");
    std::ifstream file2("test5s_output.pgm");
    std::ifstream file3("test5d_output.pgm");

    std::string workString1;


    int pixel_val;
    for( int i = 0; i < image_height; i++ )
    {
        if( std::getline(file1,workString1) && workString1.at(0) != '#' ){
            std::stringstream stream(workString1);
            for( int j = 0; j < image_width; j++ ){
                if( !stream )
                    break;
                stream >> pixel_val;
                inputImage1[i][j] = pixel_val;
            }
        } else {
            continue;
        }
    }


    std::string workString2;


    pixel_val = 0;
    for( int i = 0; i < image_height; i++ )
    {
        if( std::getline(file2,workString2) && workString2.at(0) != '#' ){
            std::stringstream stream(workString2);
            for( int j = 0; j < image_width; j++ ){
                if( !stream )
                    break;
                stream >> pixel_val;
                inputImage2[i][j] = pixel_val;
            }
        } else {
            continue;
        }
    }


    std::string workString3;


    pixel_val = 0;
    for( int i = 0; i < image_height; i++ )
    {
        if( std::getline(file3,workString3) && workString3.at(0) != '#' ){
            std::stringstream stream(workString3);
            for( int j = 0; j < image_width; j++ ){
                if( !stream )
                    break;
                stream >> pixel_val;
                inputImage3[i][j] = pixel_val;
            }
        } else {
            continue;
        }
    }

    

    for( int i = 0; i < image_height; i++ )
    {
        for( int j = 0; j < image_width; j++ ){
                if (inputImage1[i][j] != inputImage2[i][j]){
                    printf("static output is incorrect at %d, %d",i,j);
                }
                if (inputImage1[i][j] != inputImage3[i][j]){
                    printf("dynamic output is incorrect at %d, %d",i,j);
                }
            }
    }

    std::cout << "done";

    return 0;
}
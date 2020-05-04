#include"dataset.h"
#include<iostream>
#include<fstream>

using namespace std;

dataset::dataset(string fname){

    filename = fname;
    file.open(filename); // open the trainset file
    
    if( !file.is_open() )
        cout << "File error: " << fname << " could not be open.";

    else{

        int number_of_lines, number_of_columns;
        double aux;
        vector<double> temp; // store temporarily one line of data

        // the first line contains the number of lines and columns
        file >> number_of_lines >> number_of_columns; 

        shape[0] = number_of_lines;
        shape[1] = number_of_columns;

        for (size_t row = 0; row < number_of_lines; row++){

            for (size_t col = 0; col < number_of_columns; col++){
                file >> aux;
                temp.push_back(aux);
            }

            matrix.push_back(temp);    
            temp.resize(0); // clean vector temp
        }
    }
    
}

int* dataset::get_shape(){
    return shape;
}

vector<double> dataset::get_instance(int idx){
    return matrix[idx];
}
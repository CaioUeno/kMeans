#ifndef DATASET_H
#define DATASET_H

#include<fstream>
#include<vector>

using namespace std;

class dataset{
private:
    string filename; 
    fstream file; // trainset file
    vector< vector<double> > matrix; // data
    int shape[2];

public:
    dataset(string);
    int* get_shape();
    vector<double> get_instance(int);
    // ~dataset();
};

#endif
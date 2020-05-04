#ifndef KMEANS_H
#define KMEANS_H

#include<vector>
#include"dataset.h"

using namespace std;

class kmeans{
private:
    int n_clusters; // number of clusters
    vector< vector<double> > centroids;
    int* cluster; // array with cluster label for each instance
    dataset* trainset;

public:
    kmeans(int, string);
    int* select_first_centroids(int, int);
    double calc_distance(vector<double>, vector<double>);
    int fit(double);
    int* predict(string);
    vector< vector<double> > get_centroids();
    int* get_clusters();
    // ~kmeans();
};

#endif
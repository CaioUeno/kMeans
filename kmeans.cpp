#include"kmeans.h"
#include"dataset.h"
#include<cmath>
#include<limits>

using namespace std;

kmeans::kmeans(int number_of_clusters, string file){

    n_clusters = number_of_clusters;
    trainset = new dataset(file); // read the trainset

    int* trainset_shape = trainset->get_shape();
    cluster = new int[trainset_shape[0]];

}

int* kmeans::select_first_centroids(int number_of_clusters, int data_shape){

    // select number_of_clusters centroids "randomly"

    int* rand_array = new int[number_of_clusters];
    int div = (int) data_shape / number_of_clusters;

    for (size_t i = 0; i < number_of_clusters; i++)
        rand_array[i] = ((rand() % div) + (i * div));
    
    return rand_array;
}

double kmeans::calc_distance(vector<double> a, vector<double> b){

    // euclidean distance between two points

    if (a.size() != b.size())
        return -1.0;

    double dist = 0;
    for (size_t i = 0; i < a.size(); i++)
        dist += pow((a[i] - b[i]), 2);
    
    dist = sqrt(dist);

    return dist;
}

int kmeans::fit(double tolerance){

    int* trainset_shape = trainset->get_shape(); 

    // choosing random instances of data as centroids
    int* random_indexs = select_first_centroids(n_clusters, trainset_shape[0]); 

    // put them on a vector -> centroids
    for (size_t i = 0; i < n_clusters; i++)
        centroids.push_back(trainset->get_instance(random_indexs[i]));  

    double min_dist; // shortest distance 
    double dist; 
    int min_dist_centroid; // centroid with the shortest distance

    int instances_of_cluster; 
    vector<double> mean_cluster; // auxiliar centroid vector to store the new values
    double tol; // tolerance - based on movement of centroids
    int iterations = 0;
    
    do{
        iterations++;
        tol = 0;

        // find for each instance its closest centroid
        for (size_t i = 0; i < trainset_shape[0]; i++){

            min_dist = numeric_limits<double>::max();   
            for (size_t centroid = 0; centroid < n_clusters; centroid++){

                dist = calc_distance(trainset->get_instance(i), centroids[centroid]);
                if (dist < min_dist){
                    min_dist = dist;
                    min_dist_centroid = centroid;
                }
            }
            cluster[i] = min_dist_centroid;
        }

        // updating centroids
        for (size_t centroid = 0; centroid < n_clusters; centroid++){

            instances_of_cluster = 0; // number of instances that belongs to the centroid

            // initializing new centroid
            for (size_t dim = 0; dim < trainset_shape[1]; dim++)
                mean_cluster.push_back(0);
        
            for (size_t i = 0; i < trainset_shape[0]; i++){

                if (cluster[i] == centroid){
                    // only for those instances that belongs to the centroid's cluster

                    instances_of_cluster++;

                    for (size_t dim = 0; dim < trainset_shape[1]; dim++)
                        mean_cluster[dim] += trainset->get_instance(i)[dim];
                }

            }
            
            // after sum all instances, get the mean
            for (size_t dim = 0; dim < trainset_shape[1]; dim++)
                mean_cluster[dim] /= instances_of_cluster;

            // sum of displacement of centroid
            tol += calc_distance(centroids[centroid], mean_cluster);

            // update centroid's values
            for (size_t dim = 0; dim < trainset_shape[1]; dim++)
                centroids[centroid][dim] = mean_cluster[dim];
            
            // clean vector for next iteration
            mean_cluster.resize(0);
        }
        
    }while (tol > tolerance);
    
    return iterations;
       
}

int* kmeans::predict(string filen){

    dataset* testset = new dataset(filen); // open testset file
    int* testset_shape = testset->get_shape();
    int* test_clusters = new int[testset_shape[0]];

    double min_dist;
    double dist;
    int min_dist_centroid;


    // find for each instance its closest centroid
    for (size_t i = 0; i < testset_shape[0]; i++){

        min_dist = numeric_limits<double>::max();   
        for (size_t centroid = 0; centroid < n_clusters; centroid++){

            dist = calc_distance(testset->get_instance(i), centroids[centroid]);
            if (dist < min_dist){
                min_dist = dist;
                min_dist_centroid = centroid;
            }
                
        }
        test_clusters[i] = min_dist_centroid;
    }

    return test_clusters;
}

vector< vector<double> > kmeans::get_centroids(){
    return centroids;
}

int* kmeans::get_clusters(){
    return cluster;
}
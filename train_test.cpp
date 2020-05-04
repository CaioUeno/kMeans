#include<vector>
#include<iostream>
#include"dataset.h"
#include"kmeans.h"

using namespace std;

int main(int argc, char const *argv[]){

    if (argc < 3){
        throw std::invalid_argument("received less args");
    }
    
    kmeans kk(3, argv[1]);
    kk.fit(0.5);
    int* cl = kk.get_clusters();

    vector< vector<double> > cs = kk.get_centroids();

    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 4; j++)
            cout << cs[i][j] << " ";
        cout << endl;
    }

    int* test = kk.predict(argv[2]);

    for (size_t i = 0; i < 50; i++)
        cout << test[i] << " ";
    cout << endl;

    return 0;
}

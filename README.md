# kMeans
Implementation of kmeans algorithm.
There are two classes implemented: dataset and kmeans.

dataset.h contains the class and its functions headers, and dataset.cpp its implementations. 
The same thing with kmeans.

kmeans needs the number of clusters you want and the filename wich contains the data to be trained. This file must contains as first line the number of lines and columns, and then the data itself. *See trainset.txt and testset.txt as example*
It will select randomly k instances as first centroids and update them at each iteration over the data.
The iteration is over when the sum of displacement of all centroids is less than a tolerance - passed as argument to function fit().
The function predict() needs also a filename which contains the data to be predicted - same as trainset. 
As example of operation, see the file *train_test.cpp*, which train the algorithm and predict some data.

The data used is the iris dataset, it was preprocessed in the file *get_iris.py*


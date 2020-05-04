import pandas as pd
import numpy as np
import random
from sklearn import datasets

iris = datasets.load_iris()
X = pd.DataFrame(iris.data[:,:4])
X['4'] = iris.target
X = X.sample(frac=1)
trainset = X[:100].drop('4',axis=1)
testset = X[100:].drop('4',axis=1)
np.savetxt('trainset.txt', trainset, fmt='%.3f', 
            header=str(trainset.shape[0])+' '+str(trainset.shape[1]), comments='')
np.savetxt('testset.txt', testset, fmt='%.3f', 
            header=str(testset.shape[0])+' '+str(testset.shape[1]), comments='')
np.savetxt('testset_cluster.txt', X[100:]['4'], fmt='%d')

#include <iostream>

using namespace std;

/* This file defines the readfile function that builds the model
based on data given in a text file. Such a file should be as follow:

#### Comment with  the sharp symbol ####

#Ids are assigned for each line of definition, the first material gets
#its id to 0, similarly, the first node will have its ID to 0 then the second node
#will have its ID to 1 etc.

# Material definition
# Material number 0
M,Young Modulus(int),Poisson Ratio(double)

# Node definition
# Node 0
N, X(double), Y(double), Z(double)
# Node 1
N, X2(double), Y2(double), Z2(double)

# Bar Element Definition
B, Node1ID(int), Node2ID(Int), Section surface (double), MaterialID
*/

//=================================
// include guard
#ifndef __MESHER_INCLUDED__
#define __MESHER_INCLUDED__

//=================================
// forward declared dependencies
class BarElement;
class Node;
class ElasticMaterial;

//=================================
// included dependencies
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <Behaviors.h>
#include <Elements.h>

//=================================
// Prototypes

using namespace std;

/* This file defines the mesh class that builds and stores the model
based on data given in a text file. Such a file should be as follow:

#### Comment with  the sharp symbol ####

#Ids are assigned for each line of definition, the first material gets
#its id to 0, similarly, the first node will have its ID to 0 then the second node
#will have its ID to 1 etc.

# Material definition
# Material number 0
M, ID, Young Modulus(int),Poisson Ratio(double)

# Node definition
# Node 0
N,0,X(double),Y(double)
# Node 1
N,1,X2(double),Y2(double)

# Bar Element Definition
B,1,Node1ID(int),Node2ID(Int),Section surface (double),MaterialID
*/

/*  ###############################
    # Mesh class and its builders #
    ############################### */

class Mesh
{
    // Class used to define a mesh
    // it first stores each node
    // and then build the elements between the nodes

    public:

        // Attributes
        vector<Node> self_NodeArray;
        vector<BarElement> self_ElemArray;
        vector<ElasticMaterial> self_MatArray;
        MatrixXd self_MeshStiffnessMat;

        // BC attributes
        vector<float> self_Fvect;
        vector<int> self_knownF;
        vector<float> self_Uvect;
        vector<int> self_knownU;


        //Prototypes
        Mesh(string FileName);
        void assemble(void);
        void LoadBC(string);
        void Solve(void);
};


#endif // __MESHER_INCLUDED__

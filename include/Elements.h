//=================================
// include guard
#ifndef __ELEMENT_INCLUDED__
#define __ELEMENT_INCLUDED__


//=================================
// included dependencies
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <Behaviors.h>
#include <Elements.h>
#include <Eigen/Dense>
#include <functions.h>

//=================================
// forward declared dependencies
class BarElement;
class Node;

//Constants
const int SizeMat = 4;

//=================================
// Prototypes

using namespace Eigen;



/*  #######################
    ###    Node Class   ###
    ####################### */

class Node
{
    // Class used to define a Node
    // It stores the position of the node

    public:

        // Attributes

        Node(void);
        Node(double X, double Y, int ID);
        void Get_Position(double New_X, double New_Y);

        double self_X,self_Y;
        int self_ID;

};


/*  ###############################################
    ###    Bar Element Class and its builders   ###
    ############################################### */

class BarElement
{
    // Class used to define a bar element
    // It is defined by joining two Nodes Elements

    public:

        // Attributes

        double self_Section;                    // Surface of the section of the bar element
        int self_ID;                            // ID of the element
        double self_Length, self_angle;         // Length of the element
        Node self_Node1, self_Node2;            // Nodes, as defined by the Node class
        double self_strain, self_stress;        // Current stress and strain values in the BarElement
        ElasticMaterial self_Material;          // Assignation of the material to the bar element
        BarElement(Node Node1,Node Node2, double Section, ElasticMaterial Material, int ID);
        MatrixXd self_StiffnessMat = MatrixXd::Zero(SizeMat, SizeMat);
        MatrixXd GeneralizedMat(int NbNodes);
        void assignMaterial(ElasticMaterial);
        void UpdateStress(void);

};


#endif // __ELEMENT_INCLUDED__

#include <Behaviors.h>
#include <Eigen/Dense>
#include <math.h>
using namespace Eigen;


/*  ########################################
    ###    Node Class and its builders   ###
    ######################################## */

class Node
{
    // Class used to define a Node
    // It stores the position of the node

    public:

        // Attributes

        Node(void);
        Node(double X, double Y, int ID);

        double self_X,self_Y;
        int self_ID;

        // Methods

        void Get_Position(double New_X, double New_Y)
        {
            // Can be used to either update the coordinates of the nodes
            // or initiate these coordinates at the begining of the
            // Calculation.

            self_X = New_X;
            self_Y = New_Y;
        }

};

/*void  builder */
Node::Node(void)
{
    self_X = 0;
    self_Y = 0;
    self_ID = -1; // ID at -1 means that the node has not been initialized
    return;
}

/*Coordinates  builder */

Node::Node(double X,double Y,int ID)
{
    self_X = X;
    self_Y = Y;
    self_ID = ID;
    return;
}

//Overload of the orperator "<<" to print the coordinates of the node
// When the User want to print a Node
std::ostream &operator<<(std::ostream &os, Node const &m)
{
    return os <<"Node #"<<m.self_ID<<" at the coordinates: ("<<m.self_X<<","<<m.self_Y<<")";
}

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
        double self_Length;                          // Length of the element
        Node self_Node1, self_Node2;            // Nodes, as defined by the Node class
        double self_strain, self_stress;        // Current stress and strain values in the BarElement
        ElasticMaterial self_Material;          // Assignation of the material to the bar element
        BarElement(Node Node1,Node Node2, double Section, ElasticMaterial Material, int ID);
        MatrixXd self_StiffnessMat = MatrixXd::Zero(4, 4);


        // Methods

        /* Simply assign a given material to the element*/
        void assignMaterial(ElasticMaterial New_Material)
        {
            self_Material = New_Material;
        }

        /* Calculates the stress in the element using self_strain */
        void UpdateStress()
        {
           self_stress = self_Material.HookeLaw(self_strain);
        }

        /*Fills up the bar element stiffness matrix with the material properties*/
        void BuidStiffness(void)
        {

        }
};

/* builder */

BarElement::BarElement(Node Node1, Node Node2, double Section, ElasticMaterial Material, int ID)
{
    self_Node1 = Node1;
    self_Node2 = Node2;
    self_Length = sqrt(pow(Node1.self_X-Node2.self_X,2)+pow(Node1.self_Y-Node2.self_Y,2));
    self_Section = Section;
    self_Material = Material;
    self_ID = ID;
    double Factor = (self_Material.self_Young*self_Section)/self_Length;
    self_StiffnessMat(0,0)= Factor;
    self_StiffnessMat(2,2)= Factor;
    self_StiffnessMat(0,2)= -Factor;
    self_StiffnessMat(2,0)= -Factor;
    return;

}

//Overload of the orperator "<<" to print the coordinates of the node
// When the User want to print a Node
std::ostream &operator<<(std::ostream &os, BarElement const &m)
{
    return os <<"This is a bar element(ID: "<<m.self_ID<<") linking the\n"<<m.self_Node1<<" and "<<m.self_Node2<<"\nWith a section surface of "<<m.self_Section<<" square meters\nAnd a length of "<<m.self_Length;
}


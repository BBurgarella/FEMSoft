#include <Behaviors.h>

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
        Node(double X, double Y, double Z);

        double self_X,self_Y,self_Z;

        // Methods

        void Get_Position(double New_X, double New_Y, double New_Z)
        {
            // Can be used to either update the coordinates of the nodes
            // or initiate these coordinates at the begining of the
            // Calculation.

            self_X = New_X;
            self_Y = New_Y;
            self_Z = New_Z;
        }

};

/*void  builder */
Node::Node(void)
{
    self_X = 0;
    self_Y = 0;
    self_Z = 0;
    return;
}

/*Coordinates  builder */

Node::Node(double X,double Y,double Z)
{
    self_X = X;
    self_Y = Y;
    self_Z = Z;
    return;
}

//Overload of the orperator "<<" to print the coordinates of the node
// When the User want to print a Node
std::ostream &operator<<(std::ostream &os, Node const &m)
{
    return os <<"("<<m.self_X<<","<<m.self_Y<<","<<m.self_Z<<")";
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

        double self_Section; // Surface of the section of the bar element
        Node self_Node1, self_Node2; // Nodes, as defined by the Node class
        double self_strain, self_stress; // Current stress and strain values in the BarElement
        ElasticMaterial self_Material; // Assignation of the material to the bar element
        BarElement(Node Node1,Node Node2, double Section, ElasticMaterial Material);


        // Methods


        /* Build the element from two nodes */
        void Build_Bar_From_Nodes(Node New_Node1, Node New_Node2, double New_Section)
        {
            self_Node1 = New_Node1;
            self_Node2 = New_Node2;
            self_Section = New_Section;
        }

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
};

/* void builder */

BarElement::BarElement(Node Node1, Node Node2, double Section, ElasticMaterial Material)
{
    self_Node1 = Node1;
    self_Node2 = Node2;
    self_Section = Section;
    self_Material = Material;
    return;

}

//Overload of the orperator "<<" to print the coordinates of the node
// When the User want to print a Node
std::ostream &operator<<(std::ostream &os, BarElement const &m)
{
    return os <<"This is a bar element linking the nodes "<<m.self_Node1<<" and "<<m.self_Node2<<" With a section surface of "<<m.self_Section<<" square meters";
}


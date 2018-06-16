#include <Behaviors.h>

class Node
{
    // Class used to define a Node
    // It stores the position of the node

    public:

        // Attributes

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

//Overload of the orperator "<<" to print the coordinates of the node
// When the User want to print a Node
std::ostream &operator<<(std::ostream &os, Node const &m)
{
    return os <<"("<<m.self_X<<","<<m.self_Y<<","<<m.self_Z<<")";
}

class BarElement
{
    // Class used to define a bar element
    // It is defined by joining two Nodes Elements

    public:

        // Attributes

        double self_Section;
        Node self_Node1, self_Node2;

        // Methods

        void Build_Bar_From_Nodes(Node New_Node1, Node New_Node2, double New_Section)
        {
            self_Node1 = New_Node1;
            self_Node2 = New_Node2;
            self_Section = New_Section;
        }
};

#include <Elements.h>


/*  #######################
    ###    Node Class   ###
    ####################### */


void Node::Get_Position(double New_X, double New_Y)
{
    // Can be used to either update the coordinates of the nodes
    // or initiate these coordinates at the begining of the
    // Calculation.

    self_X = New_X;
    self_Y = New_Y;
}



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

/*  ##############################
    ###    Bar Element Class   ###
    ############################## */
// Methods

/* Simply assign a given material to the element*/
void BarElement::assignMaterial(ElasticMaterial New_Material)
{
    self_Material = New_Material;
}

/* Calculates the stress in the element using self_strain */
void BarElement::UpdateStress()
{
   self_stress = self_Material.HookeLaw(self_strain);
}

/*build the generalized stiffness matrix*/
/* There might be a faster way to do this but I need to come back on this later */
MatrixXd BarElement::GeneralizedMat(int NbNodes)
{
    MatrixXd tempStiffnessMat,tempStiffnessMat2;

    /* First, I initiate with an 2Nx4 empty matrix this allows the
    progressive filling of the generalized stiffness matrix by add lines
    of zero at the position of the nodes that are not used */
    tempStiffnessMat = MatrixXd::Zero(2*NbNodes, 4);
    for (int i=0;i<=2*NbNodes;i+=2)
    {
        if (self_Node1.self_ID == i/2)
        {
            /* If the cursor is on the nodes (here the first node) that are linked to the element,
            use the element stiffness matrix rows */
            tempStiffnessMat.row(i)=self_StiffnessMat.row(0);
            tempStiffnessMat.row(i+1)=self_StiffnessMat.row(1);
        }
        else if (self_Node2.self_ID == i/2)
        {
            /* If the cursor is on the nodes (here the second node) that are linked to the element,
            use the element stiffness matrix rows */
            tempStiffnessMat.row(i)=self_StiffnessMat.row(2);
            tempStiffnessMat.row(i+1)=self_StiffnessMat.row(3);
        }
    }
    /* Then, I initiate a second matrix with an 2Nx2N empty matrix this allows the
    progressive filling of the generalized stiffness matrix by add columns
    of zero at the position of the nodes that are not used */
    tempStiffnessMat2 = MatrixXd::Zero(2*NbNodes,2*NbNodes);
    for (int i=0;i<=2*NbNodes;i+=2)
    {
        if (self_Node1.self_ID == i/2)
        {
            /* If the cursor is on the nodes (here the first node) that are linked to the element,
            use the element stiffness matrix columns */
            tempStiffnessMat2.col(i)=tempStiffnessMat.col(0);
            tempStiffnessMat2.col(i+1)=tempStiffnessMat.col(1);
        }
        else if (self_Node2.self_ID == i/2)
        {
            /* If the cursor is on the nodes (here the second node) that are linked to the element,
            use the element stiffness matrix columns */
            tempStiffnessMat2.col(i)=tempStiffnessMat.col(2);
           tempStiffnessMat2.col(i+1)=tempStiffnessMat.col(3);
        }
    }
    return tempStiffnessMat2;

}


/* builder */

BarElement::BarElement(Node Node1, Node Node2, double Section, ElasticMaterial Material, int ID)
{
    // Init. the nodes
    self_Node1 = Node1;
    self_Node2 = Node2;

    // Calculates the angle of the element and its length
    self_Length = sqrt(pow(Node1.self_X-Node2.self_X,2)+pow(Node1.self_Y-Node2.self_Y,2));
    self_angle = atan((Node2.self_Y-Node1.self_Y)/(Node2.self_X-Node1.self_X));

    // Init. the section surface, material and ID
    self_Section = Section;
    self_Material = Material;
    self_ID = ID;

    /* Generation of the stiffness matrix of the element */
    double Factor = (self_Material.self_Young*self_Section)/self_Length;
    self_StiffnessMat(0,0)= Factor;
    self_StiffnessMat(2,2)= Factor;
    self_StiffnessMat(0,2)= -Factor;
    self_StiffnessMat(2,0)= -Factor;

    /* If the element angle is != 0, we need to rotate this matrix */
    MatrixXd RotMat=CalculateRotationMat(self_angle);
    MatrixXd RotMatT = RotMat.transpose();
    self_StiffnessMat = RotMatT*self_StiffnessMat*RotMat;
    return;

}

//Overload of the orperator "<<" to print the coordinates of the node
// When the User want to print a Node
std::ostream &operator<<(std::ostream &os, BarElement const &m)
{
    return os <<"This is a bar element(ID: "<<m.self_ID<<") linking the\n"<<m.self_Node1<<" and "<<m.self_Node2<<"\nWith a section surface of "<<m.self_Section<<" square meters\nAnd a length of "<<m.self_Length;
}


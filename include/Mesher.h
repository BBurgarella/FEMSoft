#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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


        // Methods definitions
        void assemble()
        /* This method creates the model stiffness matrix that will be used to solve the problem */
        {
            int NbNodes = self_NodeArray.size();
            self_MeshStiffnessMat = MatrixXd::Zero(2*NbNodes, 2*NbNodes); // Initiate with an 2Nx2N empty matrix
            for(int i=0;i<self_ElemArray.size();i++)
            {
                // Fills up the matrix using simple addition of the generalized matrices
                self_MeshStiffnessMat = self_MeshStiffnessMat + self_ElemArray[i].GeneralizedMat(NbNodes);
            }
        }

        void LoadBC(string FileName)
        /* This method read the boundary conditions from a file and creates the BC in the model */
        {
            int NbNodes = self_NodeArray.size();
            for (unsigned int i=0;i<2*NbNodes;i++)
            {
                self_Fvect.push_back(0);
                self_Uvect.push_back(0);
            }


            // Open file
            ifstream inputFile(FileName.c_str());
            string Line;
            if (inputFile.is_open())
            {
                while(!inputFile.eof())
                {
                    getline(inputFile,Line);

                    /* Definition of a new load */
                    if (Line[0]=='F')
                    {
                        // If the used wants to define a load on the X axis
                        if (Line[2]=='X')
                        {
                            vector<float> Init;
                            Init.clear();
                            // Remove the identification letter and the first comma
                            string ParseLine = Line.substr(4,Line.size());
                            stringstream ss(ParseLine);
                            while( ss.good() )
                            {
                                string substr;
                                float val;
                                getline( ss, substr, ',' );
                                std::istringstream(substr) >> val;
                                Init.push_back(val);
                            }
                            // Updates Uvect
                            self_Fvect[2*Init[0]] = Init[1];

                            // Pushes the coordinates of the known force in the known force vector
                            self_knownF.push_back(2*Init[0]);
                        }

                        // If the used wants to define a load on the Y axis
                        else if (Line[2]=='Y')
                        {
                            vector<float> Init;
                            Init.clear();
                            // Remove the identification letter and the first comma
                            string ParseLine = Line.substr(4,Line.size());
                            stringstream ss(ParseLine);
                            while( ss.good() )
                            {
                                string substr;
                                float val;
                                getline( ss, substr, ',' );
                                std::istringstream(substr) >> val;
                                Init.push_back(val);
                            }
                            // Updates Fvect
                            self_Fvect[2*Init[0]+1] = Init[1];

                            // Pushes the coordinates of the known force in the known force vector
                            self_knownF.push_back(2*Init[0]+1);
                        }
                    }
                    /* Definition of a new BC */
                    else if (Line[0]=='U')
                    {
                        // If the used wants to define a BC on the X axis
                        if (Line[2]=='X')
                        {
                            vector<float> Init;
                            Init.clear();
                            // Remove the identification letter and the first comma
                            string ParseLine = Line.substr(4,Line.size());
                            stringstream ss(ParseLine);
                            while( ss.good() )
                            {
                                string substr;
                                float val;
                                getline( ss, substr, ',' );
                                std::istringstream(substr) >> val;
                                Init.push_back(val);
                            }
                            // Updates Uvect
                            self_Uvect[2*Init[0]] = Init[1];

                            // Pushes the coordinates of the known displacement in the knownU vector
                            self_knownU.push_back(2*Init[0]);
                        }

                        // If the used wants to define a BC on the Y axis
                        else if (Line[2]=='Y')
                        {
                            vector<float> Init;
                            Init.clear();
                            // Remove the identification letter and the first comma
                            string ParseLine = Line.substr(4,Line.size());
                            stringstream ss(ParseLine);
                            while( ss.good() )
                            {
                                string substr;
                                float val;
                                getline( ss, substr, ',' );
                                std::istringstream(substr) >> val;
                                Init.push_back(val);
                            }
                            // Updates Uvect
                            self_Uvect[2*Init[0]+1] = Init[1];

                            // Pushes the coordinates of the known force in the known force vector
                            self_knownU.push_back(2*Init[0]+1);
                        }
                    }
                }
                if (self_knownU.size()+self_knownF.size()==2*NbNodes)
                {
                    std::cout<<"The entered loading and boundary conditions are correct"<<std::endl;
                }
                else
                {
                    std::cout<<"Warning ! There are nodes in your model without either BC or Load"<<std::endl;
                }
            }
            return;
        }


};

Mesh::Mesh(string FileName)
{
    // Open file
    ifstream inputFile(FileName.c_str());
    string Line;
    vector<float> Init;
    if (inputFile.is_open())
    {
        while(!inputFile.eof())
        {
            getline(inputFile,Line);

            /* Definition of a new material */
            if (Line[0]=='M')
            {
                // Remove the identification letter and the first comma
                string ParseLine = Line.substr(2,Line.size());
                stringstream ss(ParseLine);
                while( ss.good() )
                {
                    string substr;
                    float val;
                    getline( ss, substr, ',' );
                    std::istringstream(substr) >> val;
                    Init.push_back(val);
                }
                // Creates the new material
                ElasticMaterial New_Mat(Init[1],Init[2],Init[0]);
                Init.clear();
                // Pushes the material in the Material vector
                self_MatArray.push_back(New_Mat);
            }

            /* Definition of a new Node */
            if (Line[0]=='N')
            {
                // Remove the identification letter and the first comma
                string ParseLine = Line.substr(2,Line.size());
                stringstream ss(ParseLine);
                while( ss.good() )
                {
                    string substr;
                    float val;
                    getline( ss, substr, ',' );
                    std::istringstream(substr) >> val;
                    Init.push_back(val);
                }
                // Creates the new material
                Node New_Node(Init[1],Init[2],Init[0]);
                Init.clear();
                // Pushes the material in the Material vector
                self_NodeArray.push_back(New_Node);
            }
            /* Definition of a new bar element */
            if (Line[0]=='B')
            {
                // Remove the identification letter and the first comma
                string ParseLine = Line.substr(2,Line.size());
                stringstream ss(ParseLine);
                while( ss.good() )
                {
                    string substr;
                    float val;
                    getline( ss, substr, ',' );
                    std::istringstream(substr) >> val;
                    Init.push_back(val);
                }
                // Creates the new material
                BarElement New_Bar(self_NodeArray[Init[1]],self_NodeArray[Init[2]],Init[3],self_MatArray[Init[4]],Init[0]);
                Init.clear();
                // Pushes the material in the Material vector
                self_ElemArray.push_back(New_Bar);
            }
        }
    }
}

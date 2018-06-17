#include <Mesher.h>

/*  #######################
    ###    Mesh Class   ###
    ####################### */
// Methods definitions
void Mesh::assemble()
/* This method creates the model stiffness matrix that will be used to solve the problem */
{
    int NbNodes = self_NodeArray.size();
    self_MeshStiffnessMat = MatrixXd::Zero(2*NbNodes, 2*NbNodes); // Initiate with an 2Nx2N empty matrix
    for(unsigned int i=0;i<self_ElemArray.size();i++)
    {
        // Fills up the matrix using simple addition of the generalized matrices
        self_MeshStiffnessMat = self_MeshStiffnessMat + self_ElemArray[i].GeneralizedMat(NbNodes);
    }
}

void Mesh::LoadBC(string FileName)
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

            std::cout<<" Loading and Boundary conditions are correct "<<std::endl;
            std::cout << "---------------------------------------------"<<std::endl;
        }
        else
        {
            std::cout<<"#################################################################"<<std::endl;
            std::cout<<"Warning ! There are nodes in your model without either BC or Load"<<std::endl;
            std::cout<<"#################################################################"<<std::endl;
        }
    }
    return;
}


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
        std::cout <<" Model definition file successfully loaded   "<<endl;
    }
    else
    {
        std::cout <<"Error loading the model definition file"<<endl;
    }
}

void Mesh::Solve(void)
/* Solves the FEM problem */
{
    // First I need to take the block in the matrix corresponding to the known U
    int NbNodes = self_NodeArray.size();
    int Tempsize = self_knownU.size();
    int TempsizeF = self_knownF.size();
    MatrixXd TempMat,TempF,TempU,LocalUVect,LocalFVect;
    TempMat = MatrixXd::Zero(2*NbNodes,TempsizeF);
    // then fills the empty matrix with the corresponding columns
    for (unsigned int i = 0;i<TempsizeF;i++)
    {
        TempMat.col(i)=self_MeshStiffnessMat.col(self_knownF[i]);
    }
    // The next step is similar but with the known F
    MatrixXd TempMat2;
    TempMat2 = MatrixXd::Zero(TempsizeF,TempsizeF);
    // then fills the empty matrix with the corresponding rows
    TempF = MatrixXd::Zero(TempsizeF ,1);
    for (unsigned int i = 0;i<TempsizeF;i++)
    {
        TempMat2.row(i)=TempMat.row(self_knownF[i]);
        TempF(i) = self_Fvect[self_knownF[i]];
    }
    /* We now have a system with the form:
    [F](known) = [K](known)*[U](unknown)
    which can be solved as
    [K]^(-1)*[F] = [U] */
    TempU = TempMat2.inverse()*TempF;

    // Repopulate the U vector with the new found values
    for (unsigned int i = 0;i<TempsizeF;i++)
    {
        self_Uvect[self_knownF[i]]=TempU(i);
    }

    // I need the U vector as a (N,1) matrix to calculate the forces
    LocalUVect = MatrixXd(self_Uvect.size(),1);
     for (unsigned int i = 0; i<self_Uvect.size() ;i++)
    {
        LocalUVect(i)=self_Uvect[i];
    }

    // finally, I can calculate the forces with a simple [F] = [K]*[U]
    LocalFVect = self_MeshStiffnessMat*LocalUVect;

    // Repopulate the F vector with the new found values
    for (unsigned int i = 0;i<TempsizeF;i++)
    {
        self_Fvect[self_knownU[i]]=LocalFVect(self_knownU[i]);
    }
    cout << "              Computation done !             "<<endl;
    cout << "---------------------------------------------"<<endl<<endl;
}


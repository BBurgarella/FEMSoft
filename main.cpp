#include <iostream>
#include <Eigen/Dense>
#include <Elements.h>
#include <Mesher.h>
#include <functions.h>
#include <Behaviors.h>
#include <stdlib.h>

//#define debug
#define release


using namespace Eigen;
using namespace std;



int main()
{
    cout << "#############################################"<<endl;
    cout << "#   Welcome in Boris Burgarella's FEM soft  #"<<endl;
    cout << "#     This soft was written in C++ as a     #"<<endl;
    cout << "#                 training                  #"<<endl;
    cout << "#############################################"<<endl<<endl;
    cout << "---------------------------------------------"<<endl;
    cout << "                Loading model                "<<endl<<endl;
    string filename("Model.ent");
    Mesh TestMesh(filename);
    cout << "---------------------------------------------"<<endl<<endl;
    cout << "        Number of nodes in the model:        "<<endl;
    int NbNodes =  TestMesh.self_NodeArray.size();
    cout << "--------------------> "<<NbNodes<<endl;
    cout << "        Number of elements in the model:        "<<endl;
    int NbEl =  TestMesh.self_ElemArray.size();
    cout << "--------------------> "<<NbEl<<endl;
    //cout << TestMesh.self_ElemArray[0].self_StiffnessMat <<endl;
    TestMesh.assemble();
    cout << "---------------------------------------------"<<endl;
    cout << "          Loading Boundary Conditions        "<<endl<<endl;
    TestMesh.LoadBC(filename);
    cout << "  Forces imposed at positions (force vector) " << endl<<"--------------------> ";
    printVectN(TestMesh.self_knownF);
    cout << "       U imposed at positions (U vector)     " << endl<<"--------------------> ";
    printVectN(TestMesh.self_knownU);
    // Pause to let the used read the text

    cout << "---------------------------------------------"<<endl;
    cout << "                   Solving                   "<<endl<<endl;
    TestMesh.Solve();
    cout << "                 Final F Vector             " << endl<<"--------------------> ";
    printVectf(TestMesh.self_Fvect);
    cout << "                 Final U Vector             " << endl<<"--------------------> ";
    printVectf(TestMesh.self_Uvect);
    /*work in progress*/


    cout <<endl<< "---------------------------------------------"<<endl;
    cout << "             Sucessfull computation          "<<endl;
    cout << "                Have a nice day !            "<<endl;
    cout << "---------------------------------------------"<<endl;
    cout << "          Enter 'exit' to end program        "<<endl;
    string in;

#ifdef release
	while ((std::cin >> in) && (in != "exit"))
	{
        cout << "          Enter 'exit' to end program        "<<endl;
	}
#endif // release
    return 0;
}


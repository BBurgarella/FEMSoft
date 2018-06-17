#include <iostream>
#include <Eigen/Dense>
#include <Elements.h>
#include <Mesher.h>

using namespace Eigen;
using namespace std;



int main()
{
    string filename("Model.ent");
    Mesh TestMesh(filename);
    //cout << TestMesh.self_ElemArray[0].self_StiffnessMat <<endl;
    TestMesh.assemble();
    TestMesh.LoadBC(filename);
    cout << "Imposed Forces" << endl;
    printVectf(TestMesh.self_Fvect);
    cout << "Forces imposed at positions (in the force vector)" << endl;
    printVectN(TestMesh.self_knownF);
    cout << "Imposed U" << endl;
    printVectf(TestMesh.self_Uvect);
    cout << "U imposed at nodes at positions (in the U vector)" << endl;
    printVectN(TestMesh.self_knownU);

    return 0;
}


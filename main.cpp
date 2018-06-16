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
    cout <<"Module d'Young du premier materiau: "<< TestMesh.self_MatArray[0].self_Young <<" Pa"<<endl;
    cout <<"Coordonnees du premier Noeud: "<< TestMesh.self_NodeArray[0] <<endl;
    cout <<"premier Element: "<< TestMesh.self_ElemArray[0] <<endl;
    cout << TestMesh.self_ElemArray[0].self_StiffnessMat <<endl;
    TestMesh.assemble();
    cout << TestMesh.self_MeshStiffnessMat <<endl;
}


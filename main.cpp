#include <iostream>
#include <Eigen/Dense>
#include <Elements.h>
using namespace Eigen;
using namespace std;


int main()
{
  ElasticMaterial Alu(70,0.2);
  //Print the material properties
  cout << "Module d'Young de l'alu: "<<Alu.self_Young<< " GPa" <<endl;
  cout << "Coefficient de poisson de l'alu: "<<Alu.self_Nu<<endl;

  Node Test1(0,0,0);
  Node Test2(1,1,1);

  cout << "Noeud 1: "<< Test1 <<endl;
  cout << "Noeud 2: "<< Test2 <<endl;

  BarElement DesBarres(Test1,Test2,1,Alu);
  cout << DesBarres <<endl;
}


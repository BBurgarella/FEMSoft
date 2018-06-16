#include <iostream>
#include <Eigen/Dense>
#include <Elements.h>
using namespace Eigen;
using namespace std;


int main()
{
  Elastic Acier;
  Acier.Get_Params(250,0.3);
  //Print the material properties
  cout << "Module d'Young: "<<Acier.self_Young<< " GPa" <<endl;
  cout << "Coefficient de poisson: "<<Acier.self_Nu<<endl;
    Acier.Get_Params(10,0.1);
  //Print the material properties
  cout << "Module d'Young: "<<Acier.self_Young<< " GPa" <<endl;
  cout << "Coefficient de poisson: "<<Acier.self_Nu<<endl;

  Node Test;
  Test.self_X = 0;
  Test.self_Y = 0.123;
  Test.self_Z = 155;

  cout << Test <<endl;
}


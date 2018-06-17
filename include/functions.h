#include <iostream>
#include <math.h>
#include <vector>

using namespace Eigen;

// Prototypes

MatrixXd CalculateRotationMat(double angle);
void printVectf(std::vector<float> vect);
void printVectf(std::vector<int> vect);

// Definitions

void printVectf(std::vector<float> vect)
{
    std::cout<<"(";
    for (int i=0;i<vect.size()-1;i++)
    {
        std::cout<<vect[i]<<",";
    }
    std::cout<<vect[vect.size()-1]<<")"<<std::endl;
}

void printVectN(std::vector<int> vect)
{
    std::cout<<"(";
    for (int i=0;i<vect.size()-1;i++)
    {
        std::cout<<vect[i]<<",";
    }
    std::cout<<vect[vect.size()-1]<<")"<<std::endl;
}

MatrixXd CalculateRotationMat(double angle)
// Computes the rotation matrix from an angle
{
    MatrixXd tempR = MatrixXd::Zero(4, 4);
    tempR(0,0) = cos(angle);
    tempR(0,1) = sin(angle);
    tempR(1,0) = -sin(angle);
    tempR(1,1) = cos(angle);
    tempR(2,2) = cos(angle);
    tempR(3,2) = -sin(angle);
    tempR(2,3) = sin(angle);
    tempR(3,3) = cos(angle);
    return tempR;
}

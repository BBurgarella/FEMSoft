//=================================
// include guard
#ifndef __FUNCTIONS_INCLUDED__
#define __FUNCTIONS_INCLUDED__

//=================================
// forward declared dependencies
// None Here

//=================================
// included dependencies
#include <vector>
#include <Eigen/Dense>
#include <math.h>
#include <iostream>

//=================================
// Prototypes


using namespace Eigen;

MatrixXd CalculateRotationMat(double angle);
void printVectf(std::vector<float> vect);
void printVectN(std::vector<int> vect);

#endif // __FUNCTIONS_INCLUDED__


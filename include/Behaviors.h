//=================================
// include guard
#ifndef __BEHAVIOR_INCLUDED__
#define __BEHAVIOR_INCLUDED__

//=================================
// forward declared dependencies
class ElasticMaterial;

//=================================
// included dependencies
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

//=================================
// Prototypes

class ElasticMaterial
{
    public:

        // Attributes

        int self_Young;
        int self_ID;
        double self_Nu;
        ElasticMaterial(void);
        ElasticMaterial(int Young, double Nu, int MatID);
        int Get_Params(int New_Young, double New_Nu);
        double HookeLaw(double strain);
};

#endif // __BEHAVIORS_INCLUDED__

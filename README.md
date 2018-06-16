# FEMSoft
A simple C++ FEM soft that I programed to train C++

To create a model, you have to use a text file named **Model.ent** (the ability to use different names will be implemented later) This file defines the mesh class that builds and stores the model based on data given in a text file. Such a file should be as follow:

```
#### Comment with  the sharp symbol ####

#Ids are assigned for each line of definition, the first material gets
#its id to 0, similarly, the first node will have its ID to 0 then the second node
#will have its ID to 1 etc.

# Material definition
# Material number 0
M, ID, Young Modulus(int),Poisson Ratio(double)

# Node definition
# Node 0
N,0,X(double),Y(double),Z(double)
# Node 1
N,1,X2(double),Y2(double),Z2(double)

# Bar Element Definition
B,1,Node1ID(int),Node2ID(Int),Section surface (double),MaterialID
```

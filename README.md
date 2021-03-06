# FEMSoft
A simple C++ Finite Element Modeling soft that I programed to train C++, This soft allows calculations on structures made from truss elements

# Dependencies
- Eigen (eigen.tuxfamily.org) -> used for linear algebra

# What remains to be done:
- Implement a simple function to get the results in a text file
- It would be fun to parallelize this code but I didn't have time yet

# How to use it
The binary file available in the bin/release folder should be all you need if you only want to play with a FE Model
To create a model, you have to use a text file named **Model.ent** (the ability to use different names will be implemented later) This file defines the mesh class that builds and stores the model and should be placed in the same folder as the .exe. Such a file should be as follow:
```
#### Simple model to test the mesher ####

#    Example case:
#
#
#           2 
#         / |
#        0__1
#        
#   Node 0 and 1 are pinned and there is a force on the node 3
#   -----> Fx = 2; Fy = 1
#   the material used is a fictional material with a young modulus equal to 1
#   and the section of the bar elements is also 1

#####################################################################
#         Warning ! be careful on having a well defined model       #
#                     If the boundary conditions are not            #
#                  well defined, the matrix will be singular        #
#####################################################################

# Fictional material
# M, ID, Young,Nu
M,0,1,0.5

# Nodes
# N,ID,X,Y
N,0,0,0
N,1,1,0
N,2,1,1


# Elements
# B,ID,Node1,Node2,Section,Material
B,0,0,1,1,0
B,1,1,2,1,0
B,2,2,0,1,0

# Boundary conditions
# U,X or Y,NodeID,value
U,X,0,0
U,Y,0,0
U,X,1,0
U,Y,1,0

# Loading conditions
# F,X or Y,NodeID,value
F,X,2,2
F,Y,2,1

```

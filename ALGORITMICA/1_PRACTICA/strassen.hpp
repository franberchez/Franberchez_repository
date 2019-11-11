#ifndef STRASSEN_
#define STRASSEN_

#include <iostream>
#include <vector>

using namespace std;

void strassen(vector< vector<double> > &A, 
              vector< vector<double> > &B, 
              vector< vector<double> > &C, unsigned int tam);
#endif
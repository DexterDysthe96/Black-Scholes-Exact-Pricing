// ExactPricingMethodsGlobalFunctions.hpp
//
// This header file contains the declaration of two functions which will be utilized in TestExactSolutions.cpp in order to enhance
// the usability of our classes. 

#ifndef EPMGlobalFunctions_H
#define EPMGlobalFunctions

#include <vector>
#include <iostream>
using namespace std;

ostream& operator << (ostream& os, const vector<double> vec);		// This will allow the user to output vectors to the console directly

vector<double> mesher(double start, double end, double h);			// Returns a vector of doubles whose 1st entry equals start, last entry equals
																	// end, and whose j^th entry equals a+(j-1)*h. Requires (start - end)/h to be
																	// an integer. 
#endif
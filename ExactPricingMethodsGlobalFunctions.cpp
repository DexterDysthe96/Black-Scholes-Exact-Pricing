// ExactPricingMethodsGlobalFunctions.cpp

#include "ExactPricingMethodsGlobalFunctions.hpp"

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Overloaded << operator to print vector<double> objects directly.
ostream& operator << (ostream& os, const vector<double> vec)
{
	os << "(";
	for (vector<double>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		os << *it;
		if (it != vec.end() - 1)
			os << ", ";
	}
	os << ")" << endl;

	return os;
}

// Create a vector starting with the value stored in start and increment each successive value by h. 
// When i = (end - start) / h, the value we add to the vector is the value stored in end. We then 
// return the meshed vector.
vector<double> mesher(double start, double end, double h)
{
	double amtOfMeshPts = (end - start) / h;
	vector<double> meshedVec;
	for (int i = 0; i <= amtOfMeshPts; i++)
		meshedVec.push_back(start + (i * h));

	if (meshedVec.back() != end)
		meshedVec.push_back(end);

	return meshedVec;
}

// ParamMatrix.hpp
//
// The purpose of the ParamMatrix class is to extend the functionality of the Option class hierarchy so as to be able to
// handle multiple options of potentially different types at the same time i.e. to be able to compute the price or Greeks
// of a vector of Options objects. In order to allow the user to specify different parameters (S/sig/r/b) for each option, 
// we use a matrix private data member in order to store a vector of Option parameter vectors. That is, each row in the
// matrix represents a different Option object along with a different set of parameter values that will be used when working 
// with the pricing and Greeks functions defined in the Option class hiearchy. In tandem with the matrix private member,
// we use a Option shared pointer vector in order to store the address of each Option object represented in the matrix. We
// do this in order to simplify the code in the Price(), Delta(), and Gamma() member functions defined in ParamMatrix.cpp. 

#ifndef ParamMatrix_H
#define ParamMatrix_H

#include "Option.hpp"

#include <boost/shared_ptr.hpp>
typedef boost::shared_ptr<Option> OptionPtr;

#include <vector>
using namespace std;

class ParamMatrix
{
private:
	vector< vector<double> > paramMat;					// Stores a matrix of option parameters. Each row in the matrix can hold parameters for either
														// Euro options or PAMOs, and in the future any other derived option object. The number of entries
														// in a given row depends on whether that row represents a Euro option, in which case there will
														// be 7 entries (S, sig, r, b, Put/Call, K, T), or a PAMO, in which case there will be 6 entries 
														// (S, sig, r, b, Put/Call, K)

	vector<OptionPtr> optVect;							// This vector stores pointers to Option objects that are represented by rows in the matrix
														// paramMat. The j^th entry of optVect points to the Option object represented by the j^th
														// row of the matrix paramMat. It is important to note that only the last 2 (for PAMOs) and
														// last 3 (for Euro options) entries in each row are used to create an Option object, the 
														// other entries are parameters for member functions defined in the Option classes.

public:
	// Constructors and Destructor
	ParamMatrix();										// Default constructor
	ParamMatrix(const ParamMatrix& copyParamMat);		// Copy constructor
	virtual ~ParamMatrix();								// Destructor
									
								    // Constructors for Perpetual American matrices \\
			     // The purpose of each of the below constructors is described in detail in ParamMatrix.cpp \\

	ParamMatrix(const vector<double>& spot, double vol, double rate, double carry, char optionType, double strike);
	ParamMatrix(double spot, const vector<double>& vol, double rate, double carry, char optionType, double strike);
	ParamMatrix(double spot, double vol, const vector<double>& rate, double carry, char optionType, double strike);
	ParamMatrix(double spot, double vol, double rate, const vector<double>& carry, char optionType, double strike);
	ParamMatrix(double spot, double vol, double rate, double carry, char optionType, const vector<double>& strike);
										
										 // Constructors for European matrices \\
				// The purpose of each of the below constructors is described in detail in ParamMatrix.cpp  \\

	ParamMatrix(const vector<double>& spot, double vol, double rate, double carry, char optionType, double strike, double timeTillMat);
	ParamMatrix(double spot, const vector<double>& vol, double rate, double carry, char optionType, double strike, double timeTillMat);
	ParamMatrix(double spot, double vol, const vector<double>& rate, double carry, char optionType, double strike, double timeTillMat);
	ParamMatrix(double spot, double vol, double rate, const vector<double>& carry, char optionType, double strike, double timeTillMat);
	ParamMatrix(double spot, double vol, double rate, double carry, char optionType, const vector<double>& strike, double timeTillMat);
	ParamMatrix(double spot, double vol, double rate, double carry, char optionType, double strike, const vector<double>& timeTillMat);


	// Accessor Functions
	vector<double> Price() const;								// Returns a vector of prices corresponding to the options pointed to by the entries of optVec
	vector<double> Delta() const;								// Returns a vector of deltas corresponding to the options pointed to by the entries of optVec
	vector<double> DivDiffDelta(double h) const;				// Returns an vector of approximate deltas corresponding to a step size of h using centered 
																// divided differences		
	vector<double> Gamma() const;								// Returns a vector of gammas corresponding to the options pointed to by the entries of optVec
	vector<double> DivDiffGamma(double h) const;				// Returns an vector of approximate gammas corresponding to a step size of h using centered 
																// divided differences


	// Modifier Functions
	virtual void PushRow(vector<double>& newRow);				// Adds a row to the private member paramMat and populates it with the vector newRow -- at the
																// moment, newRow.size() can only equal 6 (for PAMOs) or 7 (for Euro options) 

	ParamMatrix& operator = (const ParamMatrix& newMat);		// Assignment operator	

};


#endif

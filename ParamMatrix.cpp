// ParamMatrix.cpp

#include "ParamMatrix.hpp"
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"

#include <vector>


// --------------------------------------------------------------------- Constructors and Destructor ------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Default constructor
ParamMatrix::ParamMatrix()
{
}

										// ------------------ Constructors for Perpetual American Option Matrices ------------------ \\
			  // Each of the following constructors in this subsection are intended to initialize the matrix private member paramMat by holding all parameter's \\
			  // constant except for one, which will vary according to the entries of the input vector. All matrices constructed in this subsection will have 6 \\
              // columns, 1 for each of the input parameters to the constructor, and as such each of the rows represents a PAMO. In each constructor we	also    \\
			  // populate the vector private member optVect, 1 entry for each row in the matrix paramMat, where the PAMO is constructed according to the last	\\
			  // 2 entries in each row of the matrix paramMat.																								    \\ 

// Constructs a matrix of PAMO parameters with spot.size() many rows. The i^th row of the resulting matrix paramMat will be 
// (spot[i], vol, rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike). That is, this constructor
// is used when the user wishes to only vary the underlying spot price but wishes to keep all other parameters fixed.
ParamMatrix::ParamMatrix(const vector<double>& spot, double vol, double rate, double carry, char optionType, double strike)
{
	for (vector<double>::const_iterator it = spot.begin(); it != spot.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ *it, vol, rate, carry, 1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ *it, vol, rate, carry, -1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
	//  else 
	//		throw illegalOptionTypeException(optionType)
	}
}

// Constructs a matrix of PAMO parameters with vol.size() many rows. The i^th row of the resulting matrix paramMat will be 
// (spot, vol[i], rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike). That is, this constructor
// is used when the user wishes to only vary the volatility parameter but wishes to keep all other parameters fixed.
ParamMatrix::ParamMatrix(double spot, const vector<double>& vol, double rate, double carry, char optionType, double strike)
{
	for (vector<double>::const_iterator it = vol.begin(); it != vol.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, *it, rate, carry, 1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, *it, rate, carry, -1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
	//  else 
	//		throw illegalOtionTypeException(optionType)
	}
}

// Constructs a matrix of PAMO parameters with rate.size() many rows. The i^th row of the resulting matrix paramMat will be 
// (spot, vol, rate[i], carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike). That is, this constructor
// is used when the user wishes to only vary the money market interest rate but wishes to keep all other parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, const vector<double>& rate, double carry, char optionType, double strike)
{
	for (vector<double>::const_iterator it = rate.begin(); it != rate.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, *it, carry, 1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, *it, carry, -1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
	//  else 
	//		throw illegalOtionTypeException(optionType)
	}
}

// Constructs a matrix of PAMO parameters with carry.size() many rows. The i^th row of the resulting matrix paramMat will be 
// (spot, vol, rate, carry[i], +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike). That is, this constructor
// is used when the user wishes to only vary the cost-of-carry of the underlying but wishes to keep all other parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, double rate, const vector<double>& carry, char optionType, double strike)
{
	for (vector<double>::const_iterator it = carry.begin(); it != carry.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, rate, *it, 1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, rate, *it, -1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, strike)));
		}
	//  else 
	//		throw illegalOtionTypeException(optionType)
	}
}

// Constructs a matrix of PAMO parameters with strike.size() many rows. The i^th row of the resulting matrix paramMat will be 
// (spot, vol, rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike[i]). That is, this constructor
// is used when the user wishes to only vary the strike price of the option but wishes to keep all other parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, double rate, double carry, char optionType, const vector<double>& strike)
{
	for (vector<double>::const_iterator it = strike.begin(); it != strike.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, rate, carry, 1, *it };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, *it)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, rate, carry, -1, *it };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new PerpetualAmericanOption(optionType, *it)));
		}
	//  else 
	//		throw IllegalOptionTypeException(optionType)
	}
}


										// ------------------ Constructors for European Option Matrices ------------------ \\
			  // Each of the following constructors in this subsection are intended to initialize the matrix private member paramMat by holding all parameter's \\
			  // constant except for one, which varies according to the entries of the input vector. All matrices constructed in this subsection will have 7    \\
              // columns, 1 for each of the input parameters to the constructor, and as such each of the rows represents a Euro option.	In each constructor we	\\
			  // also populate the vector private member optVect, 1 entry for each row in the matrix paramMat, where the Euro option is constructed according   \\
			  // to the last 3 entries in each row of the matrix paramMat.																						\\ 

// Constructs a matrix of Euro option parameters with spot.size() many rows. The i^th row of the resulting matrix paramMat
// will be (spot[i], vol, rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike, timeTillMat). That 
// is, this constructor is used when the user wishes to only vary the strike price of the option but wishes to keep all other 
// parameters fixed.
ParamMatrix::ParamMatrix(const vector<double>& spot, double vol, double rate, double carry, char optionType, double strike, double timeTillMat)
{
	for (vector<double>::const_iterator it = spot.begin(); it != spot.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ *it, vol, rate, carry, 1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ *it, vol, rate, carry, -1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		//  else 
		//		throw IllegalOptionTypeException(optionType)
	}
}

// Constructs a matrix of Euro option parameters with vol.size() many rows. The i^th row of the resulting matrix paramMat
// will be (spot, vol[i], rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike, timeTillMat). That 
// is, this constructor is used when the user wishes to only vary the volatility parameter of the option but wishes to keep
// all other parameters fixed.
ParamMatrix::ParamMatrix(double spot, const vector<double>& vol, double rate, double carry, char optionType, double strike, double timeTillMat)
{
	for (vector<double>::const_iterator it = vol.begin(); it != vol.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, *it, rate, carry, 1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, *it, rate, carry, -1, strike };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		//  else 
		//		throw IllegalOptionTypeException(optionType)
	}
}

// Constructs a matrix of Euro option parameters with rate.size() many rows. The i^th row of the resulting matrix paramMat
// will be (spot, vol, rate[i], carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike, timeTillMat). That 
// is, this constructor is used when the user wishes to only vary the money market interest rate but wishes to keep all other 
// parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, const vector<double>& rate, double carry, char optionType, double strike, double timeTillMat)
{
	for (vector<double>::const_iterator it = rate.begin(); it != rate.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, *it, carry, 1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, *it, carry, -1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		//  else 
		//		throw IllegalOptionTypeException(optionType)
	}
}

// Constructs a matrix of Euro option parameters with carry.size() many rows. The i^th row of the resulting matrix paramMat
// will be (spot, vol, rate, carry[i], +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike, timeTillMat). That 
// is, this constructor is used when the user wishes to only vary the cost-of-carry of the underlying but wishes to keep all
// other parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, double rate, const vector<double>& carry, char optionType, double strike, double timeTillMat)
{
	for (vector<double>::const_iterator it = carry.begin(); it != carry.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, rate, *it, 1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, rate, *it, -1, strike, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, timeTillMat)));
		}
		//  else 
		//		throw IllegalOptionTypeException(optionType)
	}
}

// Constructs a matrix of Euro option parameters with strike.size() many rows. The i^th row of the resulting matrix paramMat
// will be (spot, vol, rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike[i], timeTillMat). That 
// is, this constructor is used when the user wishes to only vary the strike price of the option but wishes to keep all other 
// parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, double rate, double carry, char optionType, const vector<double>& strike, double timeTillMat)
{
	for (vector<double>::const_iterator it = strike.begin(); it != strike.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, rate, carry, 1, *it, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, *it, timeTillMat)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, rate, carry, -1, *it, timeTillMat };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, *it, timeTillMat)));
		}
		//  else 
		//		throw IllegalOptionTypeException(optionType)
	}
}

// Constructs a matrix of Euro option parameters with timeTillMat.size() many rows. The i^th row of the resulting matrix 
// paramMat will be (spot, vol, rate, carry, +/- 1 (+1 if optionType == 'C', -1 if optionType == 'P'), strike[i], timeTillMat).
// That is, this constructor is used when the user wishes to only vary the expiry length of the option but wishes to keep all
// other parameters fixed.
ParamMatrix::ParamMatrix(double spot, double vol, double rate, double carry, char optionType, double strike, const vector<double>& timeTillMat)
{
	for (vector<double>::const_iterator it = timeTillMat.begin(); it != timeTillMat.end(); ++it)
	{
		if (optionType == 'C')
		{
			vector<double> row{ spot, vol, rate, carry, 1, strike, *it };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, *it)));
		}
		else if (optionType == 'P')
		{
			vector<double> row{ spot, vol, rate, carry, -1, strike, *it };
			paramMat.push_back(row);
			optVect.push_back(OptionPtr(new EuropeanOption(optionType, strike, *it)));
		}
		//  else 
		//		throw IllegalOptionTypeException(optionType)
	}
}

// Copy constructor
ParamMatrix::ParamMatrix(const ParamMatrix& copyParamMat) : paramMat(copyParamMat.paramMat), optVect(copyParamMat.optVect)
{
}

// Destructor
ParamMatrix::~ParamMatrix()
{
}



// ------------------------------------------------------------------------- Accessor Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Returns a vector of prices corresponding to the options whose addresses are stored in the vector optVect. Here we make use
// of the polymorphicity of the function Price() defined within the Option class hierarchy
vector<double> ParamMatrix::Price() const
{
	vector<double> resultVect;
	for (int i = 0; i < optVect.size(); i++)
		resultVect.push_back(optVect[i]->Price(paramMat[i][0], paramMat[i][1], paramMat[i][2], paramMat[i][3]));

	return resultVect;
}

// Returns a vector of deltas corresponding to the options whose addresses are stored in the vector optVect. Here we make use
// of the polymorphicity of the function Delta() defined within the Option class hierarchy
vector<double> ParamMatrix::Delta() const
{
	vector<double> resultVect;
	for (int i = 0; i < optVect.size(); i++)
	{
		resultVect.push_back((optVect[i])->Delta(paramMat[i][0], paramMat[i][1], paramMat[i][2], paramMat[i][3]));
	}

	return resultVect;
}

// Returns a vector of approximated deltas corresponding to the options whose addresses are stored in the vector optVect. Here 
// we make use of the polymorphicity of the function DivDiffDelta() defined within the Option class hierarchy
vector<double> ParamMatrix::DivDiffDelta(double h) const
{
	vector<double> resultVect;
	for (int i = 0; i < optVect.size(); i++)
	{
		resultVect.push_back((optVect[i])->DivDiffDelta(paramMat[i][0], paramMat[i][1], paramMat[i][2], paramMat[i][3], h));
	}

	return resultVect;
}

// Returns a vector of gammas corresponding to the options whose addresses are stored in the vector optVect. Here we make use
// of the polymorphicity of the function Gamma() defined within the Option class hierarchy
vector<double> ParamMatrix::Gamma() const
{
	vector<double> resultVect;
	for (int i = 0; i < optVect.size(); i++)
		resultVect.push_back((optVect[i])->Gamma(paramMat[i][0], paramMat[i][1], paramMat[i][2], paramMat[i][3]));

	return resultVect;
}

// Returns a vector of approximated gammas corresponding to the options whose addresses are stored in the vector optVect. Here 
// we make use of the polymorphicity of the function DivDiffGamma() defined within the Option class hierarchy
vector<double> ParamMatrix::DivDiffGamma(double h) const
{
	vector<double> resultVect;
	for (int i = 0; i < optVect.size(); i++)
	{
		resultVect.push_back((optVect[i])->DivDiffGamma(paramMat[i][0], paramMat[i][1], paramMat[i][2], paramMat[i][3], h));
	}

	return resultVect;
}


// ------------------------------------------------------------------------- Modifier Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Allows the user to add a new row to the parameter matrix; the row can correspond to any derived Option object,
// which at the moment (9.15.20) means the row can correspond to either a Euro option object or a PAMO object
void ParamMatrix::PushRow(vector<double>& newRow)
{
	if (newRow.size() == 6)
	{
		if (newRow[4] == 1)
			optVect.push_back(OptionPtr(new PerpetualAmericanOption('C', newRow[5])));
		else
			optVect.push_back(OptionPtr(new PerpetualAmericanOption('P', newRow[5])));
	}
	
	else if (newRow.size() == 7)
	{
		if (newRow[4] == 1)
			optVect.push_back(OptionPtr(new EuropeanOption('C', newRow[5], newRow[6])));
		else
			optVect.push_back(OptionPtr(new EuropeanOption('P', newRow[5], newRow[6])));
	}
	/*
	else
		//throw IllegalRowException()
	*/

	paramMat.push_back(newRow);
}

// Assignment operator
ParamMatrix& ParamMatrix::operator = (const ParamMatrix& newMat)
{
	if (this != &newMat)
	{
		paramMat = newMat.paramMat;
		optVect = newMat.optVect;
	}

	return *this;
}
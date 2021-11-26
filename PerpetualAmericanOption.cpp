// PerpetualAmericanOption.cpp

#include "PerpetualAmericanOption.hpp"

#include <iostream>
#include <cmath>

// --------------------------------------------------------------------- Constructors and Destructor ------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Default constructor
PerpetualAmericanOption::PerpetualAmericanOption() : Option()
{
}

// Value constructor
PerpetualAmericanOption::PerpetualAmericanOption(char optionType, double strike) : Option(optionType, strike)
{
}

// Copy constructor
PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& PAO) : Option(PAO)
{
}

// Destructor
PerpetualAmericanOption::~PerpetualAmericanOption()
{
}


// ------------------------------------------------------------------------- Accessor Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Returns the price of the PAMO object via the standard optimal early exercise approach 
double PerpetualAmericanOption::Price(double S, double sig, double r, double b) const
{
	if (GetType() == 'C')
	{
		double factor = (GetStrike() / (y_1(sig, r, b) - 1));
		return (factor * pow(((((y_1(sig, r, b) - 1)) / y_1(sig, r, b)) * (S / GetStrike())), y_1(sig, r, b)));
	}
	else
	{
		double factor = (GetStrike() / (1 - y_2(sig, r, b)));
		return (factor * pow(((((y_2(sig, r, b) - 1) * S) / (y_2(sig, r, b) * GetStrike()))), y_2(sig, r, b)));
	}
}


// Returns the delta of the PAMO object; the formula is computed by differentiating the price function once with respect to the 
// parameter S
double PerpetualAmericanOption::Delta(double S, double sig, double r, double b) const
{
	if (GetType() == 'C')
	{
		double factor = (GetStrike() / (y_1(sig, r, b) - 1));
		return ((factor * pow((1 / (y_1(sig, r, b) * factor)), y_1(sig, r, b))) * (y_1(sig, r, b) * pow(S, y_1(sig, r, b) - 1)));
	}
	else
	{
		double factor = (GetStrike() / (1 - y_2(sig, r, b)));
		return ((factor * pow((1 / (y_2(sig, r, b) * (-factor))), y_2(sig, r, b))) * (y_2(sig, r, b) * pow(S, y_2(sig, r, b) - 1)));
	}
}

// Returns the gamma of the PAMO object; the formula is computed by differentiating the price function twice with respect to the 
// parameter S
double PerpetualAmericanOption::Gamma(double S, double sig, double r, double b) const
{
	if (GetType() == 'C')
	{
		double factor = (GetStrike() / (y_1(sig, r, b) - 1));
		return ((GetStrike() * pow((1 / (y_1(sig, r, b) * factor)), y_1(sig, r, b))) * (y_1(sig, r, b) * pow(S, y_1(sig, r, b) - 2)));
	}
	else
	{
		double factor = (GetStrike() / (1 - y_2(sig, r, b)));
		return -((GetStrike() * pow((1 / (y_2(sig, r, b) * (-factor))), y_2(sig, r, b))) * (y_2(sig, r, b) * pow(S, y_2(sig, r, b) - 2)));
	}
}

// Returns an approximation of the delta of the PAMO through the method of centered divided differences for 1st derivatives
double PerpetualAmericanOption::DivDiffDelta(double S, double sig, double r, double b, double h) const
{
	double numerator = (Price((S + h), sig, r, b) - Price((S - h), sig, r, b));
	return (numerator / (2 * h));
}

// Returns the absolute value of the difference between the values returned by delta and divDiffDelta with respect to 
// a given value of h. 
double PerpetualAmericanOption::DivDiffDeltaAccuracy(double S, double sig, double r, double b, double h) const
{
	return abs(Delta(S, sig, r, b) - DivDiffDelta(S, sig, r, b, h));
}

// Returns an approximation of the gamma of the PAMO through the method of centered divided differences for 1st derivatives
double PerpetualAmericanOption::DivDiffGamma(double S, double sig, double r, double b, double h) const
{
	double numerator = ((Price((S + h), sig, r, b) - (2 * Price(S, sig, r, b))) + Price((S - h), sig, r, b));
	return (numerator / pow(h, 2));
}

// Returns the absolute value of the difference between the values returned by gamma and divDiffGamma with respect to 
// a given value of h.
double PerpetualAmericanOption::DivDiffGammaAccuracy(double S, double sig, double r, double b, double h) const
{
	return abs(Gamma(S, sig, r, b) - DivDiffGamma(S, sig, r, b, h));
}


// ------------------------------------------------------------------------- Modifier Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Assignment operator
PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& PAO)
{
	if (this != &PAO)
		Option::operator = (PAO);

	return *this;
}


// -------------------------------------------------------------------------- Static Functions ------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Called by various non-static member functions defined above; used to decongest the code in the body of those functions.
// Only used when the underlying PAMO object is a call.
double PerpetualAmericanOption::y_1(double sig, double r, double b)
{
	return ((0.5 - b / pow(sig, 2)) + sqrt(pow((b / pow(sig, 2) - 0.5), 2) + (2 * r) / pow(sig, 2)));
}

// Called by various non-static member functions defined above; used to decongest the code in the body of those functions.
// Only used when the underlying PAMO object is a put.
double PerpetualAmericanOption::y_2(double sig, double r, double b)
{
	return ((0.5 - b / pow(sig, 2)) - sqrt(pow((((b / pow(sig, 2) - 0.5))), 2) + (2 * r) / pow(sig, 2)));
}







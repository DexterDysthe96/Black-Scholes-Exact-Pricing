// Option.cpp

#include "Option.hpp"

// --------------------------------------------------------------------- Constructors and Destructor ------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Default constructor
Option::Option() : type(1), K(0)
{
}

// Value constructor
Option::Option(char optionType, double strike) : K(strike)
{
	if (optionType == 'C' || optionType == 'P')
		type = optionType;
//  else 
//		throw IllegalOptionTypeException(optionType)
}

// Copy constructor
Option::Option(const Option& op) : type(op.type), K(op.K)
{
}

// Destructor
Option::~Option()
{
}

// ------------------------------------------------------------------------- Accessor Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Returns the value of the private data member type
char Option::GetType() const
{
	return type;
}

// Returns the value of the private data member K
double Option::GetStrike() const
{
	return K;
}

// ------------------------------------------------------------------------- Modifier Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Allows the user to alter the option's type
void Option::SetType(char optionType)
{
	type = optionType;
}

// Allows the user to alter the option's strike price
void Option::SetStrike(double strike)
{
	K = strike;
}

// Assignment operator
Option& Option::operator = (const Option& op)
{
	if (this != &op)
	{
		type = op.type;
		K = op.K;
	}

	return *this;
}
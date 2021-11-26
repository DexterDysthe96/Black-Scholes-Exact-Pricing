// Option.hpp
//
// The purpose of the Option class is to serve as a unifying abstract base class for our EuropeanOption and PerpetualAmericanOption derived
// classes. There are two private members, one of character type that stores 'C' for call options and 'P' for put options, and the other a 
// double which stores the strike price of the option. 

#ifndef Option_H
#define Option_H

class Option
{
private:
	char type;									// 'C' for calls and 'P' for puts
	double K;									// Strike price


public:
	// Constructors and Destructor
	Option();									// Default constructor
	Option(char optionType, double strike);		// Value constructor
	Option(const Option& op);					// Copy constructor	
	virtual ~Option();							// Destructor


	// Accessor Functions
	char GetType() const;																			// Getter for the private member type
	double GetStrike() const;																		// Getter for the private member K
	virtual double Price(double S, double sig, double r, double b) const = 0;						// PVMF
	virtual double Delta(double S, double sig, double r, double b) const = 0;						// PVMF 
	virtual double DivDiffDelta(double S, double sig, double r, double b, double h) const = 0;		// PVMF 
	virtual double Gamma(double S, double sig, double r, double b) const = 0;						// PVMF 
	virtual double DivDiffGamma(double S, double sig, double r, double b, double h) const = 0;		// PVMF 


	// Modifier Functions
	void SetType(char optionType);																	// Setter for the private member type
	void SetStrike(double strike);																	// Setter for the private member K
	Option& operator = (const Option& op);															// Assignment operator

};


#endif

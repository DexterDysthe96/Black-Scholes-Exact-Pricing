// PerpetualAmericanOption.hpp
//
// The purpose of the PerpetualAmericanOption class is to extend the functionality of the base class Option to Option objects that are of
// American type and have no expiry date, i.e. the option holder may exercise the option at any time and this right never expires. As such,
// the PerpetualAmericanOption class is a derived class of Option. Indeed perpetual American options (PAMOs) do possess an exact pricing formula  
// unlike their non-perpetual life American counterparts, and this formula is implemented in the member function price given below. A 
// detailed derivation of the pricing equation for Perpetual American puts can be found in section 8.3 of Shreve's StoCal for Finance II.

#ifndef PerpetualAmericanOption_H
#define PerpetualAmericanOption_H

#include "Option.hpp"

class PerpetualAmericanOption : public Option
{
public:
	// Constructors and Destructor
	PerpetualAmericanOption();												// Default constructor
	PerpetualAmericanOption(char optionType, double strike);				// Value constructor									
	PerpetualAmericanOption(const PerpetualAmericanOption& PAO);			// Copy constructor
	virtual ~PerpetualAmericanOption();										// Destructor
	

	// Accessor Functions
	// Common Parameters -- S := current spot price | sig := volatility of spot price \\
	//						r := interest rate		| b := cost-of-carry			  \\
	
	double Price(double S, double sig, double r, double b) const;								// Returns the price of the PAMO according to optimal early exercise

	double Delta(double S, double sig, double r, double b) const;								// Returns the delta of the PAMO

	double Gamma(double S, double sig, double r, double b) const;								// Returns the gamma of the PAMO

	double DivDiffDelta(double S, double sig, double r, double b, double h) const;				// Approximates the E PAMO's delta via the centered divided differences method for 1st
																								// derivatives; h specifies the radius of the interval about S we apply the approx. on

	double DivDiffDeltaAccuracy(double S, double sig, double r, double b, double h) const;		// Returns the absolute value of the difference between the returned value of delta and
																								// divDiffDelta for a given value of h used for the approximation in divDiffDelta

	double DivDiffGamma(double S, double sig, double r, double b, double h) const;				// Approximates the PAMO's gamma via the centered divided differences method for 2nd
																								// derivatives; h specifies the radius of the interval about S we apply the approx. on

	double DivDiffGammaAccuracy(double S, double sig, double r, double b, double h) const;		// Returns the absolute value of the difference between the returned value of gamma and
																								// divDiffGamma for a given value of h used for the approximation in divDiffGamma

	// Modifier Functions
	PerpetualAmericanOption& operator = (const PerpetualAmericanOption& PAO);					// Assignment operator


	// Static Functions
	static double y_1(double sig, double r, double b);											// The returned valued is used in the pricing and Greeks formulas for Perpetual American
																								// call options; this function acts a helper function for various non-static member
																								// functions when the underlying PAMO object is a call

	static double y_2(double sig, double r, double b);											// The returned valued is used in the pricing and Greeks formulas for Perpetual American
																								// put options; this function acts a helper function for various non-static member
																								// functions when the underlying PAMO object is a put

};


#endif

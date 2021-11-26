// EuropeanOption.hpp
//
// The purpose of the EuropeanOption class is to extend the functionality of the base class Option to Option objects that are of
// European type, i.e. having an expiry date which constitues the sole day the option holder can exercise. As such, the EuropeanOption
// class is a derived class of Option, and we have an additional private data member to store the contract length (in years) of the 
// European option object. The member functions are described at length below. Additionally there are 3 static member functions whose
// primary purpose is to assist other non-static member functions.

#ifndef EuropeanOption_H
#define EuropeanOption_H

#include "Option.hpp"

class EuropeanOption : public Option
{
private:
	double T;																	// Time till maturity

public:
	// Constructors and Destructor
	EuropeanOption();															// Default constructor
	EuropeanOption(char optionType, double strike, double timeTillMat);			// Value constructor
	EuropeanOption(const EuropeanOption& EO);									// Copy constructor
	virtual ~EuropeanOption();													// Destructor


	// Accessor Functions
	// Common Parameters -- S := current spot price | sig := volatility of spot price \\
	//						r := interest rate		| b := cost-of-carry			  \\
	
	double GetTTM() const;																		// Getter for the private member T

	double d_1(double S, double sig, double b) const;											// Both d_1 and d_2 are used in the price() member function as well as all of the Greek
	double d_2(double S, double sig, double b) const;											// member functions declared below. We created these in order to streamline their usage
																								// They are non-static member functions because their values depend on the private members
																								// T and K
								
							   // Pricing Functions \\		

	double Price(double S, double sig, double r, double b) const;								// Returns the Black-Scholes-Merton price of the Euro option
	
	double ParityPrice(double optionPrice, double S, double r, double b) const;					// Returns the price of the Euro option object according to the Put-Call parity formula;
																								// optionPrice := price of an option of opposite type with identical strike and time till
																								// maturity
								// Greeks Functions \\

	double Delta(double S, double sig, double r, double b) const;								// Returns the Black-Scholes-Merton delta of the Euro option
	
	double Gamma(double S, double sig, double r, double b) const;								// Returns the Black-Scholes-Merton gamma of the Euro option

	double Theta(double S, double sig, double r, double b) const;								// Returns the Black-Scholes-Merton theta of the Euro option

	double Vega(double S, double sig, double r, double b) const;								// Returns the Black-Scholes-Merton vega of the Euro option

	double DivDiffDelta(double S, double sig, double r, double b, double h) const;				// Approximates the Euro option's delta via the centered divided differences method for
																								// 1st derivatives; h specifies the radius of the interval about S we apply the approx. on

	double DivDiffDeltaAccuracy(double S, double sig, double r, double b, double h) const;		// Returns the absolute value of the difference between the returned value of delta and
																								// divDiffDelta for a given value of h used for the approximation in divDiffDelta
	
	double DivDiffGamma(double S, double sig, double r, double b, double h) const;				// Approximates the Euro option's delta via the centered divided differences method for
																								// 2nd derivatives; h specifies the radius of the interval about S we apply the approx. 

	double DivDiffGammaAccuracy(double S, double sig, double r, double b, double h) const;		// Returns the absolute value of the difference between the returned value of gamma and
																								// divDiffGamma for a given value of h used for the approximation in divDiffGamma

	
	// Modifier Functions
	void SetTTM(double timeTillMat);															// Setter for the private member T
	EuropeanOption& operator = (const EuropeanOption& euroOp);									// Assignment operator


	// Static Functions
	static double N(double x);																	// Returns the CDF at x for a standard normal RV; used in many member functions above
	static double n(double x);																	// Returns the PDF at x for a standard normal RV; used in many member functions above
	static bool CheckParity(double callPrice, double putPrice, double K, double T, double S,
							double r, double b, double tolerance);								// This returns 1 if the call and put price inputs satisfy parity *up to an additive
																								// constant not exceeding the value of the input variable tolerance* and returns 0
																								// otherwise

};																										


#endif

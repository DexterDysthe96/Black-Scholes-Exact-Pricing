// EuropeanOption.cpp

#include "EuropeanOption.hpp"

#include <boost/math/distributions/normal.hpp>
using namespace boost::math;

#include <cmath>


// --------------------------------------------------------------------- Constructors and Destructor ------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Default constructor
EuropeanOption::EuropeanOption() : Option(), T(0)
{
}

// Value constructor
EuropeanOption::EuropeanOption(char optionType, double strike, double timeTillMat) : Option(optionType, strike), T(timeTillMat)
{
}

// Copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& EO) : Option(EO), T(EO.T)
{
}

// Destructor
EuropeanOption::~EuropeanOption()
{
}


// ------------------------------------------------------------------------- Accessor Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Returns the value of the private data member T
double EuropeanOption::GetTTM() const
{
	return T;
}

// Returns a value that is fundamental to computation of the Euro option object's price and Greeks 
double EuropeanOption::d_1(double S, double sig, double b) const
{
	return ((log(S / GetStrike()) + ((b + (pow(sig, 2) / 2)) * T)) / (sig * sqrt(T)));
}

// Like the above, returns a value that is fundamental to computation of the Euro option object's price and Greeks
double EuropeanOption::d_2(double S, double sig, double b) const
{
	return (d_1(S, sig, b) - (sig * sqrt(T)));
}


// Returns the Black-Scholes-Merton price of the Euro option object
double EuropeanOption::Price(double S, double sig, double r, double b) const
{
	if (GetType() == 'C')
		return ((S * exp((b - r) * T) * N((d_1(S, sig, b)))) - (GetStrike() * exp((-r) * T) * N((d_2(S, sig, b)))));
	else
		return ((GetStrike() * exp((-r) * T) * N((-d_2(S, sig, b)))) - (S * exp((b - r) * T) * N((-d_1(S, sig, b)))));
}

// This returns the value of the Euro option object according to put-call parity. As such, optionPrice denotes the price 
// of an option with identical strike and time till maturity but with opposite type i.e. if the current object is a call,
// optionPrice should be the price of a put. S, r, and b are as usual; that is, S := spot price, r := interest rate, 
// b := cost-of-carry
double EuropeanOption::ParityPrice(double optionPrice, double S, double r, double b) const
{
	if (GetType() == 'C')
		return (optionPrice + ((S * exp((b - r) * T)) - GetStrike() * exp(-r * T)));
	else
		return (optionPrice - ((S * exp((b - r) * T)) - GetStrike() * exp((-r) * T)));
}


// Returns the Black-Scholes-Merton delta of the Euro option object; delta is the first derivative of the Euro option's
// price function with respect to the parameter S
double EuropeanOption::Delta(double S, double sig, double r, double b) const
{
	if (GetType() == 'C')
		return (exp((b - r) * T) * N(d_1(S, sig, b)));
	else
		return (exp((b - r) * T) * (N(d_1(S, sig, b)) - 1));
}

// Returns the Black-Scholes-Merton gamma of the Euro option object; gamma is the second derivative of the Euro option's
// price function with respect to the parameter S
double EuropeanOption::Gamma(double S, double sig, double r, double b) const
{
	// Euro calls and puts with identical strike price and time till maturity have identical gammas 
	return (n(d_1(S, sig, b)) * exp((b - r) * T)) / (S * (sig * sqrt(T)));
}

// Returns the Black-Scholes-Merton theta of the Euro option object; theta is the first derivative of the Euro option's
// price function with respect to time
double EuropeanOption::Theta(double S, double sig, double r, double b) const
{
	if (GetType() == 'C')
	{
		double firstTerm  = -((S * (sig * (exp((b - r) * T) * n(d_1(S, sig, b))))) / (2 * sqrt(T)));
		double secondTerm = -((b - r) * (S * (exp((b - r) * T) * N(d_1(S, sig, b)))));
		double thirdTerm  = -(r * (GetStrike() * (exp(-r * T) * N(d_2(S, sig, b)))));

		return firstTerm + secondTerm + thirdTerm;
	}
	else
	{
		double firstTerm  = -((S * (sig * (exp((b - r) * T) * n(d_1(S, sig, b))))) / (2 * sqrt(T)));
		double secondTerm = ((b - r) * (S * (exp((b - r) * T) * N(d_1(S, sig, b)))));
		double thirdTerm  = (r * (GetStrike() * (exp(-r * T) * N(-d_2(S, sig, b)))));

		return firstTerm + secondTerm + thirdTerm;
	}
}

// Returns the Black-Scholes-Merton vega of the Euro option object; vega is the first derivative of the Euro option's
// price function with respect to the parameter sig
double EuropeanOption::Vega(double S, double sig, double r, double b) const
{
	return (S * (sqrt(T) * (exp((b - r) * T) * n(d_1(S, sig, b)))));
}

// Returns an approximation of the delta of the Euro option through the method of centered divided differences for 1st 
// derivatives
double EuropeanOption::DivDiffDelta(double S, double sig, double r, double b, double h) const
{
	double numerator = Price((S + h), sig, r, b) - Price((S - h), sig, r, b);
	return (numerator / (2 * h));
}

// Returns the absolute value of the difference between the values returned by delta and divDiffDelta with respect to 
// a given value of h. 
double EuropeanOption::DivDiffDeltaAccuracy(double S, double sig, double r, double b, double h) const
{
	return abs(Delta(S, sig, r, b) - DivDiffDelta(S, sig, r, b, h));
}

// Returns an approximation of the delta of the Euro option through the method of centered divided differences for 2nd 
// derivatives
double EuropeanOption::DivDiffGamma(double S, double sig, double r, double b, double h) const
{
	double numerator = ((Price((S + h), sig, r, b) - (2 * Price(S, sig, r, b))) + Price((S - h), sig, r, b));
	return (numerator / pow(h, 2));
}

// Returns the absolute value of the difference between the values returned by gamma and divDiffGamma with respect to 
// a given value of h.
double EuropeanOption::DivDiffGammaAccuracy(double S, double sig, double r, double b, double h) const
{
	return abs(Gamma(S, sig, r, b) - DivDiffGamma(S, sig, r, b, h));
}

// ------------------------------------------------------------------------- Modifier Functions -----------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Allows the user to alter the Euro option's time till maturity
void EuropeanOption::SetTTM(double timeTillMat)
{
	T = timeTillMat;
}

// Assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& euroOp)
{
	if (this != &euroOp)
	{
		Option::operator = (euroOp);
		T = euroOp.T;
	}

	return *this;
}


// -------------------------------------------------------------------------- Static Functions ------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// More compact way of calling the standard normal CDF at a value x
double EuropeanOption::N(double x)
{
	normal_distribution<> myNormal;
	return cdf(myNormal, x);
}

// More compact way of calling the standard normal PDF at a value x
double EuropeanOption::n(double x)
{
	normal_distribution<> myNormal;
	return pdf(myNormal, x);
}

// This function's purpose is to check if two Euro option prices, one corresponding to a call and the other a put with identical
// strike price and time till maturity, satisfy put-call parity *up to a given additive constant which is stored by the input
// variable tolerance*. In theory, when parity does not hold an arbitrage opportunity is present with respect to the 
// underlying stock, a forward on that stock with strike the same as the two options, and the call and put option who's prices
// served as input to the function.
bool EuropeanOption::CheckParity(double callPrice, double putPrice, double K, double T, double S, double r, double b, double tolerance)
{
	bool condition = abs((callPrice - putPrice) - ((S * exp((b - r) * T)) - K * exp(-r * T))) < tolerance;
	return condition;
}
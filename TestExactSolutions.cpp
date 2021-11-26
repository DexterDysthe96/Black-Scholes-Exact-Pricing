// TestExactSolutions.cpp
// Dexter Dysthe
//
// The purpose of this program is to test the newly created Option class hierarchy along with the ParamMatrix class in their totality.
// We break up the code in main() in below according to the 3 sections outlined in the Level 9 Exercises pdf. 

#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include "ParamMatrix.hpp"
#include "ExactPricingMethodsGlobalFunctions.hpp"

#include <iostream>

using namespace std;

int main()
{	
	EuropeanOption Put('P', 120, 1.45);
	cout << Put.Price(108, 0.51, 0.045, 0) << endl;
	cout << Put.Delta(108, 0.51, 0.045, 0) << endl;
	cout << Put.Gamma(108, 0.51, 0.045, 0) << endl;

	// EuropeanOption Call('C', strike, expiry);
	// EuropeanOption Put('P', strike, expiry);
	// Call.Price/Delta/DivDiffDelta/Gamma/DivDiffGamma(spot, sig, r, b, h(for approx functions));
	// Put.Price/Delta/DivDiffDelta/Gamma/DivDiffGamma(spot, sig, r, b, h(for approx functions));
	// 
	// Call.ParityPrice(putOptionPrice, spot, r, b);
	// Put.ParityPrice(callOptionPrice, spot, r, b);
	// EuropeanOption::CheckParity(callPrice, putPrice, K, expiry, spot, r, b, tolerance);


	// PerpetualAmericanOption AmCall('C', strike);
	// PerpetualAmericanOption AmPut('P', strike);
	// AmCall.Price/Delta/DivDiffDelta/Gamma/DivDiffGamma(spot, sig, r, b, h(for approx functions));
	// AmPut.Price/Delta/DivDiffDelta/Gamma/DivDiffGamma(spot, sig, r, b, h(for approx functions));


	// Order for matrix initialization: Spot, Vol, Rate, Carry, Type, Strike, Maturity
	//
	// ParamMatrix EPM1(mesher(5, 35, 5), 0.5, 0.12, 0.12, 'C', 10, 1);
	// ParamMatrix EPM2(5, mesher(0.2, 0.55, 0.05), 0.12, 0.12, 'C', 10, 1);
	// ParamMatrix EPM3(5, 0.5, 0.12, 0.12, 'C', mesher(7, 12, 1), 1);
	// ParamMatrix EPM4(5, 0.5, 0.12, 0.12, 'C', 10, mesher(0.25, 1.75, 0.25));
	//
	// ParamMatrix EPM5;
	// vector<double> batchOnePut{ 60, 0.30, 0.08, 0.08, -1, 65, 0.25 };
	// vector<double> batchTwoPut{ 100, 0.2, 0, 0, -1, 100, 1 };
	// vector<double> batchThreePut{ 5, 0.50, 0.12, 0.12, -1, 10, 1 };
	// vector<double> batchFourPut{ 100, 0.30, 0.08, 0.08, -1, 100, 30 };
	// EPM5.PushRow(batchOnePut);
	// EPM5.PushRow(batchTwoPut);
	// EPM5.PushRow(batchThreePut);
	// EPM5.PushRow(batchFourPut);
	//
	// EPM1.Price()/Delta()/DivDiffDelta(tolerance) 







	/*

	// ----------------------------------------------------------------------------- Part 1 ------------------------------------------------------------------------------------- \\
	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \\

	cout << "------------------------------------- Exact Solutions of One-Factor Plain Options -------------------------------------" << endl;
	cout << "" << endl;

	cout << "	     Batch 1" << endl;
	cout << "-------------------------------------" << endl;
	EuropeanOption batch1Call('C', 65, 0.25);
	EuropeanOption batch1Put('P', 65, 0.25);
	double callPrice = batch1Call.Price(60, 0.30, 0.08, 0.08);
	double putPrice = batch1Put.Price(60, 0.30, 0.08, 0.08);
	cout << "Call" << endl;
	cout << "Price: " << callPrice << endl;
	cout << "Price using parity: " << batch1Call.ParityPrice(putPrice, 60, 0.08, 0.08) << endl;
	cout << "" << endl;
	cout << "Put" << endl;
	cout << "Price: " << putPrice << endl;
	cout << "Price using parity: " << batch1Put.ParityPrice(callPrice, 60, 0.08, 0.08) << endl;
	cout << "" << endl;
	cout << "Parity holds (1->Yes, 0->No): " << EuropeanOption::CheckParity(callPrice, putPrice, 65, 0.25, 60, 0.08, 0.08, 0.0001) << endl;
	cout << "" << endl;

	
	cout << "" << endl;
	cout << "	     Batch 2" << endl;
	cout << "-------------------------------------" << endl;
	EuropeanOption batch2Call('C', 100, 1);
	EuropeanOption batch2Put('P', 100, 1);
	callPrice = batch2Call.Price(100, 0.2, 0, 0);
	putPrice = batch2Put.Price(100, 0.2, 0, 0);
	cout << "Call" << endl;
	cout << "Price: " << callPrice << endl;
	cout << "Price using parity: " << batch2Call.ParityPrice(putPrice, 100, 0, 0) << endl;
	cout << "" << endl;
	cout << "Put" << endl;
	cout << "Price: " << putPrice << endl;
	cout << "Price using parity: " << batch2Put.ParityPrice(callPrice, 100, 0, 0) << endl;
	cout << "" << endl;
	cout << "Parity holds (1->Yes, 0->No): " << EuropeanOption::CheckParity(callPrice, putPrice, 100, 1, 100, 0, 0, 0.0001) << endl;
	cout << "" << endl;


	cout << "" << endl;
	cout << "	     Batch 3" << endl;
	cout << "-------------------------------------" << endl;
	EuropeanOption batch3Call('C', 10, 1);
	EuropeanOption batch3Put('P', 10, 1);
	callPrice = batch3Call.Price(5, 0.5, 0.12, 0.12);
	putPrice = batch3Put.Price(5, 0.5, 0.12, 0.12);
	cout << "Call" << endl;
	cout << "Price: " << callPrice  << endl;
	cout << "Price using parity: " << batch3Call.ParityPrice(putPrice, 5, 0.12, 0.12) << endl;
	cout << "" << endl;
	cout << "Put" << endl;
	cout << "Price: " << putPrice << endl;
	cout << "Price using parity: " << batch3Put.ParityPrice(callPrice, 5, 0.12, 0.12) << endl;
	cout << "" << endl;
	cout << "Parity holds (1->Yes, 0->No): " << EuropeanOption::CheckParity(callPrice, putPrice, 10, 1, 5, 0.12, 0.12, 0.0001) << endl;
	cout << "" << endl;


	cout << "" << endl;
	cout << "	     Batch 4" << endl;
	cout << "-------------------------------------" << endl;
	EuropeanOption batch4Call('C', 100, 30);
	EuropeanOption batch4Put('P', 100, 30);
	callPrice = batch4Call.Price(100, 0.30, 0.08, 0.08);
	putPrice = batch4Put.Price(100, 0.30, 0.08, 0.08);
	cout << "Call" << endl;
	cout << "Price: " << callPrice << endl;
	cout << "Price using parity: " << batch4Call.ParityPrice(putPrice, 100, 0.08, 0.08) << endl;
	cout << "" << endl;
	cout << "Put" << endl;
	cout << "Price: " << putPrice << endl;
	cout << "Price using parity: " << batch4Put.ParityPrice(callPrice, 100, 0.08, 0.08) << endl;
	cout << "" << endl;
	cout << "Parity holds (1->Yes, 0->No): " << EuropeanOption::CheckParity(callPrice, putPrice, 100, 30, 100, 0.08, 0.08, 0.0001) << endl;
	cout << "" << endl;

	
	cout << "" << endl;
	cout << "	  Matrix Pricing" << endl;
	cout << "-------------------------------------" << endl;
	ParamMatrix EPM1(mesher(5, 35, 5), 0.5, 0.12, 0.12, 'C', 10, 1);
	ParamMatrix EPM2(5, mesher(0.2, 0.55, 0.05), 0.12, 0.12, 'C', 10, 1);
	ParamMatrix EPM3(5, 0.5, 0.12, 0.12, 'C', mesher(7, 12, 1), 1);
	ParamMatrix EPM4(5, 0.5, 0.12, 0.12, 'C', 10, mesher(0.25, 1.75, 0.25));
	
	ParamMatrix EPM5;
	vector<double> batchOnePut{ 60, 0.30, 0.08, 0.08, -1, 65, 0.25 };
	vector<double> batchTwoPut{ 100, 0.2, 0, 0, -1, 100, 1 };
	vector<double> batchThreePut{ 5, 0.50, 0.12, 0.12, -1, 10, 1 };
	vector<double> batchFourPut{ 100, 0.30, 0.08, 0.08, -1, 100, 30 };
	EPM5.PushRow(batchOnePut);
	EPM5.PushRow(batchTwoPut);
	EPM5.PushRow(batchThreePut);
	EPM5.PushRow(batchFourPut);

	cout << "Call (Using Batch 3 for Fixed Parameters)" << endl;
	cout << "Price vector (Spot Varying): " << EPM1.Price();
	cout << "Price vector (Vol Varying): " << EPM2.Price();
	cout << "Price vector (Strike Varying): " << EPM3.Price();
	cout << "Price vector (TTM Varying): " << EPM4.Price() << endl;

	cout << "" << endl;
	cout << "Put (Testing Batches 1-4)" << endl;
	cout << "Price vector: " << EPM5.Price() << endl;
	cout << "" << endl;

	// ----------------------------------------------------------------------------- Part 2 ------------------------------------------------------------------------------------- \\
	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \\

	cout << "" << endl;
	cout << "-------------------------------------- Option Sensitivities, aka the Greeks --------------------------------------------" << endl;
	cout << "" << endl;

	EuropeanOption opt1('C', 100, 0.5);
	EuropeanOption opt2('P', 100, 0.5);

	cout << "Call" << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "Delta: " << opt1.Delta(105, 0.36, 0.1, 0) << endl;
	cout << "Approximate Delta (h = 5, 0.5, 0.01, 0.0000001): " << opt1.DivDiffDelta(105, 0.36, 0.1, 0, 5) << ", " << opt1.DivDiffDelta(105, 0.36, 0.1, 0, 0.5)
		 << ", " << opt1.DivDiffDelta(105, 0.36, 0.1, 0, 0.01) << ", " << opt1.DivDiffDelta(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "Error		  (h = 5, 0.5, 0.01, 0.0000001): " << opt1.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 5) << ", " << opt1.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 0.5) 
		 << ", " << opt1.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 0.01) << ", " << opt1.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "" << endl;
	
	cout << "Gamma: " << opt1.Gamma(105, 0.36, 0.1, 0) << endl;
	cout << "Approximate Gamma (h = 5, 0.5, 0.01, 0.0000001): " << opt1.DivDiffGamma(105, 0.36, 0.1, 0, 5) << ", " << opt1.DivDiffGamma(105, 0.36, 0.1, 0, 0.5)
		 << ", " << opt1.DivDiffGamma(105, 0.36, 0.1, 0, 0.01) << ", " << opt1.DivDiffGamma(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "Error		  (h = 5, 0.5, 0.01, 0.0000001): " << opt1.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 5) << ", " << opt1.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 0.5)
		 << ", " << opt1.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 0.01) << ", " << opt1.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "" << endl;

	cout << "" << endl;
	cout << "Put" << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	cout << "Delta: " << opt2.Delta(105, 0.36, 0.1, 0) << endl;
	cout << "Approximate Delta (h = 5, 0.5, 0.01, 0.0000001): " << opt2.DivDiffDelta(105, 0.36, 0.1, 0, 5) << ", " << opt2.DivDiffDelta(105, 0.36, 0.1, 0, 0.5)
		<< ", " << opt2.DivDiffDelta(105, 0.36, 0.1, 0, 0.01) << ", " << opt2.DivDiffDelta(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "Error		  (h = 5, 0.5, 0.01, 0.0000001): " << opt2.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 5) << ", " << opt2.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 0.5)
		<< ", " << opt2.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 0.01) << ", " << opt2.DivDiffDeltaAccuracy(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "" << endl;

	cout << "Gamma: " << opt2.Gamma(105, 0.36, 0.1, 0) << endl;
	cout << "Approximate Gamma (h = 5, 0.5, 0.01, 0.0000001): " << opt2.DivDiffGamma(105, 0.36, 0.1, 0, 5) << ", " << opt2.DivDiffGamma(105, 0.36, 0.1, 0, 0.5)
		<< ", " << opt2.DivDiffGamma(105, 0.36, 0.1, 0, 0.01) << ", " << opt2.DivDiffGamma(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "Error		  (h = 5, 0.5, 0.01, 0.0000001): " << opt2.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 5) << ", " << opt2.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 0.5)
		<< ", " << opt2.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 0.01) << ", " << opt2.DivDiffGammaAccuracy(105, 0.36, 0.1, 0, 0.0000001) << endl;
	cout << "" << endl;

	cout << "" << endl;
	cout << "					Matrix Greeks" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	cout << "" << endl;
	cout << "Call (Using Batch 3 for Fixed Parameters)" << endl;
	cout << "------------------------------------------" << endl;
	cout << "Delta vector (Spot Varying): " << EPM1.Delta();
	cout << "Approx Delta vector (h = 0.8): " << EPM1.DivDiffDelta(0.8);
	cout << "Approx Delta vector (h = 0.001): " << EPM1.DivDiffDelta(0.001) << endl;
	cout << "Gamma vector (Spot Varying): " << EPM1.Gamma();
	cout << "Approx Gamma vector (h = 0.8): " << EPM1.DivDiffGamma(0.8);
	cout << "Approx Gamma vector (h = 0.001): " << EPM1.DivDiffGamma(0.001) << endl;
	cout << "" << endl;

	cout << "Delta vector (Vol Varying): " << EPM2.Delta();
	cout << "Approx Delta vector (h = 0.8): " << EPM2.DivDiffDelta(0.8);
	cout << "Approx Delta vector (h = 0.001): " << EPM2.DivDiffDelta(0.001) << endl;
	cout << "Gamma vector (Vol Varying): " << EPM2.Gamma();
	cout << "Approx Gamma vector (h = 0.8): " << EPM2.DivDiffGamma(0.8);
	cout << "Approx Gamma vector (h = 0.001): " << EPM2.DivDiffGamma(0.001) << endl;
	cout << "" << endl;

	cout << "Delta vector (Strike Varying): " << EPM3.Delta();
	cout << "Approx Delta vector (h = 0.8): " << EPM3.DivDiffDelta(0.8);
	cout << "Approx Delta vector (h = 0.001): " << EPM3.DivDiffDelta(0.001) << endl;
	cout << "Gamma vector (Strike Varying): " << EPM3.Gamma();
	cout << "Approx Gamma vector (h = 0.8): " << EPM3.DivDiffGamma(0.8);
	cout << "Approx Gamma vector (h = 0.001): " << EPM3.DivDiffGamma(0.001) << endl;
	cout << "" << endl;

	cout << "Delta vector (TTM Varying): " << EPM4.Delta();
	cout << "Approx Delta vector (h = 0.8): " << EPM4.DivDiffDelta(0.8);
	cout << "Approx Delta vector (h = 0.001): " << EPM4.DivDiffDelta(0.001) << endl;
	cout << "Gamma vector (TTM Varying): " << EPM4.Gamma();
	cout << "Approx Gamma vector (h = 0.8): " << EPM4.DivDiffGamma(0.8);
	cout << "Approx Gamma vector (h = 0.001): " << EPM4.DivDiffGamma(0.001) << endl;

	cout << "" << endl;
	cout << "Put (Testing Batches 1-4)" << endl;
	cout << "------------------------------------------" << endl;
	cout << "Delta vector: " << EPM5.Delta();
	cout << "Gamma vector: " << EPM5.Gamma();
	cout << "" << endl;


	// ----------------------------------------------------------------------------- Part 3 ------------------------------------------------------------------------------------- \\
	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \\

	cout << "" << endl;
	cout << "--------------------------------------------- Perpetual American Options ----------------------------------------------" << endl;
	cout << "" << endl;

	PerpetualAmericanOption Call('C', 100);
	PerpetualAmericanOption Put('P', 100);
	cout << "Call" << endl;
	cout << "Price: " << Call.Price(110, 0.1, 0.1, 0.02) << endl;
	cout << "" << endl;
	cout << "Put" << endl;
	cout << "Price: " << Put.Price(110, 0.1, 0.1, 0.02) << endl;
	cout << "" << endl;


	cout << "" << endl;
	cout << "	      Matrix Pricing" << endl;
	cout << "----------------------------------------------" << endl;
	ParamMatrix PAPM1(mesher(90, 120, 5), 0.1, 0.1, 0.02, 'P', 100);
	ParamMatrix PAPM2(110, mesher(0.075, 0.25, 0.025), 0.1, 0.02, 'P', 100);
	ParamMatrix PAPM3(110, 0.1, 0.1, 0.02, 'P', mesher(80, 130, 10));
	cout << "Put (Using Given Data for Fixed Parameters)" << endl;
	cout << "Price vector (Spot Varying): " << PAPM1.Price();
	cout << "Price vector (Vol Varying): " << PAPM2.Price();
	cout << "Price vector (Strike Varying): " << PAPM3.Price() << endl;

	*/

	return 0;
}
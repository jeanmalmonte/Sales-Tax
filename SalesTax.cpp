#include "SalesTax.h"
#pragma once

SalesTax::SalesTax()
{}

SalesTax::~SalesTax() {}

bool SalesTax::readfile(string filename)
{
	taxData.open(filename);
	
	//Test the File if it opens
	if (!taxData) {
		cout << "Can't open the input file.\n";
		cout << "Please make sure you have the file \"taxData.txt\" on the Sales Tax folder.\n";
		cout << "If no file is available, please make a text file called taxData.txt and add it to the Sales Tax Folder.\n";
		return false;
	}

	//read initial value
	taxData >> sumData;
	
	//Read the values from filename and calculate total sum
	while (taxData) {
		totalSum = sumData + totalSum;
		taxData >> sumData;
	}

	//File read succesfully
	return true;
}

double SalesTax::getTotalSum()
{
	return totalSum;
}

double SalesTax::calculateMadisonGR()
{
	return getTotalSum() * madisonGeneralRate;
}

double SalesTax::calculateHSVGS()
{
	return getTotalSum() * (cityHSVGSalesRate * double(100.00));
}

bool SalesTax::hsvDiscount()
{
	//Calculate Huntsville Gross
	HuntsvilleGrossAmount = calculateHSVGS();
	
	/*City of Huntsville Discount calculation */
	if (HuntsvilleGrossAmount <= double(100.00)) {
		//Apply 5% discount only!
		HSVTotalDiscount = HuntsvilleGrossAmount * (discountRate_5 * double(100.00));
		
		HSVTaxTotal = HuntsvilleGrossAmount - HSVTotalDiscount; //set tax total
		return true;
	}
	else {
		//Apply 5% discount and 2% discount on remainder!
		HSVdiscount_5 = HuntsvilleGrossAmount * (discountRate_5 * double(100.00));
		HSVRemainder = HuntsvilleGrossAmount - double(100.00);
		HSVdiscount_2 = HSVRemainder * (discountRate_2 * double(100.00));
		HSVTotalDiscount = HSVdiscount_5 + HSVdiscount_2;

		HSVTaxTotal = HuntsvilleGrossAmount - HSVTotalDiscount; //set tax total
		return true;
	}
	return false; //something unexpected happened. error
}

bool SalesTax::madisonDiscount()
{
	//Calculate Madison Gross
	MadisonGrossAmount = calculateMadisonGR();

	if (MadisonGrossAmount <= float(100.00)) {
		//Apply 5% discount
		MadisonTotalDiscount = MadisonGrossAmount * (discountRate_5 * float(100.00));
		MadisonTaxTotal = MadisonGrossAmount - MadisonTotalDiscount;
		return true;
	}

	else {
		//Apply 5% discount and 2% discount on remainder!
		MadisonDiscount_5 = MadisonGrossAmount * (discountRate_5 * float(100.00));
		MadisonRemainder = MadisonGrossAmount - float(100.00);
		MadisonDiscount_2 = MadisonRemainder * (discountRate_2 * float(100.00));
		MadisonTotalDiscount = MadisonDiscount_5 + MadisonDiscount_2;
		MadisonTaxTotal = MadisonGrossAmount - MadisonTotalDiscount;
		return true;
	}
	return false; //something unexpected happened. error
}
double SalesTax::getHSVDiscount()
{
	return HSVTotalDiscount;
}

double SalesTax::getMadisonDiscount()
{
	return MadisonTotalDiscount;
}
double SalesTax::getMadisonTaxTotal()
{	
	return MadisonTaxTotal;
}
double SalesTax::getHSVTaxTotal()
{
	return HSVTaxTotal;
}

void SalesTax::initTaxProgram()
{
	string name;
	cout << "Please enter the name of the tax file\nMust be a .txt file\n";
	cin >> name;
	string filename;
	filename = name + ".txt";
	if (!readfile(filename)) {
		cout << "Error in reading file. Exiting program...\n";
		return;
	}
	cout << endl << "*****************************************\n";
	printTotalSum();
	printHSVTax();
	printMadisonTax();
}

void SalesTax::printHSVTax()
{
	if (!hsvDiscount()) {
		cout << "Error calculating Huntsville discount.\nExiting program...";
		return;
	}
	cout << "City of Huntsville Gross Tax (No Discount): " << setprecision(4) << HuntsvilleGrossAmount << endl;
	cout << "City of Huntsville Discount (5% only): " << setprecision(4) << getHSVDiscount() << endl;
	cout << "City of Huntsville Total Amount Due: " << setprecision(4) << HSVTaxTotal << "\n" << endl;
}
void SalesTax::printMadisonTax()
{
	if (!madisonDiscount()) {
		cout << "Error calculating Madison discount.\nExiting program...";
		return;
	}
	cout << "Madison Total Tax (Gross Tax Due, No discount): " << setprecision(4) << MadisonGrossAmount << endl;
	cout << "Madison Discount (5% and 2% on remainder): " << setprecision(4) << getMadisonDiscount()<< endl;
	cout << "Madison Total Amount Due: " << setprecision(4) << getMadisonTaxTotal() << "\n" << endl;
}
void SalesTax::printTotalSum()
{
	cout << "Total Sum: " << getTotalSum() << '\n' << endl;
}
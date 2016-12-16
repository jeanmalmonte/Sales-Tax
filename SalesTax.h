/* Sales Tax Program
This program will calculate Madison County Sales Tax and
City of Huntsville Standard Local Tax Return/
*/

#include <iostream>
#include <fstream>
#include <iomanip> //setprecision function
#include <string>

using namespace std;

class SalesTax
{
private:
	//Variable to open file
	ifstream taxData;
	
	//Tax Rates
	const double madisonGeneralRate = 0.005;
	const double cityHSVGSalesRate = 0.00045;	//4.50% in decimal form
	const double discountRate_5 = 0.0005;		//5% in decimal form
	const double discountRate_2 = 0.0002;		//2% in decimal form

	//Tax calculation variables
	double sumData;
	double totalSum = 0.00;
	
	double HuntsvilleGrossAmount;
	double MadisonGrossAmount;
	double HSVTaxTotal;
	double MadisonTaxTotal;

	//5% Discount Variables. Part of the if statement
	double HSVDiscount;
	double MadisonDiscount;

	//2% Discount Variables. Part of the else statement
	double HSVdiscount_5;
	double HSVdiscount_2;
	double HSVTotalDiscount;
	double HSVRemainder;
	
	double MadisonDiscount_5;
	double MadisonDiscount_2;
	double MadisonTotalDiscount;
	double MadisonRemainder;

	//Discount functions
	bool hsvDiscount();
	bool madisonDiscount();

public:
	bool readfile(string filename);					//reads file of doubles i.e 11.12

	double calculateMadisonGR();					//Madison County General Rate Gross Calculation
	double calculateHSVGS();						//City of Huntsville General Sales Gross calculation
	
	double getMadisonTaxTotal();
	double getHSVTaxTotal();
	double getTotalSum();					

	void printHSVTax();
	void printMadisonTax();
	void printTotalSum();
	
	double getHSVDiscount();
	double getMadisonDiscount();

	SalesTax();		//class constructor
	~SalesTax();	//class destructor
	void initTaxProgram();
};


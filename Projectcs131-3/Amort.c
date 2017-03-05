#include "Amort.h"
#include <stdio.h>
#include <stdlib.h>
#define ONE 1
#define ZERO 0
#define TRUE 1
#define FALSE 0
#define EIGHT 8
#define HUNDRED 100
#define HALF 0.5
#define VERYSMALL 0.001
#define MANYTIMES 20
#define YEARLY_INTEREST_RATE 1200
#pragma once

//----------------------------------------------------------------------------
//	Function:		getPaymentAmount()
//  Title:			Get payment amount
//	Description:	This function will calculate the Payment Amount for the 
//					program when annual interest rate, the size of loan
//					and number of months has been prompted
//	Programmer:		Son Minh Tran
// 
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			None		
//	Output:			None
//	Calls:			roundToNextCent()
//	Parameters:		monthlyRate	(double)
//					principal	(double)
//					months	(int)
//  Returns:		The amount of monthly payment 
//					monthlyPayment	(double)
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double getPaymentAmount(int months, double principal, double monthlyRate)
{
	double numerator = 0.0;
	double denominator = 0.0;
	if (monthlyRate == ZERO)
	{
		return roundToNextCent(principal / months);
	}
	else
	{
		numerator = pow((ONE + monthlyRate), months) 
			* principal * monthlyRate;
		denominator = pow((ONE + monthlyRate), months) - ONE;
		return roundToNextCent(numerator / denominator);
	}
}

//----------------------------------------------------------------------------
//	Function:		double getLoanAmount() 
//  Title:			Get loan amount
//	Description:	This function will calculate the Loan Amount for the 
//					program when annual interest rate, annual payment
//					and number of months has been prompted
//	Programmer:		Son Minh Tran
// 
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			None		
//	Output:			None
//	Calls:			roundToNearestCent()
//	Parameters:		totalPayment	(double)
//					monthlyRate	(double)
//					months	(int)
//  Returns:		The amount of the entire loan	
//					amountOfLoan	(double)
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double getLoanAmount(int months, double totalPayment, double monthlyRate)
{
	double numerator = 0.0;
	double denominator = 0.0;
	if (monthlyRate == ZERO)
	{
		return roundToNearestCent(totalPayment * months);
	}
	else
	{
		numerator = (pow((ONE + monthlyRate), months) - ONE) * totalPayment;
		denominator = pow((ONE + monthlyRate), months) * monthlyRate;
		return roundToNearestCent(numerator / denominator);
	}
}

//----------------------------------------------------------------------------
//	Function:		int getNumberOfMonths() 
//  Title:			Get number of month
//	Description:	This function will calculate the number of months for the 
//					program when annual interest rate, annual payment
//					and size of loan has been prompted
//	Programmer:		Son Minh Tran
// 
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		monthlyRate	(double)
//					principal	(double)
//					totalPayment	(double)
//  Returns:		The amount of months that payments need to be made	
//					months	(int)
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
int getNumberOfMonths(double principal, double totalPayment,
	double monthlyRate)
{
	double numerator = 0.0;
	double denominator = 0.0;
	if (monthlyRate == ZERO)
	{
		return (int)ceil(principal / totalPayment);
	}
	else
	{
		numerator = log(totalPayment) - 
			log(totalPayment - (principal*monthlyRate));
		denominator = log(1 + monthlyRate);
		return (int)ceil(numerator / denominator);
	}
}

//----------------------------------------------------------------------------
//	Function:		iterativeFormula() 
//  Title:			Iterative Formula
//	Description:	This function will use this iterative formula to estimate 
//					the interest rate
//	Programmer:		Son Minh Tran
// 
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		sizeOfLoan	(double)
//					monthlyPayment	(double)
//					rate	(double)
//					months	(double)
//  Returns:		The solution from the formula	
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double iterativeFormula(double sizeOfLoan, double monthlyPayment,
	double rate, double months)
{
	//formula to estimate apr
	double answer = (monthlyPayment / sizeOfLoan) - ((rate * 
		pow(1 + rate, months)) / (pow(1 + rate, months) - 1));
	return answer;
}

//----------------------------------------------------------------------------
//	Function:		getAppDer() 
//  Title:			Get derivative for formula
//	Description:	This function will find the derivative of iterativeFormula
//  Programmer:		Son Minh Tran
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		secondary	(double)
//					primary	(double)
//					distance	(double)
//  Returns:		The derivative number for a formula
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double getAppDer(double secondary, double primary, double distance)
{
	double answer = 0;
	answer = (secondary - primary) / distance;
	return answer;
}


//----------------------------------------------------------------------------
//	Function:		getInterestRate()
//  Title:			Get interest rate
//	Description:	This function will calculate the interest rate (APR) 
//					for the program when size of loan, annual
//					payment and number of months has been prompted
//  Programmer:		Son Minh Tran
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			None		
//	Output:			None
//	Calls:			getAppDer()
//					iterativeFormula()
//					roundToOneEighth()
//	Parameters:		sizeOfLoan	(double)
//					monthlyPayment	(double)
//					months	(int)
//  Returns:		The interest rate for the program	
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double getInterestRate(double sizeOfLoan, double monthlyPayment, int months)
{
	double rateGuess = 0.0;
	int counter = 0;
	if (monthlyPayment * months <= sizeOfLoan)
	{
		return 0;
	}
	//apply newton-raphson method
	rateGuess = ((monthlyPayment * months) - sizeOfLoan) / (sizeOfLoan);
	int keepGoing = TRUE;
	while (keepGoing == TRUE)
	{
		rateGuess = rateGuess - (iterativeFormula(sizeOfLoan, monthlyPayment,
			rateGuess, months) / 
			(getAppDer(iterativeFormula(sizeOfLoan,
				monthlyPayment, rateGuess + VERYSMALL, months),
				iterativeFormula
				(sizeOfLoan, monthlyPayment, rateGuess, months), VERYSMALL)));
		counter++;
		if (counter == MANYTIMES)
		{
			keepGoing = FALSE;
		}
	}
	rateGuess = rateGuess * YEARLY_INTEREST_RATE;
	return roundToOneEighth(rateGuess);
}

//----------------------------------------------------------------------------
//	Function:		readApr()
//  Title:			read APR
//	Description:	This function will read in the annual percentage rate
//					from the console where user enter the apr
//  Programmer:		Son Minh Tran
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			user input the apr		
//	Output:			roudn to one eight and print out apr
//	Calls:			safeReadDouble()
//					roundToOneEighth()
//	Parameters:		void
//  Returns:		the APR	
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double readApr() {
	double interestRate = 0.0;
	printf("\nEnter the interest rate (APR) you will be paying"
		"(nearest 1/8 points, >=0): ");
	int condition = FALSE;
	do
	{
		safeReadDouble(&interestRate, "Please enter a non-negative number");
		if (interestRate < 0)
		{
			printf("please enter a positive value for Annual Payment Rate: ");
			condition = TRUE;
		}
		else {
			interestRate = roundToOneEighth(interestRate);
			printf("Interest: %.3lf%c", interestRate, '%');
			condition = FALSE;
		}
	} while (condition == TRUE);
	return interestRate;
}

//----------------------------------------------------------------------------
//	Function:		readPrincipal()
//  Title:			read Principal
//	Description:	This function will read in the total loan 
//					from the console where user enter the total loan
//  Programmer:		Son Minh Tran
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			user input the principal		
//	Output:			roudn to nearest cent and print out the console
//	Calls:			safeReadDouble()
//					roundToNearestCent()
//	Parameters:		void
//  Returns:		the principal
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double readPrincipal() {
	double loan = 0.0;
	printf("\nEnter the amount of money to be borrowed (amount > 0): $");
	int condition = FALSE;
	do
	{
		safeReadDouble(&loan, "\nPlease enter a non-negative number");
		if (loan <= 0)
		{
			printf("\nThe amount of Loan needs to be bigger than 0");
			condition = TRUE;
		}
		else {
			printf("Principal: $%.2lf", loan);
			condition = FALSE;
		}
	} while (condition == TRUE);
	return roundToNearestCent(loan);
}

//----------------------------------------------------------------------------
//	Function:		readMonth()
//  Title:			read Principal
//	Description:	This function will read in the number of month 
//					from the console where user enter the number of months
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			user input the month	
//	Output:			print out the month
//	Calls:			safeReadInt()
//	Parameters:		void
//  Returns:		the numbers of month
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
int readMonth() {
	int numMonth = 0;
	int condition = FALSE;
	printf("\nEnter the number of months you will be making "
		"payments (0 < months <= 360): ");
	do
	{
		safeReadInt(&numMonth, "\nPlease enter a non - negative"
			"number from 0 to 360:");
		if (numMonth <= 0 || numMonth > 360)
		{
			puts("\nYou have to input positive number for number of months");
			condition = TRUE;
		}
		else {
			printf("Number of Months to pay: %d", numMonth);
			condition = FALSE;
		}
	} while (condition == TRUE);
	return numMonth;
}

//----------------------------------------------------------------------------
//	Function:		readPayment()
//  Title:			read Payment
//	Description:	This function will read in amount of monthly payment
//					from the console where user enter the monthly payment
//	Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
//	Input:			user input the amount of monthly payment	
//	Output:			roudn to nearest cent and print out the monthly payment
//	Calls:			safeReadDouble()
//					roundToNearestCent()
//	Parameters:		void
//  Returns:		the amount of monthly payment
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double readPayment() {
	double payment = 0.0;
	int condition = FALSE;
	printf("\nEnter the amount of the monthly payment (amount > 0): $");
	do
	{
		safeReadDouble(&payment, "\nPlease enter a non-negative number");
		if (payment <= 0)
		{
			puts("\nPlease enter number bigger" 
				"than 0 for your monthly payment");
			condition = TRUE;
		}
		else {
			printf("Payment: $%.2lf per month", payment);
			condition = FALSE;
		}
	} while (condition == TRUE);
	return roundToNearestCent(payment);
}

//----------------------------------------------------------------------------
//	Function:		safeReadDouble()
//  Title:			Read in safe double value
//	Description:	This function will read in the right (double) input number 
//					into the program
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			read in a number
//					number_ptr (double*)
//	Output:			a prompt if a invalid number has been entered
//	Calls:			cleanBuffer()
//	Parameters:		number_ptr (int*)
//					prompt (const char*)
//  Returns:		None
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
void safeReadDouble(double * number_ptr, const char * prompt)
{
	while ((scanf("%lf", number_ptr)) != ONE)
	{
		puts(prompt);
		cleanBuffer();
	}
	cleanBuffer();
}

//----------------------------------------------------------------------------
//	Function:		safeReadInt()
//  Title:			Read in safe integer value
//	Description:	This function will read in the right (integer) input  
//					number into the program
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			read in a number
//					number_ptr (double*)
//	Output:			a prompt if a invalid number has been entered
//	Calls:			cleanBuffer()
//	Parameters:		number_ptr (int*)
//					prompt (const char*)
//  Returns:		None
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
void safeReadInt(int * number_ptr, const char * prompt)
{
	while ((scanf("%d", number_ptr)) != ONE)
	{
		puts(prompt);
		cleanBuffer();
	}
	cleanBuffer();
}

//----------------------------------------------------------------------------
//	Function:		cleanBuffer()
//  Title:			Clean the buffer
//	Description:	This function will clean the buffer for the program
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		None
//  Returns:		None
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
void cleanBuffer()
{
	while (getchar() != '\n');
}

//----------------------------------------------------------------------------
//	Function:		printMenu()
//  Title:			print menu
//	Description:	This function will print out the menu option
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		None
//  Returns:		None
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
void printMenu() {
	printf("Amortization!\n");
	printf("Amortization Program written by Son Tran. ");
	printf("Please select a Menu Option\n\n");
	printf("\t1. Calculate (P)ayment Size\n");
	printf("\t2. Calculate (L)oan Size\n");
	printf("\t3. Calculate (N)umber of Payments\n");
	printf("\t4. Calculate (I)nterest (APR)\n");
	printf("\t5. (Q)uit\n\n");
	printf("Enter a menu option: ");
}

//----------------------------------------------------------------------------
//	Function:		roundToNextCent()
//  Title:			Round to Next Cent
//	Description:	This function will round the amount of money to next cent
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		number	(double)
//  Returns:		double number after rounding to next cent
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double roundToNextCent(double number) {
	return ceil(number * HUNDRED) / HUNDRED;
}

//----------------------------------------------------------------------------
//	Function:		roundToOneEighth()
//  Title:			Round to one eighth
//	Description:	This function will round the apr to one eighth
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		number	(double)
//  Returns:		double number after rounding to one eighth
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double roundToOneEighth(double number) {
	double out = 0.0;
	double roundUp = 0.0;
	double roundDown = 0.0;
	roundUp = ceil(number * EIGHT) / EIGHT;
	roundDown = floor(number * EIGHT) / EIGHT;
	if (fabs(roundUp - number) <= fabs(roundDown - number))
		return roundUp;
	else
		return roundDown;
}

//----------------------------------------------------------------------------
//	Function:		roundToNearestCent()
//  Title:			Round to nearest cent
//	Description:	This function will round the amount of money to the 
//					nearest cent
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			None		
//	Output:			None
//	Calls:			None
//	Parameters:		number	(double)
//  Returns:		double number after rounding to nearest cent
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
double roundToNearestCent(double number) {
	return floor(number * HUNDRED + HALF) / HUNDRED;
}

//----------------------------------------------------------------------------
//	Function:		printTable()
//  Title:			print table
//	Description:	This function will print the table out to a file
//  Programmer:		Son Minh Tran
//  Date:			03/04/2017
//	Version:			1.0
//	Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit 
//	Input:			None		
//	Output:			print and export a file contain the table of APR, payment
//	Calls:			roundToNextCent
//	Parameters:		principal	(double)
//					payment		(double)
//					monthlyRate	(double)
//					month		(int)
//  Returns:		void
//	History Log:	03/04/2017 Complete version 1.0
//----------------------------------------------------------------------------
void printTable(double principal, double payment, double monthlyRate, int month) {
	char ch = ' ';
	char filename[FILENAME_MAX] = "AmTable.txt";
	int returnValue = EXIT_SUCCESS;
	double interestPaid = 0.0;
	double principalPaid = 0.0;
	double loanBalance = 0.0;
	double tabPayment = 0.0;
	int countMonth = 1;
	FILE * outFileHandle = NULL;
	int i = 0;
	printf("\nDo you wish to print an Amortization Table(Y/N)? Y\b");
	ch = getche();
	if (ch == 'N' || ch == 'n')
	{
		return;
	}
	else {
		outFileHandle = fopen(filename, "w");
		loanBalance = principal;
		if (outFileHandle == NULL)
		{
			printf("Could not open file %s for output.\n"
				"Press any key to Continue", filename);
			returnValue = EXIT_FAILURE;
		}
		else {
			fprintf(outFileHandle, "Amortization Table for $%.2lf Loan "
				"at %.3lf%% interest for %d months\n", principal,
				monthlyRate * 1200, month);
			fprintf(outFileHandle, "\n");
			fprintf(outFileHandle, "%s %22s %15s %15s\n",
				"Payments", "Principal Paid", "Interest Paid",
				"Loan Balance");
			if (monthlyRate == 0)
			{
				tabPayment = payment;
				interestPaid = 0;
				principalPaid = payment;
				for (i = 0; i < month; i++)
				{
					if (i < month - 1)
					{
						loanBalance -= principalPaid;
					}
					else
					{
						principalPaid = loanBalance;
						tabPayment = loanBalance;
						loanBalance = 0;
					}
					fprintf(outFileHandle, "%-5d ( %8.2lf) ",
						countMonth, tabPayment);
					fprintf(outFileHandle, "$ %13.2lf ",
						principalPaid);
					fprintf(outFileHandle, "$ %13.2lf ",
						interestPaid);
					fprintf(outFileHandle, "$ %12.2lf \n",
						loanBalance);
					countMonth++;
				}
			}
			else
			{
				for (i = month; i > ZERO; i--)
				{
					if (i > ONE)
					{
						tabPayment = getPaymentAmount(i, loanBalance, monthlyRate);
						interestPaid = loanBalance * monthlyRate;
						principalPaid = tabPayment - interestPaid;
						loanBalance -= principalPaid;
					}
					else
					{
						interestPaid = loanBalance * monthlyRate;
						principalPaid = loanBalance;
						tabPayment = roundToNextCent(principalPaid + interestPaid);
						loanBalance = 0;
					}

					fprintf(outFileHandle, "%-5d ( %8.2lf) ",
						countMonth, tabPayment);
					fprintf(outFileHandle, "$ %13.2lf ",
						principalPaid);
					fprintf(outFileHandle, "$ %13.2lf ",
						interestPaid);
					fprintf(outFileHandle, "$ %12.2lf \n",
						loanBalance);
					countMonth++;
				}
			}
		}
		fclose(outFileHandle);
		system("AmTable.txt");
	}
}

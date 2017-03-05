//----------------------------------------------------------------------------
// File: MainAmortization.c
// Functions:
//		int main(int argc, char *argv[])
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Amort.h"
#define TRUE 1
#define FALSE 0
#define MONTHPERCENT 1200
//----------------------------------------------------------------------------
// Function:		main(void)		
//
// Title:			Main Amortization
//
// Description:		The program has different function to calculate based on
//					the option user input in the command prompt. Users choose
//					1 to calculate the monthly payment based on APR, principal
//					and the number of months to make payment.user choose 2 to 
//					calculate the total loan based on monthly payment, apr, 
//					and number of months. Users choose 3 to calculate number 
//					of months based on principal, monthly payment, and apr.
//					Users choose 4 to calculate the apr based on principal,
//					monthly payment and number of months making payment.
//					Users choose 5 to exit. Especially, at the end of every 
//					option from 1 to 4, user can choose yes or no to print 
//					the table of payment each month
// Programmer:		Son Minh Tran
// 
// Date:			03/04/2017
// Version:			1.0
//
// Environment:		HP Elitebook 8570P 
//					Hardware: 8GB
//							  Intel(R) Core(TM) i5-3320M 
//					Software: OS: MS Windows 10 Professional 64-bit
// Output:			The monthly payment if choose 1
//					The total loan if choose 2
//					The number months making payment if choose 3
//					The apr if choose 4
//					Exit the program if choose 5
//					
//
//	Parameters:		void
//  Returns:		EXIT_SUCCESS for successful completion 
//					Or EXIT_FAILURE when the program cannot read the 
//					data file and output file
// Called By:		None
// Calls:			readApr()
//					readPrincipal()
//					readMonth()
//					readPayment()
//					getPaymentAmount(int months, double principal,
//									double monthlyRate)
//					getLoanAmount(int months, double totalPayment, 
//									double monthlyRate)
//					getNumberOfMonths(double principal, double totalPayment,
//									double monthlyRate)
//					getInterestRate(double sizeOfLoan, double monthlyPayment, 
//									int months)
//					printTable(double principal, double payment, 
//									double monthlyRate, int month)
//
// History Log:		Commit github on 01/24/2017: 
//					Commit github on 01/25/2017: 
//					Commit github on 02/04/2017: 
//					Commit github on 02/08/2017: 
//----------------------------------------------------------------------------
int main(void) {
	short again = TRUE;
	double totalPayment = 0.0;
	double principal = 0.0;
	double lowBound = 0.0;
	double upBound = 0.0;
	int month = 0;
	double monthlyRate = 0.0;
	double apr = 0.0;
	int initialGuessMonth = 0;

	do
	{
		//clean and print menu to console
		system("cls");
		printMenu();
		switch (getche())
		{
			case '1':
			case 'P':
			case 'p':
				//read the apr
				apr = readApr();
				//convert to monthly rate
				monthlyRate = apr / MONTHPERCENT;
				//read the principal
				principal = readPrincipal();
				//read the month
				month = readMonth();
				//calculate the payment each month
				totalPayment = getPaymentAmount(month, 
					principal, monthlyRate);
				//print out the payment for each month
				printf("\nPayment: $%.2lf per month", totalPayment);
				//print table or not depend on user choice
				printTable(principal, totalPayment, monthlyRate, month);
				break;
			case '2':
			case 'l':
			case 'L':
				//read the APR
				apr = readApr();
				//convert to monthly rate
				monthlyRate = apr / MONTHPERCENT;
				//read the payment of each month
				totalPayment = readPayment();
				//read number of months making payment
				month = readMonth();
				//calculate the loan size
				principal = getLoanAmount(month, totalPayment, monthlyRate);
				//print out the loan size
				printf("\nLoan Amount: $%.2lf", principal);
				//print out the table of loan depend on user choice
				printTable(principal, totalPayment, monthlyRate, month);
				break;
			case '3':
			case 'N':
			case 'n':
				//read the apr
				apr = readApr();
				//convert to monthly rate
				monthlyRate = apr / MONTHPERCENT;
				//read the amount of principal
				principal = readPrincipal();
				//set uper and lower bound for condition
				lowBound = roundToNearestCent(principal * 
					(apr / MONTHPERCENT));
				upBound = roundToNearestCent(principal *
					(1 + (apr / MONTHPERCENT)));
				printf("\nThe payment you entered must be greater than"
					" %.2lf and no bigger than %.2lf", lowBound, upBound);
				//keep reading until correct
				do
				{
					totalPayment = readPayment();
					if ((totalPayment < lowBound) || (totalPayment > upBound))
					{
						printf("\nThe payment you entered must be greater than"
						" %.2lf and no bigger than %.2lf", lowBound, upBound);
					}
				} while ((totalPayment < lowBound) || (totalPayment > upBound));
				//calculate the month
				month = getNumberOfMonths(principal, totalPayment, monthlyRate);
				//print out the month
				printf("\nNumber of months to pay the loan: %d", month);
				//print the table if user choose y
				printTable(principal, totalPayment, monthlyRate, month);
				break;
			case '4':
			case 'I':
			case 'i':
				//read principal
				principal = readPrincipal();
				//read payment amount
				totalPayment = readPayment();
				//guess for the interest rate
				initialGuessMonth = ceil(principal / totalPayment);
				printf("\nNumber of months must be at least %d",
					initialGuessMonth);
				do
				{
					month = readMonth();
					if (month < initialGuessMonth)
					{
						printf("\nThe month you entered must be at least %d",
							initialGuessMonth);
					}
				} while (month < initialGuessMonth);
				//calculate the apr
				apr = getInterestRate(principal, totalPayment, month);
				//calculate monthly rate
				monthlyRate = apr / MONTHPERCENT;
				//print out the apr
				printf("\nAnnual Percentage Rate: %.3lf%c", apr, '%');
				//print the table if user choose y
				printTable(principal, totalPayment, monthlyRate, month);
				break;
			case '5':
			case 'Q':
			case 'q':
				//exit
				return EXIT_SUCCESS;
			default:
				//clean and print the menu
				system("cls");
				printMenu();
				again = TRUE;
				break;
		}
	} while (again == TRUE);
	getchar();
	return EXIT_SUCCESS;
}
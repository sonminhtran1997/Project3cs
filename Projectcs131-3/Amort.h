#ifndef AMORT_H
#define AMORT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#pragma warning(disable: 4996)
double getPaymentAmount(int months, double principal, double monthlyRate);
double getLoanAmount(int months, double totalPayment, double monthlyRate);
int getNumberOfMonths(double principal, double totalPayment, double monthlyRate);
double iterativeFormula(double sizeOfLoan, double monthlyPayment,
	double rate, double months);
double getAppDer(double secondary, double primary, double distance);
double getInterestRate(double sizeOfLoan, double monthlyPayment, int months);
void safeReadDouble(double* number_ptr, const char * prompt);
void safeReadInt(int* number_ptr, const char * prompt);
void cleanBuffer();
void printMenu();
void printTable(double principal, double payment, double monthlyRate, int month);
double readApr();
double readPrincipal();
double readPayment();
int readMonth();
double roundToNextCent(double number);
double roundToOneEighth(double number);
double roundToNearestCent(double number);
#endif #pragma once

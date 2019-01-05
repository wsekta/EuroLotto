#pragma once
#include <stdio.h> 
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef enum { MALE, FAMALE } SexType;
typedef enum { MON, TUE, WED, THU, FRI, SAT, SUN } DayNames;
typedef enum { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC } MonthNames;

//wszystkie define
#define LOTTO 50
#define EXTRALOTTO 10

#define MAXBETS			5
#define MAXEXTRABETS	2

#define ALLOCPLAYER		5
#define ALLOCBET		3
#define MAXNAME			31

#define PAYBACK_LEN 10

#define SWIFT_BANK_LEN 4
#define SWIFT_COUNTRY_LEN 2
#define SWIFT_LOC_LEN 2
#define SWIFT_DEPARTMENT_LEN 3

#define IBAN_CONTROLSUM_LEN 2
#define IBAN_COUNTRY_LEN 2
#define IBAN_BANKID_LEN 8
#define IBAN_ACC_NUMBER_LEN 16

#define PESEL_LEN 11


typedef struct 
{
	int* bFive;
	int* bTwo;
} Bets;

typedef struct
{
	char Institute[ SWIFT_BANK_LEN ];
	char Country[ SWIFT_COUNTRY_LEN ];
	char Location[ SWIFT_LOC_LEN ];
	char Department[ SWIFT_DEPARTMENT_LEN ];
} Swift;

typedef struct
{
	char ControlSum[ IBAN_CONTROLSUM_LEN ];
	char BankId[ IBAN_BANKID_LEN ];
	char AccNumber[ IBAN_ACC_NUMBER_LEN ];
	char Country[ IBAN_COUNTRY_LEN ];
} Iban;

typedef struct 
{
	Swift swift;
	Iban iban;
} Account;


typedef struct
{
	DayNames Day;
	MonthNames Month;
	int DayNumber;
	int Year;
} Date;

typedef struct
{
	char Surname[ MAXNAME ];
	char Name[ MAXNAME ];
	SexType  sex;
	Date Date;
	Account account;
	char PayBack[ PAYBACK_LEN ];
	Bets* Bets;
	int ReadBets;
	//int BetsLimit;
	char PESEL[ PESEL_LEN ];
} Player;
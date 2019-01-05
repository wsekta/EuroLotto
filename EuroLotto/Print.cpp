#include "Print.h"

void PrintSex( FILE* fout, Player* p );
void PrintDate( FILE* fout, Player* p );
void PrintBets( FILE* fout, Bets* bets );
void PrintTab( FILE* fout, char* str, int nSize );

void PrintResults( int** pNums, Player** pDraws, int nDrawsNo )
{
	FILE * fout = NULL;
	if ( ( fout = fopen( "lottoOutput.txt", "w+" ) ) == NULL )
	{
		printf( "PrintResults: file error" );
		return;
	}
	
	for ( int i = 0; i < nDrawsNo; i++)
	{
		Player* p = pDraws[i];
		fprintf( fout, "%s %s\t\t", p->Surname, p->Name );
		PrintSex( fout, p );
		PrintDate( fout, p );

		//fprintf( fout, "%4c%2c%2c%3c %2c%2c%8c%16c %11c ", 
		fprintf( fout, "\n" );
		PrintTab( fout, p->account.swift.Institute, SWIFT_BANK_LEN );
		fprintf( fout, " " );
		PrintTab( fout, p->account.swift.Country, SWIFT_COUNTRY_LEN );
		fprintf( fout, " " );
		PrintTab( fout, p->account.swift.Location, SWIFT_LOC_LEN );
		fprintf( fout, " " );
		PrintTab( fout, p->account.swift.Department, SWIFT_DEPARTMENT_LEN );
		fprintf( fout, "\t\t" );
		PrintTab( fout, p->account.iban.Country, IBAN_COUNTRY_LEN );
		fprintf( fout, " " );
		PrintTab( fout, p->account.iban.ControlSum, IBAN_CONTROLSUM_LEN );
		fprintf( fout, " " );
		PrintTab( fout, p->account.iban.BankId, IBAN_BANKID_LEN );
		fprintf( fout, " " );
		PrintTab( fout, p->account.iban.AccNumber, IBAN_ACC_NUMBER_LEN );
		/*fprintf( fout, " " );
		PrintTab( fout, p->PESEL, PESEL_LEN );*/

		fprintf( fout, "\n------------------------------------------------------------------------\n" );
		Bets* b = p->Bets;
		for ( int j = 0; j < p->ReadBets; j++ )
		{
			PrintBets( fout, b++ );
		} 
	}

	fprintf( fout, "\n\n\n========================================\n              STATYSTYKI\n========================================\n" );

	int *pNumsAll5 = pNums[ 0 ];
	for ( int i = 0; i < LOTTO; i++ )
	{
		fprintf( fout, "%d: %d\t", i + 1, *pNumsAll5++ ); 
		if ( ( ( i + 1 ) % 10 ) == 0 )
			fprintf( fout, "\n" );
	}

	fprintf( fout, "\n\n" );
	int *pNumsAll2 = pNums[ 1 ];
	for ( int i = 0; i < EXTRALOTTO; i++ )
	{
		fprintf( fout, "%d: %d\t", i + 1, *pNumsAll2++ ); 
		if ( ( ( i + 1 ) % 10 ) == 0 )
			fprintf( fout, "\n" );
	}
	fclose( fout );
}



//==============================================
void PrintSex( FILE* fout, Player* p )
{
	switch ( p->sex )
	{
	case FAMALE:fprintf( fout, "*Panienka* " ); break;
	case MALE:fprintf( fout, "*Facet* " ); break;
	}
}



//==============================================
void PrintDate( FILE* fout, Player* p )
{
	switch ( p->Date.Day )
	{
	case MON:fprintf( fout, "Mon" ); break;
	case TUE:fprintf( fout, "Tue" ); break;
	case WED:fprintf( fout, "Wed" ); break;
	case THU:fprintf( fout, "Thu" ); break;
	case FRI:fprintf( fout, "Fri" ); break;
	case SAT:fprintf( fout, "Sat" ); break;
	case SUN:fprintf( fout, "Sun" ); break;

	}
	fprintf( fout, ", %2d/", p->Date.DayNumber );

	switch ( p->Date.Month )
	{
	case JAN: fprintf( fout, "Jan/" ); break;
	case FEB: fprintf( fout, "Feb/" ); break;
	case MAR: fprintf( fout, "Mar/" ); break;
	case APR: fprintf( fout, "Apr/" ); break;
	case MAY: fprintf( fout, "May/" ); break;
	case JUN: fprintf( fout, "Jun/" ); break;
	case JUL: fprintf( fout, "Jul/" ); break;
	case AUG: fprintf( fout, "Aug/" ); break;
	case SEP: fprintf( fout, "Sep/" ); break;
	case OCT: fprintf( fout, "Oct/" ); break;
	case NOV: fprintf( fout, "Nov/" ); break;
	case DEC: fprintf( fout, "Dec/" ); break;
	}
	fprintf( fout, "%4d ", p->Date.Year );
}



//==============================================
void PrintBets( FILE* fout, Bets * pBets )
{
	Bets * p = pBets;
	int *v = p->bFive;
	int *q = p->bTwo;
	for ( int i = 0; i < MAXBETS; i++ )
		fprintf( fout, "%2d ", *v++ );
	fprintf( fout, "\t\t" );
	for ( int i = 0; i < MAXEXTRABETS; i++ )
		fprintf( fout, "%2d ", *q++ );
	fprintf( fout, "\n" );
}



//==============================================
void PrintTab( FILE* fout, char* str, int nSize )
{
	for ( int i = 0; i < nSize; i++ )
		fprintf(fout,"%c", str[i]);
}
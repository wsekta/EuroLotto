#include "defs.h"
#include "Data.h"
#include "Print.h"

#include <string.h>

void HeapCheck(); // _heapchk
void CalcStat( int **pNums, Player** pDraws, int nDrawsNo ); // zlicza ilość wystąpień każdej licby we wszystkich zakładach osobno dla podstawowych i dodatkowych
void Sort( Player** pDraws, int nDrawsNo );

int main(int argc, char** argv)
{
	//Parametrem programu jest plik tekstowy z zakładami
	if ( argc!=2 )
	{
		printf( "EuroLotto.exe [input file]" );
		return 1;
	}
	//def dynamicnej tab 
	Player** pPlayers = NULL;
	int nPlayersNumber = 0;
	if ( !( nPlayersNumber = ReadData( &pPlayers, argv[ 1 ] )) )
	{
		printf( "main: error with file" );
		//return 1;
	}
	//printf( "%d\n",nPlayersNumber);
	
	int **pNum = ( int** )calloc( 2, sizeof( int* ) );//!!!!!
	if ( !pNum )
	{
		printf( "main: allocation error" );
		return 0;
	}
	pNum[0]= ( int* )calloc( LOTTO, sizeof( int ) );
	pNum[1] = ( int* )calloc( EXTRALOTTO, sizeof( int ) );
	if( !pNum[ 0 ] || !pNum[ 1 ] )
	{
		printf( "main: allocation error" );
		return 0;
	}

	
	CalcStat( pNum, pPlayers, nPlayersNumber );
	Sort( pPlayers, nPlayersNumber );
	PrintResults( pNum, pPlayers, nPlayersNumber );

	free( pNum[ 0 ] );
	free( pNum[ 1 ] );
	free( pNum );
	FreeMem( &pPlayers, nPlayersNumber );
	HeapCheck();
	return 0;
}

void HeapCheck() {
	int heapstatus = _heapchk();
	switch ( heapstatus )
	{
	case _HEAPOK:
		printf( " OK - heap is fine\n" );
		break;
	case _HEAPEMPTY:
		printf( " OK - heap is empty\n" );
		break;
	case _HEAPBADBEGIN:
		printf( "ERROR - bad start of heap\n" );
		break;
	case _HEAPBADNODE:
		printf( "ERROR - bad node in heap\n" );
		break;
	}
}

void Sort( Player** pDraws, int nDrawsNo )
{
	for ( int i = 0; i < nDrawsNo - 1; i++ )
	{
		Player* min = pDraws[ i ];
		int x = i;

		for ( int j = i + 1; j < nDrawsNo; j++ )
		{
			if ( strcmp(min->Surname, pDraws[j]->Surname) > 0 )
			{
				min = pDraws[ j ];//niebezp kopiow struktur  gdy str ma skladowe dynamiczne
				x = j;
			}
		}
		pDraws[ x ] = pDraws[ i ];
		pDraws[ i ] = min;
	}
}

void CalcStat( int **pNums, Player** pDraws, int nDrawsNo )
{
	int* a5 = pNums[0];
	int* a2 = pNums[1];

	for ( int i = 0; i < nDrawsNo; i++ )
	{
		Player *p = *pDraws++;
		Bets* bets = p->Bets;

		for ( int j = 0; j < p->ReadBets; j++ )
		{
			int* Num5 = bets->bFive;
			for ( int k = 0; k < MAXBETS; k++ )
			{
				if ( ( *Num5 > LOTTO + 1  ) || ( *Num5 < 1 ) )
				{
					printf( "CalcStat: wrong data");
					return;
				}
				a5[ *Num5++ - 1 ]++;
			}

			int* Num2 = bets->bTwo;
			for ( int k = 0; k < MAXEXTRABETS; k++ )
			{
				if ( ( *Num2 >  EXTRALOTTO  ) ||  *Num2 < 1 )
				{
					printf( "CalcStat: wrong data" );
					return;
				}
				a2[ *Num2++ - 1 ]++;
			}
			bets++;
		}
	}
}
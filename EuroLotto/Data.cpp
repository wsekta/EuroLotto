#include "Data.h"

int AllocAddMem( Player*** pTab, int nCurrSize );
int AllocAddMemBets( Bets** pTab, int nCurrSize );

int SetSex( Player* p, char c );
int SetDate( Player* p, int d, int m, int y );

int ReadData( Player*** pAllDraws, const char* sFileName )
{
	//otwiera plik wejœciowy i bada blendu - gdy blad wypisuje komunikat  i zwraca 0
	FILE* fin = fopen( sFileName, "rt" );
	if ( !fin )
	{
		printf( "ReadData: file error" );
		return 0;
	}
	int nCurrSize = 0;
	while ( !feof( fin ) )
	{
		if ( fgetc( fin ) == '*' )
		{
			if ( !( nCurrSize % ALLOCPLAYER ) )
			{
				if ( !AllocAddMem( pAllDraws, nCurrSize ) )
					break;
			}

			Player *p = ( *pAllDraws )[ nCurrSize++ ] = ( Player* )calloc( 1, sizeof( Player ) );
			if ( !p )
			{
				printf( "ReadData: allocation error" );
				return 0;
			}

			char c;
			int d;
			int m;
			int y;
			fscanf( fin, "%s %s %c %4c%2c%2c%3c %2c%2c%8c%16c %d/%d/%d %11c",
				&p->Surname, &p->Name, &c,
				&p->account.swift.Institute, &p->account.swift.Country,
				&p->account.swift.Location, &p->account.swift.Department,
				&p->account.iban.Country, &p->account.iban.ControlSum,
				&p->account.iban.BankId, &p->account.iban.AccNumber,
				&d, &m, &y, &p->PESEL );

			if ( !SetDate( p, d, m, y ) || !SetSex( p, c ) )
			{
				printf( "ReadData: wrong data" );
				break;
			}

			while ( !feof( fin ) )
			{
				if ( ( c = fgetc( fin ) ) == '*' )
				{
					ungetc( c, fin );
					break;
				}
				if ( c<'0' || c>'9' )
					continue;
				ungetc( c, fin );
				if ( !( p->ReadBets % ALLOCBET ) )
				{
					if ( !AllocAddMemBets( &p->Bets, p->ReadBets ) )
						break;
				}
				Bets* q = &( p->Bets[ p->ReadBets++ ] );



				int* v5 = q->bFive = ( int* )calloc( MAXBETS, sizeof( int ) );                                                                                            // wczytywac jedna instrukcja fscanf wszystkie dane opidujace gracza
				int* v2 = q->bTwo = ( int* )calloc( MAXEXTRABETS, sizeof( int ) );
				if ( !v5 || !v2 )
				{
					printf( "ReadData: allocation error" );
					break;
				}
				for ( int i = 0; i < MAXBETS; i++ )                                                                  // przy czym dane dot. plci i daty do zmiennych pomocniczych
					fscanf( fin, "%d", v5++ );
				for ( int i = 0; i < MAXEXTRABETS; i++ )
					fscanf( fin, "%d", v2++ );
			}
		}
	}
	fclose( fin );
	return nCurrSize;
}



//==============================================
int AllocAddMem( Player*** pTab, int nCurrSize )
{
	//u¿ywa funkcji realloc i memset przy czym
	if ( !( nCurrSize % ALLOCPLAYER ) )
	{
		Player** tmp = ( Player** )realloc( *pTab, ( nCurrSize + ALLOCPLAYER ) * sizeof( Player* ) );
		if ( !tmp )
		{
			printf( "AllocAddMem: allocation error" );
			return 0;
		}
		*pTab = tmp;
		memset( ( *pTab + nCurrSize ), 0, sizeof( Player* ) * ALLOCPLAYER );
		return 1;
	}
	return 0;
}



//==============================================
int AllocAddMemBets( Bets** pTab, int nCurrSize )
{
	Bets* tmp = ( Bets* )realloc( *pTab, sizeof( Bets )*( nCurrSize + ALLOCBET ) );
	if ( !tmp )
	{
		printf( "AllocAddMemBets: allocation error" );
		return 0;
	}
	*pTab = tmp;
	memset( ( *pTab + nCurrSize ), 0, sizeof( Bets ) * ALLOCBET );
	return 1;
}



//==============================================
void FreeMem( Player*** pTab, int nDrawsNo )
{

	for ( int i = 0; i < nDrawsNo; i++ )
	{
		Player* p = (*pTab)[ i ];
		Bets* b = p->Bets;
		for ( int j = 0; j < p->ReadBets; j++, b++ )
		{
			free( b->bFive );
			free( b->bTwo );
		}
		free( p->Bets );
		free( p );
	}
	free( *pTab );
}


//==============================================
int SetSex( Player* p, char c )
{
	switch ( c )
	{
	case 'f':
	case 'F':
		p->sex = FAMALE;
		return 1;
	case 'm':
	case 'M':
		p->sex = MALE;
		return 1;
	default:
		return 0;
	}
}



//==============================================
int SetDate( Player* p, int d, int m, int y )
{
	if ( d > 0 && d < 32 && m >0 && m < 13 && y>1900 )
	{
		p->Date.DayNumber = d;
		tm rTime; //
		rTime.tm_year = y - 1900;
		rTime.tm_mon = m - 1;
		rTime.tm_mday = d - 1;

		rTime.tm_hour = rTime.tm_min = rTime.tm_sec = 0;
		mktime( &rTime );
		switch ( rTime.tm_wday )
		{
		case 0: p->Date.Day = MON; break;
		case 1: p->Date.Day = TUE; break;
		case 2: p->Date.Day = WED; break;
		case 3: p->Date.Day = THU; break;
		case 4: p->Date.Day = FRI; break;
		case 5: p->Date.Day = SAT; break;
		case 6: p->Date.Day = SUN; break;
		}

		switch ( m )             //miesiac
		{
		case 1:p->Date.Month = JAN; break;
		case 2:p->Date.Month = FEB; break;
		case 3:p->Date.Month = MAR; break;
		case 4:p->Date.Month = APR; break;
		case 5:p->Date.Month = MAY; break;
		case 6:p->Date.Month = JUN; break;
		case 7:p->Date.Month = JUL; break;
		case 8:p->Date.Month = AUG; break;
		case 9:p->Date.Month = SEP; break;
		case 10:p->Date.Month = OCT; break;
		case 11:p->Date.Month = NOV; break;
		case 12:p->Date.Month = DEC; break;
		}

		p->Date.Year = y;
		return 1;
	}
	return 0;
}
/*	Author:	Matthew Branstetter
 *	Title:	dValues.h
 *	Date:	11/21/2013
 */

#include <KLpartition.h>
 
void KLpartition::getDValues( vector<int>& partA, vector<int>& partB ) 
{
	int location = 0;
	int value = 0;
	int pA = -1;
	int pB = -1;
	for( int i = 0 ; (unsigned)i < matrix.size() ; i++)
	{
		location = i + 1;
		pA = findValue( partA , location );
		pB = findValue( partB , location );
		if( pA >= 0 )
		{
			for( int j = 0 ; (unsigned) j < partB.size() ; j++ )
			{
				if( partB[j] >= 0 ) value = value + matrix[ partA[pA] - 1 ][ partB[j] - 1];
			}
			for( int j = 0 ; (unsigned) j < partA.size() ; j++ )
			{
				if( partA[j] >= 0 )value = value - matrix[ partA[pA] - 1 ][ partA[j] - 1];
			}
		}
		else if( pB>= 0 )
		{
			for( int j = 0 ; (unsigned) j < partA.size() ; j++ )
			{
				if( partA[j] >= 0 ) value = value + matrix[ partB[pB] - 1 ][ partA[j] - 1];
			}
			for( int j = 0 ; (unsigned) j < partB.size() ; j++ )
			{
				if( partB[j] >= 0 ) value = value - matrix[ partB[pB] - 1 ][ partB[j] - 1];
			}
		}
		dValues[i] = value ;
		pA = -1;
		pB = -1;
		value = 0;
	}
}

void KLpartition::updateDValues( vector<int>& partA, vector<int>& partB , int a , int b )
{
	int pos = 0;
	int cia = 0;
	int cib = 0;
	for( int i = 0 ; (unsigned)i < partA.size() ; i++ )
	{
		if( partA[i] > 0 )
		{	
			pos = partA[i] - 1;
			cia = matrix[pos][ a - 1 ];
			cib = 0;
			if( b > 0 ) cib = matrix[pos][ b - 1 ];
			dValues[pos] = dValues[pos] + ( 2 * cia ) - ( 2 * cib );
		}
	}
	for( int j = 0 ; (unsigned)j < partB.size() ; j++ )
	{
		if( partB[j] > 0 )
		{
			pos = partB[j] - 1;
			cia = 0;
			if( a > 0 ) cia = matrix[pos][ a - 1 ];
			cib = matrix[pos][ b - 1 ];
			dValues[pos] = dValues[pos] + ( 2 * cib ) - ( 2 * cia );
		}
	}
}
/*	Author:	Matthew Branstetter
 *	Title:	lastVertex.h
 *	Date:	11/21/2013
 */

#include <KLpartition.h>
 
int KLpartition::lastVertex( vector<int> &partA , vector<int> &partB )
{			
	int a = partA[0];
	int b = partB[0];
	int c = 0;
	int d = 0;
	int cab = 0;
	int value = 0;
	if( a < 0 ) 
	{
		c = 0;
		d = dValues[ b - 1 ];
	}	
	else if( b < 0 )
	{
		c = dValues[ a - 1 ];
		d = 0;
	}
	else 
	{
		c = dValues[ a - 1 ];
		d = dValues[ b - 1 ];
		cab = matrix[ a - 1 ][ b - 1 ];
	}
	value = c + d - ( 2 * cab );
	return value;
}
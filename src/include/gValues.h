/*	Author:	Matthew Branstetter
 *	Title:	gValues.h
 *	Date:	11/21/2013
 */

#include <KLpartition.h>
 
void KLpartition::getGValues( vector<int>& partA, vector<int>& partB ) 
{
	gValues.clear();
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int cab = 0;
	node temp;
	if( unevenA == true ) partA.pop_back();
	if( unevenB == true ) partB.pop_back();
	int value = 0;
	for( int i = 0 ; (unsigned)i < partA.size() ; i++ )
	{
		a = partA[i];
		c = dValues[ a - 1];
		for( int j = 0 ; (unsigned)j < partB.size() ; j++ )
		{
			b = partB[j];
			d = dValues[ b - 1];
			cab = matrix[ a - 1 ][ b - 1 ];
			value = c + d - ( 2 * cab );
			temp.gain = value;
			temp.a = a;
			temp.b = b;
			gValues.push_back( temp );
		}
	}
	if( unevenA == true ) partA.push_back( -1 );
	if( unevenB == true ) partB.push_back( -1 );
}
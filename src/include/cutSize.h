/*	Author:	Matthew Branstetter
 *	Title:	cutSize.h
 *	Date:	11/21/2013
 */

#include <KLpartition.h>
 
int KLpartition::cutSize( vector<int>& partA, vector<int>& partB )
{
	int g = 0;
	for( int i = 0 ; (unsigned)i < partA.size() ; i++)
	{
		for( int j = 0 ; (unsigned)j < partB.size() ; j++)
		{
			if( partA[i] > 0 )
			{
				if( matrix[ partA[i] - 1 ][ partB[j] - 1 ] == 1) g++;
			}
		}
	}
	return g;
}
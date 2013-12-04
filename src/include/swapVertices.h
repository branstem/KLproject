/*	Author:	Matthew Branstetter
 *	Title:	swapVertices.h
 *	Date:	11/21/2013
 */

#include <KLpartition.h>
 
void KLpartition::swapVertices( vector<int>& partA, vector<int>& partB, int a, int b)
{ 
	int c = findValue( partA , a );
	int d = findValue( partB , b );
	partA[c] = b;
	partB[d] = a;
	sort( partA.begin(), partA.end() );
	sort( partB.begin(), partB.end() );
	if( partA[0] == -1) 
	{
		partA.erase( partA.begin() );
		partA.push_back( -1 );
		unevenA = true;
		unevenB = false;
	}
	if( partB[0] == -1) 
	{
		partB.erase( partB.begin() );
		partB.push_back( -1 );
		unevenB = true;
		unevenA = false;
	}
}
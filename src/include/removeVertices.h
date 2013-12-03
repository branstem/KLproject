/*	Author:	Matthew Branstetter
 *	Title:	removeVertices.h
 *	Date:	11/21/2013
 */

void KLpartition::removeVertices( vector<int>& partA, vector<int>& partB, int a, int b )
{
	int pA = 0;
	int pB = 0;
	pA = findValue( partA , a );
	pB = findValue( partB , b );
	if( partA.size() > 1 ) partA.erase( partA.begin() + pA );
	else partA.clear();
	if( partB.size() > 1 )partB.erase( partB.begin() + pB );
	else partB.clear();
}
/*	Author:	Matthew Branstetter
 *	Title:	initPartition.h
 *	Date:	11/21/2013
 */

void KLpartition::initPartition()
{
	int start = numVertices + 1;
	vector<int> partA( numVertices , 0 );
	vector<int> partB( numVertices , 0 );
	if( unevenA == true) start--;
	for( int i = 0 ; i < numVertices ; i++)
	{
		partA[i] = i + 1;
		partB[i] = i + start;
	}
	if( unevenA == true ) partA[ numVertices - 1 ] = -1;
	A.push_back( partA );
	B.push_back( partB );
	
}
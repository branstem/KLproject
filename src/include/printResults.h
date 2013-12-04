/*	Author:	Matthew Branstetter
 *	Title:	printResults.h
 *	Date:	11/21/2013
 */
 
#include <KLpartition.h>

void KLpartition::printResults()
{
	int best = 0;
	int g = 0;
	for( int i = 0 ; (unsigned) i < A.size() ; i++ )
	{
		g = cutSize( A[i], B[i] ); 
		printIteration( i + 1 , g , A[i] , B[i] );
	}
	best = A.size() - 2;
	printFinal( A[best] , B[best] );
}

void KLpartition::printPartition( vector<int>& part )
{
	sort( part.begin(), part.end() );
	if( part[0] == -1) part.erase( part.begin() );
	cout << '{';
	for(int i = 0 ; (unsigned)i < part.size() ; i++)
	{
		cout << part[i];
		if( (unsigned)i == part.size() - 1 ) cout << '}';
		else cout << ',';
	}
}

void KLpartition::printIteration( int a, int b, vector<int>& partA, vector<int>& partB )
{
	cout << endl;
	cout << "a. Iteration number: " << a << endl;
	cout << "b. Partition 1:" << ' ';
	printPartition(partA);
	cout << endl;
	cout << "c. Partition 2:" << ' ';
	printPartition(partB);
	cout << endl;
	cout << "Cost of the partition: " << b << endl;
}

void KLpartition::printFinal( vector<int>& partA, vector<int>& partB )
{
	int b = cutSize( partA , partB );
	cout << endl;
	cout << "Final Partition 1:" << ' ';
	printPartition(partA);
	cout << endl;
	cout << "Final Partition 2:" << ' ';
	printPartition(partB);
	cout << endl;
	cout << "Cost of the Final partitions: " << b << endl << endl;
}
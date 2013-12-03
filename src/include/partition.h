/*	Author:	Matthew Branstetter
 *	Title:	partition.h
 *	Date:	11/21/2013
 */

void KLpartition::partition()
{
	int location = 0;
	int maxGain = 0;
	int maxK = 0;
	int swapA = 0;
	int swapB = 0;
	int total = 0;
	node temp;
	temp.gain = 0;
	temp.a = 0;
	temp.b = 0;
	vector<int> partA;
	vector<int> partB;
	initPartition();
	while( repeat == true ) 
	{
		partA = A[location];
		partB = B[location];
		getDValues( partA , partB );
		for( int i = 0 ; i < numVertices - 1 ; i++ )
		{	
			getGValues( partA , partB );
			maxGain = maxgValue();
			temp = gValues[maxGain];
			total = total + temp.gain;
			temp.gain = total;
			G.push_back(temp);
			removeVertices( partA , partB , temp.a , temp.b );
			updateDValues( partA , partB , temp.a , temp.b );
			temp.a = 0;
			temp.b = 0;
			temp.gain = 0;
		}
		temp.gain = lastVertex( partA , partB );
		total = total + temp.gain;
		temp.gain = total;
		temp.a = partA[0];
		temp.b = partB[0];
		G.push_back(temp);
		maxK = maxG();
		swapA = G[maxK].a;
		swapB = G[maxK].b;
		partA.clear();
		partB.clear();
		partA = A[location];
		partB = B[location];
		swapVertices( partA, partB, swapA , swapB );
		A.push_back( partA );
		B.push_back( partB );
		location++;
		if( G[maxK].gain < 1 ) repeat = false;
		G.clear();
		total = 0;
	}
	G.clear();
	dValues.clear();
	gValues.clear();
	partA.clear();
	partB.clear();
}
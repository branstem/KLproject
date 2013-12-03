/*	Author:	Matthew Branstetter
 *	Title:	KLpartition.h
 *	Date:	11/21/2013
 *
 *	Kernighan-Lin Algorithm:
 *
 *	Step 1:
 *		Create initial Partitions {A, B} such that A and B 
 *		are equal-sized subsets of V with no overlap and their 
 *		union covering all of V.
 *
 *	Step 2:
 *		Compute D values for all vertices.
 *			Formula: 	( Di = Ei - Ii )
 *		Set iteration to 1.
 *		Copy all of A into A', A' = A.
 *		Copy all of B into B', B' = B.
 *
 *	Step 3:
 *		Compute gi values.  
 *			Formula:	( gi = Dai + Dbi - 2caibi )
 *		Choose ai from A' and bi from B' which represents the 
 *		maximum calculated gi.
 *		Add pair (ai, bi) and corresponding gain to que.
 *		Remove ai from A' and bi from B'.
 *
 *	Step 4:
 *		If A' and B' are not empty, update Di values for
 *		all vertices in A' and B'.
 *		Increment Iteration.
 *		Goto Step 3. 
 *		Else Goto Step 5.
 *
 *	Step 5:
 *		Find k to maximize the partial sum of gi from i to k in the queue.
 *		If G > 0 then swap corresponding 'a' value from partition A to 
 *		partition B, and corresponding 'b' value from partition B to
 *		partition A. 
 *		Goto Step 2.
 *		Else Stop.
 */
 
#include <partition.h>
#include <dValues.h>
#include <gValues.h>
#include <initPartition.h>
#include <removeVertices.h>
#include <cutSize.h>
#include <findValue.h>
#include <swapVertices.h>
#include <max.h>
#include <lastVertex.h>

struct node
{
	int gain;
	int a;
	int b;
};

class KLpartition{
	private:
		int	numVertices;				//	Number of vertices (n) per partition
		bool unevenA;					//	Odd number of vertices Flag Partition 1
		bool unevenB;					//	Odd number of vertices Flag Partition 2
		bool repeat;					//	Continue to partition vertices Flag
		vector<vector<int> > matrix;	//	Adjacency Matrix
		vector<vector<int> > A;			//	Matrix with each Partition 1 array
		vector<vector<int> > B;			//	Matrix with each Partition 2 array
		vector<int> dValues;			//	Array to store D values
		vector<node> gValues;			//	Array to store gain values
		vector<node> G;				//	Array to store G values for each k (swap step)
		
		void initPartition();
		void printPartition( vector<int>& part );
		void printIteration( int a, int b, vector<int>& partA, vector<int>& partB );
		void printFinal( vector<int>& partA, vector<int>& partB );
		void getDValues( vector<int>& partA, vector<int>& partB );
		void updateDValues( vector<int>& partA, vector<int>& partB , int a , int b );
		void getGValues( vector<int>& partA, vector<int>& partB );
		void removeVertices( vector<int>& partA, vector<int>& partB, int a, int b );
		void swapVertices( vector<int>& partA, vector<int>& partB, int a, int b );
		int cutSize( vector<int>& partA, vector<int>& partB );
		int maxG();
		int maxgValue();
		int findValue( vector<int>& part , int a );
		int lastVertex( vector<int> &partA , vector<int> &partB );
		
	public:
		KLpartition( int a, vector<vector<int> >& adjacencyMatrix );
		void partition();
		void printResults();
};

KLpartition::KLpartition( int a, vector<vector<int> >& adjacencyMatrix )
{
	numVertices = a/2;
	unevenA = false;
	unevenB = false;
	repeat = true;
	if( a % 2 == 1)
	{
		numVertices++;
		unevenA = true;
	}
	matrix.resize( a , vector<int>( a , 0 ));
	matrix = adjacencyMatrix;
	dValues.resize( a , 0 );
}

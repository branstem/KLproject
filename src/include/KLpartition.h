/*	Author:	Matthew Branstetter
 *	Title:	KLpartition.h
 *	Date:	11/21/2013
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


struct kSwap
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
		vector<kSwap> gValues;			//	Array to store gain values
		vector<kSwap> G;				//	Array to store G values for each k (swap step)
		
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


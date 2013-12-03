/*	Author:	Matthew Branstetter
 *	Title:	project.cpp
 *	Date:	11/21/2013
 *
 *	Description:	This project demonstrates the Kernighan-Lin
 *	algorithm to partition the set V of vertices into {A,B} 
 * 	partitions.  
 *
 *	Kernighan-Lin Algorithm:
 *
 * 	Step 1:
 *	Open text file and read in vertices and edges to Adjacency
 *	Matrix. 
 *	Create initial Partitions {A, B} such that A and B 
 *	are equal-sized subsets of V with no overlap and their 
 *	union covering all of V.
 *
 *	Step 2
 * 	Compute D values for all vertices.
 *	Formula: 	( Di = Ei - Ii )
 *	Iteration = 1;
 *	A' = A;
 *	B' = B;
 *
 *	Step 3
 *	Compute gi values.  
 *	Formula:	( gi = Dai + Dbi - 2caibi )
 *	Choose ai from A' and bi from B' which represents the 
 *	maximum calculated gi.
 *	Add pair (ai, bi) and corresponding gain to que.
 *	Remove ai from A' and bi from B'
 *
 *	Step 4
 *	If A' and B' are not empty, update Di values for
 *	all vertices in A' and B'.
 *	Increment Iteration.
 * 	Goto Step 3. 
 *	Else Goto Step 5.
 *
 *	Step 5
 *	Find k to maximize the partial sum of gi from i to k in the queue.
 *	If G > 0 then swap corresponding 'a' value from partition A to 
 *	partition B. Then swap corresponding 'b' value from partition B to
 *	partition A. 
 *	Goto Step 2
 *  Else display iterations and corresponding {A,B} partitions including
 *	cost. 
 */
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

//	Function reads in a text file to an adjacency matrix
void getMatrix(ifstream& inF, vector<vector<int> >& matrix, int num);

//	Node to store k step gain and corresponding X and Y values.
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

int main(int argc, char * const argv[])
{
	//	Store number of nodes (2n) from file in variable
	int	numNodes;
	//	Use default filename
	const char* filename;
	//	If user provided file name
	if(argc > 1)
		filename = argv[1];
	//	If not, use default file name
	else
		filename = "kl.txt";
	//	Try to open file with filename	
	ifstream inFile(filename);
	//	File open error check
	if(!inFile.is_open())
	{
       //	Notify user file not open and close program
		cout << "Unable to open file. \nProgram terminating...\n";
		return 0;
	}
	//	File is open
	else
	{
		//	Get number of nodes (2n) from text file
		string buffer;
		const char * buffer2;
		getline(inFile, buffer);
		buffer2 = buffer.c_str(); 
		numNodes = atoi(buffer2);
		//	Create adjacency matrix
		vector<int> line(numNodes,0);
		vector<vector<int> > adjMatrix(numNodes, line);
		//	Fill adjacency matrix with appropriate values
		getMatrix(inFile,adjMatrix,numNodes);
		//	Create Initial Partition 
		KLpartition kl(numNodes, adjMatrix);
		//	Find the best Partition
		kl.partition();
		//	Print Results of KL algorithm
		kl.printResults();
	}
	//	Close open text file
	inFile.close();
	//	Close program
	fclose( stdin );
	fclose( stdout );
	fclose( stderr );
	return(0);
}

void getMatrix(ifstream& inF, vector<vector<int> >& matrix, int num)
{
	string buffer;
	string location;
	const char* buffer2;
	int nodePos;
	int lineNum = 0;
	while(getline(inF, buffer))
	{
		stringstream line(buffer);
		string location;
		getline(line,location,',');
		while(getline(line,location,','))
		{
			buffer2 = location.c_str(); 
			nodePos = atoi(buffer2) - 1;
			matrix[lineNum][nodePos]++;
		} 
		lineNum++;
	}
}

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

void KLpartition::getDValues( vector<int>& partA, vector<int>& partB ) 
{
	int location = 0;
	int value = 0;
	int pA = -1;
	int pB = -1;
	if( unevenA == true ) partA.pop_back();
	if( unevenB == true ) partB.pop_back();
	for( int i = 0 ; (unsigned)i < matrix.size() ; i++)
	{
		location = i + 1;
		pA = findValue( partA , location );
		pB = findValue( partB , location );
		if( pA >= 0 )
		{
			for( int j = 0 ; (unsigned) j < partB.size() ; j++ )
			{
				value = value + matrix[ partA[pA] - 1 ][ partB[j] - 1];
			}
			for( int j = 0 ; (unsigned) j < partA.size() ; j++ )
			{
				value = value - matrix[ partA[pA] - 1 ][ partA[j] - 1];
			}
		}
		else if( pB>= 0 )
		{
			for( int j = 0 ; (unsigned) j < partA.size() ; j++ )
			{
				value = value + matrix[ partB[pB] - 1 ][ partA[j] - 1];
			}
			for( int j = 0 ; (unsigned) j < partB.size() ; j++ )
			{
				value = value - matrix[ partB[pB] - 1 ][ partB[j] - 1];
			}
		}
		dValues[i] = value ;
		pA = -1;
		pB = -1;
		value = 0;
	}
	if( unevenA == true ) partA.push_back( -1 );
	if( unevenB == true ) partB.push_back( -1 );
}

void KLpartition::updateDValues( vector<int>& partA, vector<int>& partB , int a , int b )
{
	int pos = 0;
	int cia = 0;
	int cib = 0;
	for( int i = 0 ; (unsigned)i < partA.size() ; i++ )
	{
		if( partA[i] > 0 )
		{	
			pos = partA[i] - 1;
			cia = matrix[pos][ a - 1 ];
			cib = 0;
			if( b > 0 ) cib = matrix[pos][ b - 1 ];
			dValues[pos] = dValues[pos] + ( 2 * cia ) - ( 2 * cib );
		}
	}
	for( int j = 0 ; (unsigned)j < partB.size() ; j++ )
	{
		if( partB[j] > 0 )
		{
			pos = partB[j] - 1;
			cia = 0;
			if( a > 0 ) cia = matrix[pos][ a - 1 ];
			cib = matrix[pos][ b - 1 ];
			dValues[pos] = dValues[pos] + ( 2 * cib ) - ( 2 * cia );
		}
	}
}

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

int KLpartition::maxG()
{
	int max = 0;
	int location = 0;
	for( int i = 0 ; (unsigned)i < G.size() ; i++ )
	{
		if( G[i].gain > max ) 
		{
			max = G[i].gain;
			location = i;
		}
	}
	return location;
}

int KLpartition::maxgValue()
{
	int max = 0;
	int location = 0;
	for( int i = 0 ; (unsigned)i < gValues.size() ; i++ )
	{
		if( i == 0) max = gValues[i].gain;
		else if( gValues[i].gain > max ) 
		{
			max = gValues[i].gain;
			location = i;
		}
	}
	return location;
}

int KLpartition::findValue( vector<int>& part , int a )
{
	int location = -1;
	for( int i = 0 ; (unsigned) i < part.size() ; i++ )
	{
		if( part[i] == a ) return i;
	}
	return location;
}

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

void KLpartition::getGValues( vector<int>& partA, vector<int>& partB ) 
{
	gValues.clear();
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int cab = 0;
	kSwap temp;
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

void KLpartition::partition()
{
	int location = 0;
	int maxGain = 0;
	int maxK = 0;
	int swapA = 0;
	int swapB = 0;
	int total = 0;
	kSwap temp;
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


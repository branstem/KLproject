/*	Author:	Matthew Branstetter
 *	Title:	KLpartition.cpp
 *	Date:	11/21/2013
 */

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "KLpartition.h"

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
	for( int i = 0 ; (unsigned)i < matrix.size() ; i++)
	{
		location = i + 1;
		pA = findValue( partA , location );
		pB = findValue( partB , location );
		if( pA >= 0 )
		{
			for( int j = 0 ; (unsigned) j < partB.size() ; j++ )
			{
					if( partB[j] > 0 ) value = value + matrix[ partA[pA] - 1 ][ partB[j] - 1];
			}
			for( int j = 0 ; (unsigned) j < partA.size() ; j++ )
			{
					if( partA[j] > 0 )value = value - matrix[ partA[pA] - 1 ][ partA[j] - 1];
			}
		}
		else if( pB>= 0 )
		{
			for( int j = 0 ; (unsigned) j < partA.size() ; j++ )
			{
					if( partA[j] > 0 ) value = value + matrix[ partB[pB] - 1 ][ partA[j] - 1];
			}
			for( int j = 0 ; (unsigned) j < partB.size() ; j++ )
			{
					if( partB[j] > 0 ) value = value - matrix[ partB[pB] - 1 ][ partB[j] - 1];
			}
		}
		dValues[i] = value ;
		pA = -1;
		pB = -1;
		value = 0;
	}
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
			if( a > 0 ) cia = matrix[pos][ a - 1 ];
			else cia = 0;
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
			else cia = 0;
			if( b > 0 ) cib = matrix[pos][ b - 1 ];
			else cib = 0;
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
	int max = - 2 * numVertices;
	int location = 0;
	for( int i = 0 ; (unsigned)i < G.size() ; i++ )
	{
		if( i == 0) max = G[i].gain;
		else if( G[i].gain > max )
		{
			max = G[i].gain;
			location = i;
		}
	}
	return location;
}

int KLpartition::maxgValue()
{
	int max = - 2 * numVertices;
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
	node temp;
	int value = 0;
	for( int i = 0 ; (unsigned)i < partA.size() ; i++ )
	{
		a = partA[i];
		if( a > 0 ) c = dValues[ a - 1];
		else c = 0;
		for( int j = 0 ; (unsigned)j < partB.size() ; j++ )
		{
			b = partB[j];
			if( b > 0 ) d = dValues[ b - 1];
			else d = 0;
			if( ( a > 0 ) && ( b > 0 ) ) cab = matrix[ a - 1 ][ b - 1 ];
			else cab = 0;
			value = c + d - ( 2 * cab );
			temp.gain = value;
			temp.a = a;
			temp.b = b;
			gValues.push_back( temp );
		}
	}
}

void KLpartition::partition()
{
	int location = 0;
	int maxGain = 0;
	int maxK = 0;
	int total = 0;
	node temp;
	temp.gain = 0;
	temp.a = 0;
	temp.b = 0;
	vector<int> partA;
	vector<int> partB;
	// Step 1.
	initPartition();
	while( repeat == true )
	{
		partA = A[location];
		partB = B[location];
		// Step 2.
		getDValues( partA , partB );
		while( partA.size() > 1 )
		{        
			// Step 3.
			getGValues( partA , partB );
			maxGain = maxgValue();
			temp = gValues[maxGain];
			total = total + temp.gain;
			temp.gain = total;
			G.push_back(temp);
			removeVertices( partA , partB , temp.a , temp.b );
			// Step 4.
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
		// Step 5.
		maxK = maxG();
		partA.clear();
		partB.clear();
		partA = A[location];
		partB = B[location];
		for( int i = 0 ; i < maxK + 1 ; i++ )
		{
			swapVertices( partA, partB, G[i].a , G[i].b );
		}
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

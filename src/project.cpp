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
#include <KLpartition.h>

using namespace std;

//	Function reads in a text file to an adjacency matrix
void getMatrix(ifstream& inF, vector<vector<int> >& matrix, int num);

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

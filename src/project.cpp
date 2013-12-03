/*	Author:	Matthew Branstetter
 *	Title:	project.cpp
 *	Date:	11/21/2013
 *
 *	Description:	This project demonstrates the Kernighan-Lin
 *	algorithm to partition the set V of vertices into {A,B} 
 * 	partitions. A text file containing the information to 
 *	build the adjacency matrix is opened. A function getMatrix(),
 *	is called to read in information from file and store in 
 *	adjacency matrix. Then the initial partitions are created
 *	and the partitioning algorithm is performed. The results 
 *	of the algorithm are then printed out and the file is
 *	closed. Program then ends.
 * 
 */
 
#include <iostream>
#include <fstream>
#include <sstream>.
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

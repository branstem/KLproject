/*	Author:	Matthew Branstetter
 *	Title:	findValue.h
 *	Date:	11/21/2013
 */

#include <KLpartition.h>
 
int KLpartition::findValue( vector<int>& part , int a )
{
	int location = -1;
	for( int i = 0 ; (unsigned) i < part.size() ; i++ )
	{
		if( part[i] == a ) return i;
	}
	return location;
}
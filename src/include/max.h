/*	Author:	Matthew Branstetter
 *	Title:	max.h
 *	Date:	11/21/2013
 */

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
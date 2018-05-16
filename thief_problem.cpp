/**
 * This file resolves a problem called thief problem.
 *
 * Problem description:
 *  There is a city comprised of a ring houses. A theif can steal from houses, however, two houses
 *  that being neighbour cannot be stolen. How can the thief make best profit.
 *
 * Input:
 *  A list of number each of which specifies the value of a house in the city.
 *
 * Output:
 *  A single number indicate the best profit
 *  A list of the houses which will be stolen so that the theif can make best profit
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * suppose city [N] = {100, 1, 7, 100, 5, 8, 100, 10}
 * 
 * When the theif is stealing, he is going to skip 1 or 2 houses, but not going to skip 3 houses.
 * Because when skipping 3 houses, it's always better to steal the middle house to increase the incomes.
 * 
 * A house cannot be stolen twice. 
 * 
 * find the max value, steal it or 
 */
int * profits = NULL;
int * stolen = NULL;

inline int max( int a, int b ) { return a > b ? a : b; }

int steal_city( int * city, int houses )
{
    if ( houses == 0 )
        return 0;

    if ( houses == 1 )
        return city[ 0 ];
    
    if ( houses == 2 )
        return max( city[ 0 ], city[ 1 ] );

    if ( houses == 3 )
        return max( city[ 0 ], max( city[ 1 ], city[ 2 ] ) );

    // 1 don't contain the first element and contain the last element
    int profit1 = steal_city( &city[1], houses - 2 ) + city[ houses - 1 ];
    
    // 2 contian the first element but not contain the last element
    int profit2 = steal_city( &city[1], houses - 2 ) + city[ 0 ];

    // 3 don't contian both first and last element, which means the second and last second is take in to count
    int profit3 = steal_city( &city[2], houses - 4 ) + city[ 1 ] + city[ houses - 2 ];

    return max( max( profit1, profit2 ), profit3 );
}

int main( int argc, char * argv[] )
{
    int houses = atoi( argv[1] );
    int * city = (int *)malloc( sizeof(int) * houses );
    int * profits = (int *)malloc( sizeof(int) * houses );
    int * stolen = (int *)malloc( sizeof(int) * houses );

    for ( int i = 0; i < houses; ++i )
    {
        profits[ i ] = 0;
        stolen[ i ] = 1;
    }
        
    // initialize the city randomly
    printf( "initialize the city randomly: \n" );
    for ( int i = 0; i < houses; ++i )
    {
        city[i] = rand();
        printf( i == 0 ? "%d" : " %d", city[i] );
    }

    printf( "max profit that the thief can make is %d\n", steal_city( city, houses ) );

    return 0;
}

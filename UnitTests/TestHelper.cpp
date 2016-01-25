#include "TestHelper.h"

#include "Solution.h"
#include "Graph.h"

bool TestHelper::solutionHasUniqueAndCorrectVertices( const Solution& solution )
{
    const std::vector<int> vertexOrder = solution.getVertexOrder();

    std::vector<bool> foundVertices;
    foundVertices.resize( vertexOrder.size() );

    for ( unsigned int i = 0; i < foundVertices.size(); ++i )
        foundVertices[ i ] = false;

    for ( unsigned int i = 0; i < vertexOrder.size(); ++i ) {
        if ( vertexOrder[ i ] < 0 || vertexOrder[ i ] >= (int)vertexOrder.size() || foundVertices[ vertexOrder[ i ] ] )
            return false;
        else
            foundVertices[ vertexOrder[ i ] ] = true;
    }

    return true;
}

bool TestHelper::areSolutionsSame( const Solution& solution1, const Solution& solution2 )
{
    if ( solution1.getVertexOrder().size() != solution2.getVertexOrder().size() )
        return false;

    for ( unsigned int i = 0; i < solution1.getVertexOrder().size(); ++i ) {
        if ( solution1.getVertexOrder()[ i ] != solution2.getVertexOrder()[ i ] )
            return false;
    }

    return true;
}
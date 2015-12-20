#include "Solution.h"

#include <string>
#include <random>
#include <chrono>

std::default_random_engine Solution::randomGenerator = std::default_random_engine( std::chrono::system_clock::now( ).time_since_epoch( ).count( ) );

std::shared_ptr<Solution> Solution::createRandom( int vertexCount )
{
    std::shared_ptr<Solution> solution = std::make_shared<Solution>();

    std::vector<int> vertices;
    vertices.resize( vertexCount );
    for ( int i = 0; i < vertexCount; ++i )
        vertices[ i ] = i;

    solution->vertexOrder.resize( vertexCount );

    std::uniform_int_distribution<int> distribution( 0, vertexCount );

    for ( int i = 0; i < vertexCount; ++i ) {
        const int randomIndex = distribution( randomGenerator ) % vertices.size( );

        solution->vertexOrder[ i ] = vertices[ randomIndex ];

        vertices.erase( vertices.begin() + randomIndex );
    }

    return solution;
}

std::shared_ptr<Solution> Solution::reproduce( const Solution& solution1, const Solution& solution2 )
{
    //#TODO: Mix two solution together.
}

void Solution::mutate(int k)
{
    //#TODO: Modify this solution with k-interchange (k as param).
}

Solution::Solution()
{}


Solution::~Solution()
{}

const std::vector<int>& Solution::getVertexOrder() const
{
    return vertexOrder;
}

std::string Solution::toString( ) const
{
    std::string text;

    text += "{";
    for ( int i = 0; i < (int)vertexOrder.size(); ++i ) {
        text += ( i > 0 ? ", " : "" ) + std::to_string( vertexOrder[ i ] );
    }
    text += "}";

    return text;
}

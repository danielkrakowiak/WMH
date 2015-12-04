#include "Graph.h"

#include "TextFile.h"
#include "Solution.h"

std::shared_ptr<Graph> Graph::loadFromFile( std::string path )
{
    std::shared_ptr< std::vector<char> > fileData = TextFile::load( path );
    std::vector<char>::const_iterator it = fileData->begin();

    std::shared_ptr<Graph> graph = std::make_shared<Graph>();

    graph->vertexCount = TextFile::parseInt( it, fileData->end( ) );
    TextFile::skipSpacesAndNewlines( it, fileData->end( ) );

    if ( graph->vertexCount < 2 )
        throw std::exception( "Graph::loadFromFile - vertex count has to be higher than 1." );

    const int weightsCount = graph->vertexCount * graph->vertexCount;
    graph->weightsMatrix.resize( weightsCount );
    
    int weightIndex = 0;

    while ( it != fileData->end( ) ) {
        graph->weightsMatrix[ weightIndex ] = TextFile::parseFloat( it, fileData->end( ) );

        ++weightIndex;
        TextFile::skipSpacesAndNewlines( it, fileData->end( ) );
    }

    if ( weightIndex < weightsCount )
        throw std::exception( "Graph::loadFromFile - too few weights for the given number of vertices." );

    return graph;
}

Graph::Graph() :
    vertexCount( 0 )
{}


Graph::~Graph()
{
}

float Graph::getWeight( int vertexFrom, int vertexTo ) const
{
    if ( vertexFrom < 0 || vertexFrom >= vertexCount || vertexTo < 0 || vertexTo >= vertexCount )
        throw std::exception( "Graph::getWeight - incorrect vertex index passed." );

    return weightsMatrix.at( vertexFrom * vertexCount + vertexTo );
}

int Graph::getVertexCount() const
{
    return vertexCount;
}

float Graph::evaluateSolution( const Solution& solution ) const
{
    if ( solution.getVertexOrder().size( ) != vertexCount )
        throw std::exception( "Graph::evaluateSolution - path is incomplete." );

    float eval = 0.0f;

    for ( int i = 0; i < vertexCount - 1; ++i ) {
        eval += getWeight( solution.getVertexOrder( )[ i ], solution.getVertexOrder( )[ i + 1 ] );
    }

    return eval;
}

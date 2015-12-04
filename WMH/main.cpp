#include "Graph.h"
#include "Solution.h"

#include <Windows.h>

void main()
{
    try {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "Graphs/test1.txt" );

        for ( int i = 0; i < 100; ++i ) {
            std::shared_ptr<Solution> solution = Solution::createRandom( graph->getVertexCount() );
            const float eval = graph->evaluateSolution( *solution );

            OutputDebugString( (std::to_string( eval ) + " " + solution->toString() + "\n").c_str() );
        }

    } catch ( std::exception& e ) {
        OutputDebugString( (e.what() + std::string( "\n" )).c_str() );
    }
}
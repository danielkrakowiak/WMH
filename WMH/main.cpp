#include "Graph.h"
#include "Solution.h"

#include <Windows.h>

const int generationSize = 100;
const int maxGenerationCount = 100000;

void main()
{
    try {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "Graphs/test1.txt" );

        std::vector<std::shared_ptr<Solution>> currentGeneration;
        currentGeneration.reserve( generationSize );

        float                     bestEval = 99999.0f;
        std::shared_ptr<Solution> bestSolution = nullptr;
        int                       currentGenerationIndex = 0;

        while ( currentGenerationIndex < maxGenerationCount ) {
            currentGeneration.clear();

            float                     semiBestEval = 99999.0f;
            std::shared_ptr<Solution> semiBestSolution = nullptr;

            // Create initial generation.
            for ( int i = 0; i < generationSize; ++i )
                currentGeneration.push_back( Solution::createRandom( graph->getVertexCount() ) );

            // Evaluate current generation.
            for ( int i = 0; i < generationSize; ++i ) {
                const float eval = graph->evaluateSolution( *currentGeneration[ i ] );
                if ( eval < bestEval ) {
                    bestEval = eval;
                    bestSolution = currentGeneration[ i ];
                }

                if ( eval < semiBestEval ) {
                    semiBestEval = eval;
                    semiBestSolution = currentGeneration[ i ];
                }
            }

            OutputDebugString( (std::to_string( currentGenerationIndex ) + ":" + std::to_string( semiBestEval ) + " " + semiBestSolution->toString( ) + "\n").c_str( ) );
        
            ++currentGenerationIndex;
        }

        OutputDebugString( (std::to_string( currentGenerationIndex ) + ":" + std::to_string( bestEval ) + " " + bestSolution->toString( ) + "\n").c_str( ) );

    } catch ( std::exception& e ) {
        OutputDebugString( (e.what() + std::string( "\n" )).c_str() );
    }
}
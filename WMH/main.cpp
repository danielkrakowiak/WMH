#include "Graph.h"
#include "Solution.h"

#include <random>
#include <chrono>
#include <Windows.h>

const int baseGenerationSize = 3000;
const int tempGenerationSize = baseGenerationSize * 2;
const int maxGenerationCount = 8000;

int findIndex( const std::vector<float>& values, float targetValue );

void main()
{
    const int   mutateVertexCount = 5;
    const float crossProbability = 0.7f;
    const float mutationProbability = 0.05f;

    try {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "Graphs/ft70 (38673).txt" );

        std::default_random_engine            randomGenerator = std::default_random_engine( std::chrono::system_clock::now( ).time_since_epoch( ).count( ) );
        std::uniform_real_distribution<float> realDistribution( 0.0f, 1.0f );
        std::uniform_int_distribution<int>    intDistribution( 0, 100000 );

        std::vector<std::shared_ptr<Solution>> baseGeneration, tempGeneration, childGeneration;
        baseGeneration.reserve( baseGenerationSize );
        tempGeneration.reserve( tempGenerationSize );

        std::vector<float> rouletteValues;
        rouletteValues.resize( baseGenerationSize );

        // Create initial generation.
        while ( baseGeneration.size() < baseGenerationSize )
            baseGeneration.push_back( Solution::createRandom( *graph ) );

        float                     bestEval = FLT_MAX, generationBestEval = FLT_MAX;
        std::shared_ptr<Solution> bestSolution, generationBestSolution;
        int                       currentGenerationIndex = 0;

        while ( currentGenerationIndex < maxGenerationCount ) 
        {
            generationBestEval     = FLT_MAX;
            generationBestSolution = nullptr;
            tempGeneration.clear();

            { // Create temporary generation - roulette wheel selection.
                float totalEval = 0.0f, worstEval = 0.0f;
                for ( std::shared_ptr<Solution>& solution : baseGeneration ) {
                    totalEval += solution->getEvaluation();
                    worstEval = max( worstEval, solution->getEvaluation() );
                }
                OutputDebugString( ("\nBase gen - Av. eval: " + std::to_string( totalEval / (float)baseGenerationSize )).c_str() );

                // Calculate values on the "roulette wheel" for each solution.
                rouletteValues[ 0 ] = (worstEval - baseGeneration[ 0 ]->getEvaluation() + 1.0f) / (totalEval + 1.0f);
                for ( int i = 1; i < baseGenerationSize; ++i )
                    rouletteValues[ i ] = rouletteValues[ i - 1 ] + ((worstEval - baseGeneration[ i ]->getEvaluation() + 1.0f) / (totalEval + 1.0f));

                // Select solutions from base to temporary generation.
                float totalEval2 = 0.0f; // For debug.
                while ( tempGeneration.size() < tempGenerationSize )
                {
                    float random = fmodf( realDistribution( randomGenerator ), rouletteValues.back() );
                    int index = findIndex( rouletteValues, random );
                    tempGeneration.push_back( baseGeneration[ index ] );
                    totalEval2 += baseGeneration[ index ]->getEvaluation();
                }
                OutputDebugString( ("\nTemp gen - Av. eval: " + std::to_string( totalEval2 / (float)tempGenerationSize )).c_str() );
            }

            baseGeneration.clear();

            { // Reproduce solutions from the temporary generation.
                while ( baseGeneration.size() < baseGenerationSize )
                {
                    // Select first parent.
                    int index1 = intDistribution( randomGenerator ) % tempGeneration.size();
                    std::shared_ptr<Solution> solution1 = tempGeneration[ index1 ];
                    tempGeneration.erase( tempGeneration.begin() + index1 );

                    // Select second parent.
                    int index2 = intDistribution( randomGenerator ) % tempGeneration.size();
                    std::shared_ptr<Solution> solution2 = tempGeneration[ index2 ];
                    tempGeneration.erase( tempGeneration.begin() + index2 );

                    float random = realDistribution( randomGenerator );
                    if ( random <= crossProbability ) {
                        // Cross solutions.
                        std::shared_ptr<Solution> childSolution = Solution::reproduce( *solution1, *solution2, *graph );
                        baseGeneration.push_back( childSolution );
                    } else {
                        // Select the better of the parents.
                        if ( solution1->getEvaluation() <= solution2->getEvaluation() )
                            baseGeneration.push_back( solution1 );
                        else
                            baseGeneration.push_back( solution2 );
                    }
                }
            }

            {  // Mutate solutions.
                for ( std::shared_ptr<Solution>& solution : baseGeneration )
                {
                    float random = realDistribution( randomGenerator );
                    if ( random <= mutationProbability )
                        solution->mutate( mutateVertexCount, *graph );
                }
            }


            // Evaluate current generation.
            for ( std::shared_ptr<Solution>& solution : baseGeneration ) {
                if ( solution->getEvaluation() < bestEval ) {
                    bestEval = solution->getEvaluation();
                    bestSolution = solution;
                }

                if ( solution->getEvaluation() < generationBestEval ) {
                    generationBestEval = solution->getEvaluation();
                    generationBestSolution = solution;
                }
            }

            OutputDebugString( ("\n" + std::to_string( currentGenerationIndex ) + ":" + std::to_string( generationBestEval ) + " " + generationBestSolution->toString( ) + "\n").c_str( ) );
        
            ++currentGenerationIndex;
        }

        OutputDebugString( ("\n\n Final result: " + std::to_string( currentGenerationIndex ) + ":" + std::to_string( bestEval ) + " " + bestSolution->toString( ) + "\n").c_str( ) );

    } catch ( std::exception& e ) {
        OutputDebugString( (e.what() + std::string( "\n" )).c_str() );
    }
}

int findIndex( const std::vector<float>& values, float targetValue )
{
    //std::string str = "";
    //for ( float value : values )
    //    str += std::to_string( value ) + ", ";
    //
    //str += "\n\ntarget = " + std::to_string( targetValue ) + "\n\n";

    int minIndex = 0;
    int maxIndex = values.size() - 1;

    while ( minIndex != maxIndex )
    {
        //str += "min_index = " + std::to_string( minIndex ) + " (" + std::to_string( values[ minIndex ] ) + "), ";
        //str += "max_index = " + std::to_string( maxIndex ) + " (" + std::to_string( values[ maxIndex ] ) + ") \n";

        const int middleIndex1 = (minIndex + maxIndex) / 2;
        const int middleIndex2 = min(middleIndex1 + 1, maxIndex);
        if ( targetValue < values[ middleIndex1 ])
            maxIndex = middleIndex1;
        else if ( targetValue > values[ middleIndex2 ] )
            minIndex = middleIndex2;
        else
        {
            //str += "found: index = " + std::to_string( middleIndex1 ) + ", value = " + std::to_string( values[ middleIndex1 ] ) + "\n";
            //OutputDebugString( str.c_str() );
            return middleIndex1;
        }
    }

    //str += "found: index = " + std::to_string( minIndex ) + ", value = " + std::to_string( values[ minIndex ] ) + "\n";
    //OutputDebugString( str.c_str() );
    return minIndex;
}
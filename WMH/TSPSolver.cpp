#include "TSPSolver.h"

#include <algorithm>
#include <random>
#include <chrono>

#include "Graph.h"
#include "Solution.h"

std::shared_ptr<TSPSolver::Result> TSPSolver::solve( const Graph& graph, const unsigned int baseGenerationSize, const unsigned int maxGenerationCount,
                                                     const int mutateVertexCount, const float crossProbability, const float mutationProbability )
{
    const unsigned int tempGenerationSize = baseGenerationSize * 2;

    std::shared_ptr<Result> result = std::make_shared<Result>();

    try {
        std::default_random_engine            randomGenerator = std::default_random_engine( std::chrono::system_clock::now().time_since_epoch().count() );
        std::uniform_real_distribution<float> realDistribution( 0.0f, 1.0f );
        std::uniform_int_distribution<int>    intDistribution( 0, 100000 );

        std::vector<std::shared_ptr<Solution>> baseGeneration, tempGeneration, childGeneration;
        baseGeneration.reserve( baseGenerationSize );
        tempGeneration.reserve( tempGenerationSize );

        std::vector<float> rouletteValues;
        rouletteValues.resize( baseGenerationSize );

        // Create initial generation.
        while ( baseGeneration.size() < baseGenerationSize )
            baseGeneration.push_back( Solution::createRandom( graph ) );

        float                     bestEval = FLT_MAX, generationBestEval = FLT_MAX, generationTotalEval = 0.0f;
        std::shared_ptr<Solution> bestSolution, generationBestSolution;
        unsigned int              currentGenerationIndex = 0;

        while ( currentGenerationIndex < maxGenerationCount ) {
            generationBestEval = FLT_MAX;
            generationBestSolution = nullptr;
            generationTotalEval = 0.0f;
            tempGeneration.clear();

            { // Create temporary generation - roulette wheel selection.
                float worstEval = 0.0f;
                for ( std::shared_ptr<Solution>& solution : baseGeneration ) {
                    generationTotalEval += solution->getEvaluation();
                    worstEval = std::max( worstEval, solution->getEvaluation() );
                }
                //OutputDebugString( ("\nBase gen - Av. eval: " + std::to_string( totalEval / (float)baseGenerationSize )).c_str() );

                // Calculate values on the "roulette wheel" for each solution.
                rouletteValues[ 0 ] = (worstEval - baseGeneration[ 0 ]->getEvaluation() + 1.0f) / (generationTotalEval + 1.0f);
                for ( unsigned int i = 1; i < baseGenerationSize; ++i )
                    rouletteValues[ i ] = rouletteValues[ i - 1 ] + ((worstEval - baseGeneration[ i ]->getEvaluation() + 1.0f) / (generationTotalEval + 1.0f));

                // Select solutions from base to temporary generation.
                while ( tempGeneration.size() < tempGenerationSize ) {
                    float random = fmodf( realDistribution( randomGenerator ), rouletteValues.back() );
                    int index = findIndex( rouletteValues, random );
                    tempGeneration.push_back( baseGeneration[ index ] );
                }
            }

            baseGeneration.clear();

            { // Reproduce solutions from the temporary generation.
                while ( baseGeneration.size() < baseGenerationSize ) {
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
                        std::shared_ptr<Solution> childSolution = Solution::reproduce( *solution1, *solution2, graph );
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
                for ( std::shared_ptr<Solution>& solution : baseGeneration ) {
                    float random = realDistribution( randomGenerator );
                    if ( random <= mutationProbability )
                        solution->mutate( mutateVertexCount, graph );
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

            GenerationStats stat;
            stat.bestEval    = generationBestEval;
            stat.avarageEval = generationTotalEval / (float)baseGenerationSize;
            result->generationStats.push_back( stat );
            //OutputDebugString( ("\n" + std::to_string( currentGenerationIndex ) + ":" + std::to_string( generationBestEval ) + " " + generationBestSolution->toString() + "\n").c_str() );

            ++currentGenerationIndex;
        }

        //OutputDebugString( ("\n\n Final result: " + std::to_string( currentGenerationIndex ) + ":" + std::to_string( bestEval ) + " " + bestSolution->toString() + "\n").c_str() );
        result->bestSolution = *bestSolution;
        return result;

    } catch ( ... ) {
        throw std::exception( "TSPSolver::solve - Error occurred." );
    }
}

int TSPSolver::findIndex( const std::vector<float>& values, float targetValue )
{
    int minIndex = 0;
    int maxIndex = values.size() - 1;

    while ( minIndex != maxIndex ) {

        const int middleIndex1 = (minIndex + maxIndex) / 2;
        const int middleIndex2 = std::min( middleIndex1 + 1, maxIndex );
        if ( targetValue < values[ middleIndex1 ] )
            maxIndex = middleIndex1;
        else if ( targetValue > values[ middleIndex2 ] )
            minIndex = middleIndex2;
        else {
            return middleIndex1;
        }
    }

    return minIndex;
}
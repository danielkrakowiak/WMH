#pragma once

#include "Solution.h"

class TSPSolver
{
    public:

    struct GenerationStats
    {
        float bestEval;
        float avarageEval;
    };

    struct Result
    {
        Solution bestSolution;
        std::vector<GenerationStats> generationStats;
    };

    static std::shared_ptr<Result> solve( const Graph& graph, const unsigned int baseGenerationSize, const unsigned int maxGenerationCount, 
                         const int mutateVertexCount, const float crossProbability, const float mutationProbability );

    private:

    static int TSPSolver::findIndex( const std::vector<float>& values, float targetValue );
};


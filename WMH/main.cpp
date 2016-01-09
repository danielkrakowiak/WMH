#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>

#include "Graph.h"
#include "Solution.h"
#include "TSPSolver.h"


void main()
{
    const int   baseGenerationSize  = 3000;
    const int   tempGenerationSize  = baseGenerationSize * 2;
    const int   maxGenerationCount  = 5;//8000;
    const int   mutateVertexCount   = 5;
    const float crossProbability    = 0.7f;
    const float mutationProbability = 0.05f;

   std::string graphName = "ft70 (38673)";

    std::shared_ptr<Graph> graph = Graph::loadFromFile( "Graphs/" + graphName + ".txt" );

    std::string path = "Output/";
    std::string filename = 
        graphName + " " +
        std::to_string( baseGenerationSize ) + " " + 
        std::to_string( mutateVertexCount ) + " " +
        std::to_string( crossProbability ) + " " +
        std::to_string( mutationProbability ) + ".txt";

    std::ofstream file;
    file.open( (path + filename).c_str() );
    bool ok = file.good();

    try {
        file << "Params: ----------------------------- \n";
        file << ("\n  baseGenerationSize: " + std::to_string( baseGenerationSize )).c_str();
        file << ("\n  maxGenerationCount: " + std::to_string( baseGenerationSize )).c_str();
        file << ("\n  mutateVertexCount: " + std::to_string( baseGenerationSize )).c_str();
        file << ("\n  crossProbability: " + std::to_string( baseGenerationSize )).c_str();
        file << ("\n  mutationProbability: " + std::to_string( baseGenerationSize )).c_str();

        std::shared_ptr<TSPSolver::Result> result = TSPSolver::solve( *graph, baseGenerationSize, maxGenerationCount, mutateVertexCount, crossProbability, mutationProbability );

        file <<  "\n\nResult: ----------------------------- \n";
        file <<  ("\n  best eval: " + std::to_string( result->bestSolution.getEvaluation() )).c_str();
        file <<  ("\n  best solution: " + result->bestSolution.toString() ).c_str();

        file <<  "\n\nGenerations: ----------------------------- \n";
        for (unsigned int i = 0; i < result->generationStats.size(); ++i)
            file << ("\n     " + std::to_string( i ) + "      :      " +
            std::to_string( result->generationStats[ i ].bestEval ) ).c_str();

    } catch ( std::exception& e ) {
        file << (e.what() + std::string( "\n" )).c_str();
    }

    file.close();
}
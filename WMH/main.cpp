#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <chrono>

#include "Graph.h"
#include "Solution.h"
#include "TSPSolver.h"


void main(int argc, char* argv[])
{
    unsigned int run = 0;
    unsigned int maxGenerationCount     = 1;
    float        maxTime                = 300.0f;
    unsigned int baseGenerationSizeMin  = 1000,  baseGenerationSizeMax  = 3000,   baseGenerationSizeStep  = 500;
    unsigned int mutateVertexCountMin   = 0,     mutateVertexCountMax   = 10,     mutateVertexCountStep   = 2;
    float        crossProbabilityMin    = 0.5f,  crossProbabilityMax    = 0.95f,  crossProbabilityStep    = 0.05f;
    float        mutationProbabilityMin = 0.0f,  mutationProbabilityMax = 0.2f,   mutationProbabilityStep = 0.025f;

    for ( unsigned int i = 1; i + 1 < argc; i += 2 )
    {
        std::string paramName(argv[ i ]);
        std::string paramValue(argv[ i + 1 ]);

        if (paramName.compare("run") == 0)                          run                     = atoi(paramValue.c_str());
        else if (paramName.compare("maxGenerationCount") == 0)      maxGenerationCount      = atoi(paramValue.c_str());
        else if (paramName.compare("maxTime") == 0)                 maxTime                 = atof(paramValue.c_str());
        else if (paramName.compare("baseGenerationSizeMin") == 0)   baseGenerationSizeMin   = atoi(paramValue.c_str());
        else if (paramName.compare("baseGenerationSizeMax") == 0)   baseGenerationSizeMax   = atoi(paramValue.c_str());
        else if (paramName.compare("baseGenerationSizeStep") == 0)  baseGenerationSizeStep  = atoi(paramValue.c_str());
        else if (paramName.compare("mutateVertexCountMin") == 0)    mutateVertexCountMin    = atoi(paramValue.c_str());
        else if (paramName.compare("mutateVertexCountMax") == 0)    mutateVertexCountMax    = atoi(paramValue.c_str());
        else if (paramName.compare("mutateVertexCountStep") == 0)   mutateVertexCountStep   = atoi(paramValue.c_str());
        else if (paramName.compare("crossProbabilityMin") == 0)     crossProbabilityMin     = atof(paramValue.c_str());
        else if (paramName.compare("crossProbabilityMax") == 0)     crossProbabilityMax     = atof(paramValue.c_str());
        else if (paramName.compare("crossProbabilityStep") == 0)    crossProbabilityStep    = atof(paramValue.c_str());
        else if (paramName.compare("mutationProbabilityMin") == 0)  mutationProbabilityMin  = atof(paramValue.c_str());
        else if (paramName.compare("mutationProbabilityMax") == 0)  mutationProbabilityMax  = atof(paramValue.c_str());
        else if (paramName.compare("mutationProbabilityStep") == 0) mutationProbabilityStep = atof(paramValue.c_str());
        else 
        {
            std::cout << "param: " << paramName << " unrecognized.\n";
            return;
        }
    }

    std::string path = "Output/";
    std::ofstream outputFile;
    outputFile.open( path + "output" + std::to_string(run) + ".txt" );

    std::string graphName = "ft70 (38673)";

    std::shared_ptr<Graph> graph = Graph::loadFromFile( "Graphs/" + graphName + ".txt" );

    const unsigned int totalRunCount = 
        ((baseGenerationSizeMax - baseGenerationSizeMin) / baseGenerationSizeStep + 1) *
        ((mutateVertexCountMax - mutateVertexCountMin) / mutateVertexCountStep + 1) *
        (unsigned int)((crossProbabilityMax - crossProbabilityMin) / crossProbabilityStep) *
        (unsigned int)((mutationProbabilityMax - mutationProbabilityMin) / mutationProbabilityStep);

    std::cout << std::fixed << std::setprecision(3);
    outputFile << std::fixed << std::setprecision(3);

    unsigned int runIndex = 0;
    for ( unsigned int baseGenerationSize = baseGenerationSizeMin; baseGenerationSize <= baseGenerationSizeMax; baseGenerationSize += baseGenerationSizeStep) {
        for ( unsigned int mutateVertexCount = mutateVertexCountMin; mutateVertexCount <= mutateVertexCountMax; mutateVertexCount += mutateVertexCountStep ) {
            for ( float crossProbability = crossProbabilityMin; crossProbability <= crossProbabilityMax; crossProbability += crossProbabilityStep ) {
                for ( float mutationProbability = mutationProbabilityMin; mutationProbability <= mutationProbabilityMax; mutationProbability += mutationProbabilityStep ) {
                    std::cout << "Progress: " << runIndex << "/" << totalRunCount;

                    try {
                        
                        std::string filename =
                            graphName + " " +
                            std::to_string( baseGenerationSize ) + " " +
                            std::to_string( mutateVertexCount ) + " " +
                            std::to_string( crossProbability ) + " " +
                            std::to_string( mutationProbability ) + ".txt";

                        std::ofstream file;
                        file.open( (path + filename).c_str() );

                        try {
                            file << "Params: ----------------------------- \n";
                            file << ("\n  baseGenerationSize: " + std::to_string( baseGenerationSize )).c_str();
                            file << ("\n  maxGenerationCount: " + std::to_string( baseGenerationSize )).c_str();
                            file << ("\n  maxTime: " + std::to_string( maxTime )).c_str();
                            file << ("\n  mutateVertexCount: " + std::to_string( baseGenerationSize )).c_str();
                            file << ("\n  crossProbability: " + std::to_string( baseGenerationSize )).c_str();
                            file << ("\n  mutationProbability: " + std::to_string( baseGenerationSize )).c_str();

                            std::shared_ptr<TSPSolver::Result> result = TSPSolver::solve( *graph, baseGenerationSize, maxGenerationCount, maxTime, mutateVertexCount, crossProbability, mutationProbability );

                            std::cout << "\r" << baseGenerationSize << ", " << mutateVertexCount << ", " << crossProbability << ", " << mutationProbability << "    :     " << result->bestSolution.getEvaluation() << "\n";
                            outputFile << baseGenerationSize << ", " << mutateVertexCount << ", " << crossProbability << ", " << mutationProbability << "    :     " << result->bestSolution.getEvaluation() << "\n";

                            file << "\n\nResult: ----------------------------- \n";
                            file << ("\n  best eval: " + std::to_string( result->bestSolution.getEvaluation() )).c_str();
                            file << ("\n  best solution: " + result->bestSolution.toString()).c_str();

                            file << "\n\nGenerations: ----------------------------- \n";
                            for ( unsigned int i = 0; i < result->generationStats.size(); ++i )
                                file << ("\n     " + std::to_string( i ) + "      :      " +
                                std::to_string( result->generationStats[ i ].bestEval )).c_str();

                        } catch ( std::exception& e ) {
                            file << (e.what() + std::string( "\n" )).c_str();
                        }

                        file.close();
                    } catch ( ... ) {
                    }

                    ++runIndex;
                }
            }
        }
    }

    outputFile.close();
}
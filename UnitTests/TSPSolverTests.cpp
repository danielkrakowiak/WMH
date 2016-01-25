#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

#include "TSPSolver.h"

#include "TestHelper.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(TSPSolverTests)
	{
	public:

		TEST_METHOD_INITIALIZE(Init)
		{
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{}

		TEST_METHOD(TSPSolver_solve_Simple_Graph)
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/test2.txt");

			unsigned int maxGenerationCount = 50;
			float        maxTime = 10.0f;
			unsigned int baseGenerationSize = 15;
			unsigned int mutateVertexCount = 2;
			float        crossProbability = 0.55f;
			float        mutationProbability = 0.025f;

            try {
                std::shared_ptr<TSPSolver::Result> result = TSPSolver::solve( *graph, baseGenerationSize, maxGenerationCount, maxTime, mutateVertexCount, crossProbability, mutationProbability );

                Assert::IsTrue( result->bestSolution.getVertexOrder().size() == (unsigned int)graph->getVertexCount() );
                Assert::IsTrue( TestHelper::solutionHasUniqueAndCorrectVertices( result->bestSolution ) );

            } catch ( ... ) {
                Assert::Fail();
            }
		}

		TEST_METHOD(TSPSolver_solve_Complex_Graph)
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/ft70 (38673).txt");

			unsigned int maxGenerationCount = 50;
			float        maxTime = 10.0f;
			unsigned int baseGenerationSize = 15;
			unsigned int mutateVertexCount = 2;
			float        crossProbability = 0.55f;
			float        mutationProbability = 0.025f;

            try {
			    std::shared_ptr<TSPSolver::Result> result = TSPSolver::solve(*graph, baseGenerationSize, maxGenerationCount, maxTime, mutateVertexCount, crossProbability, mutationProbability);

                Assert::IsTrue( result->bestSolution.getVertexOrder().size() == (unsigned int)graph->getVertexCount() );
                Assert::IsTrue( TestHelper::solutionHasUniqueAndCorrectVertices( result->bestSolution ) );

            } catch ( ... ) {
                Assert::Fail();
            }
		}
	};
}
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

#include "TSPSolver.h"


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

		TEST_METHOD(Compare_Result_Size_To_Graph_Size)
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/test2.txt");

			unsigned int maxGenerationCount = 50;
			float        maxTime = 300.0f;
			unsigned int baseGenerationSize = 15;
			unsigned int mutateVertexCount = 2;
			float        crossProbability = 0.55f;
			float        mutationProbability = 0.025f;

			std::shared_ptr<TSPSolver::Result> result = TSPSolver::solve(*graph, baseGenerationSize, maxGenerationCount, maxTime, mutateVertexCount, crossProbability, mutationProbability);

			try
			{
				Assert::IsTrue(result->bestSolution.getVertexOrder().size() == graph->getVertexCount());
			}
			catch (std::exception& e)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(Each_Corner_Visited_Once)
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/ft70 (38673).txt");

			unsigned int maxGenerationCount = 50;
			float        maxTime = 300.0f;
			unsigned int baseGenerationSize = 15;
			unsigned int mutateVertexCount = 2;
			float        crossProbability = 0.55f;
			float        mutationProbability = 0.025f;

			std::shared_ptr<TSPSolver::Result> result = TSPSolver::solve(*graph, baseGenerationSize, maxGenerationCount, maxTime, mutateVertexCount, crossProbability, mutationProbability);

			std::vector<bool> reservedNumber;
			reservedNumber.resize(graph->getVertexCount());

			for (int i=0; i < result->bestSolution.getVertexOrder().size(); i++)
			{
				reservedNumber[i] = false;
			}

			try
			{
				for (int i=0; i < result->bestSolution.getVertexOrder().size(); i++){
					if (reservedNumber[result->bestSolution.getVertexOrder().at(i)] == true) {
						Assert::Fail();
					} else {
						reservedNumber[result->bestSolution.getVertexOrder().at(i)] = true;
					}

				}

				for (int i = 0; i < result->bestSolution.getVertexOrder().size(); i++) {
					if (reservedNumber[result->bestSolution.getVertexOrder().at(i)] != true) {
						Assert::Fail();
					}
				}
			}
			catch (std::exception& e)
			{
				Assert::Fail();
			}
		}
	};
}
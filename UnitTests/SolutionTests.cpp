#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

#include "Solution.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SolutionTests)
	{
	public:

		TEST_METHOD_INITIALIZE(Init)
		{
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{}

		TEST_METHOD( Solution_createRandom_Size_Matching_Graph_Size )
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/test2.txt");

			std::shared_ptr<Solution> solution = std::make_shared<Solution>();

			solution = Solution::createRandom( *graph );

			try
			{
				Assert::IsTrue( graph->getVertexCount() == solution->getVertexOrder().size() );
			}
			catch ( ... )
			{
				Assert::Fail();
			}
		}

		TEST_METHOD( Solution_createRandom_Corners_Matching_Graph_Corners) 
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/test2.txt");

			std::shared_ptr<Solution> solution = std::make_shared<Solution>();

			solution = Solution::createRandom(*graph);

			int graphCount = graph->getVertexCount();

			try
			{
				for (unsigned int i = 0; i < solution->getVertexOrder().size(); i++)
				{
					Assert::IsTrue(solution->getVertexOrder().at(i) < graphCount);
				}
			}
			catch ( ... )
			{
				Assert::Fail();
			}
		}

		TEST_METHOD( Solution_cross_k_Positive )
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/test1.txt");

			std::shared_ptr<Solution> solution = std::make_shared<Solution>();
			std::shared_ptr<Solution> solution1 = std::make_shared<Solution>();
			std::shared_ptr<Solution> solution2 = std::make_shared<Solution>();

			solution1 = Solution::createRandom(*graph);
			solution2 = Solution::createRandom(*graph);

			bool sameSolutions = true;

			for (int i = 0; i < graph->getVertexCount(); i++)
			{
				if (solution1->getVertexOrder().at(i) != solution1->getVertexOrder().at(i)) {
					sameSolutions = false;
					break;
				}
			}

			solution = Solution::cross(*solution1, *solution2, 2);

			try
			{
				if (!sameSolutions) {
					Assert::IsTrue(solution->getVertexOrder().at(0) == solution1->getVertexOrder().at(0));
					Assert::IsTrue(solution->getVertexOrder().at(1) == solution1->getVertexOrder().at(1));
					Assert::IsFalse(solution->getVertexOrder().at(2) == solution1->getVertexOrder().at(2));
					Assert::IsFalse(solution->getVertexOrder().at(3) == solution1->getVertexOrder().at(3));
				}
			}
			catch ( ... )
			{
				Assert::Fail();
			}
		}

		TEST_METHOD( Solution_cross_k_Negative )
		{
			std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/test1.txt");

			std::shared_ptr<Solution> solution = std::make_shared<Solution>();
			std::shared_ptr<Solution> solution1 = std::make_shared<Solution>();
			std::shared_ptr<Solution> solution2 = std::make_shared<Solution>();

			solution1 = Solution::createRandom(*graph);
			solution2 = Solution::createRandom(*graph);

			solution = Solution::cross(*solution1, *solution2, -2);

			bool sameSolutions = true;

			for (int i = 0; i < graph->getVertexCount(); i++)
			{
				if (solution1->getVertexOrder().at(i) != solution1->getVertexOrder().at(i)) {
					sameSolutions = false;
					break;
				}
			}

			try
			{
				if (!sameSolutions) {
					Assert::IsFalse(solution->getVertexOrder().at(0) == solution1->getVertexOrder().at(0));
					Assert::IsFalse(solution->getVertexOrder().at(1) == solution1->getVertexOrder().at(1));
					Assert::IsTrue(solution->getVertexOrder().at(2) == solution1->getVertexOrder().at(2));
					Assert::IsTrue(solution->getVertexOrder().at(3) == solution1->getVertexOrder().at(3));
				}
			}
			catch ( ... )
			{
				Assert::Fail();
			}
		}
	};
}
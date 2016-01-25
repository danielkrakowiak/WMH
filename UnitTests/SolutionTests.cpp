#include "stdafx.h"
#include "CppUnitTest.h"
#include "Graph.h"

#include "Solution.h"

#include "TestHelper.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(SolutionTests)
	{
	public:

    TEST_METHOD( Solution_createRandom )
    {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/test2.txt" );

        try {
            std::shared_ptr<Solution> solution = Solution::createRandom( *graph );

            Assert::IsTrue( solution->getVertexOrder().size() == (unsigned int)graph->getVertexCount() );
            Assert::IsTrue( TestHelper::solutionHasUniqueAndCorrectVertices( *solution ) );
        } catch ( ... ) {
            Assert::Fail();
        }
    }

    TEST_METHOD( Solution_cross_different_solutions_for_positive_k )
    {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/test1.txt" );

        std::shared_ptr<Solution> solution1 = Solution::createRandom( *graph );

        std::shared_ptr<Solution> solution2 = nullptr;
        do {
            solution2 = Solution::createRandom( *graph );
        } while ( TestHelper::areSolutionsSame( *solution1, *solution2 ) );

        try {

            std::shared_ptr<Solution> solution = Solution::cross( *solution1, *solution2, 2 );

            TestHelper::solutionHasUniqueAndCorrectVertices( *solution );
        } catch ( ... ) {
            Assert::Fail();
        }
    }

    TEST_METHOD( Solution_cross_different_solutions_for_negative_k )
    {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/test1.txt" );

        std::shared_ptr<Solution> solution1 = Solution::createRandom( *graph );

        std::shared_ptr<Solution> solution2 = nullptr;
        do {
            solution2 = Solution::createRandom( *graph );
        } while ( TestHelper::areSolutionsSame( *solution1, *solution2 ) );

        try {

            std::shared_ptr<Solution> solution = Solution::cross( *solution1, *solution2, -2 );

            TestHelper::solutionHasUniqueAndCorrectVertices( *solution );
        } catch ( ... ) {
            Assert::Fail();
        }
    }

    TEST_METHOD( Solution_cross_same_solutions_for_positive_k )
    {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/test1.txt" );

        std::shared_ptr<Solution> solution1 = Solution::createRandom( *graph );

        try {

            std::shared_ptr<Solution> solution = Solution::cross( *solution1, *solution1, 2 );

            TestHelper::solutionHasUniqueAndCorrectVertices( *solution );
            TestHelper::areSolutionsSame( *solution, *solution1 );
        } catch ( ... ) {
            Assert::Fail();
        }
    }

    TEST_METHOD( Solution_cross_same_solutions_for_negative_k )
    {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/test1.txt" );

        std::shared_ptr<Solution> solution1 = Solution::createRandom( *graph );

        try {

            std::shared_ptr<Solution> solution = Solution::cross( *solution1, *solution1, -2 );

            TestHelper::solutionHasUniqueAndCorrectVertices( *solution );
            TestHelper::areSolutionsSame( *solution, *solution1 );
        } catch ( ... ) {
            Assert::Fail();
        }
    }

    TEST_METHOD( Solution_mutate )
    {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/test1.txt" );

        std::shared_ptr<Solution> solution = Solution::createRandom( *graph );

        try {
            solution->mutate( 2, *graph);

            TestHelper::solutionHasUniqueAndCorrectVertices( *solution );
        } catch ( ... ) {
            Assert::Fail();
        }
    }
    };
}
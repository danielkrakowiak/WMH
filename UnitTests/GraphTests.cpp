#include "stdafx.h"
#include "CppUnitTest.h"

#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS( GraphTests )
	{
	public:

        TEST_METHOD_INITIALIZE( Init )
        {}

        TEST_METHOD_CLEANUP( Cleanup )
        {}
		
		TEST_METHOD( Graph_Initial_State_Test )
		{
			Graph graph;

            Assert::IsTrue( graph.getVertexCount() == 0 );

            try 
            {
                graph.getWeight( 0, 1 );
                Assert::Fail();
            } 
            catch ( std::exception& e ) 
            {}
		}

        TEST_METHOD( Graph_Loading_From_Wrong_Path )
        {
            try 
            {
                std::shared_ptr<Graph> graph = Graph::loadFromFile( "blabla.txt" );
                Assert::Fail();
            } 
            catch ( ... ) 
            {}
        }

        TEST_METHOD( Graph_Loading_Corrupted_1 )
        {
            try 
            {
                std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/Test/corrupted1.txt" );
                Assert::Fail();
            } 
            catch ( ... )  
            {}
        }

        TEST_METHOD( Graph_Loading_Corrupted_2 )
        {
            try 
            {
                std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/Test/corrupted2.txt" );
                Assert::Fail();
            } 
            catch ( ... ) 
            {}
        }

		TEST_METHOD( Graph_Loading_Simple_Check_Size )
		{
			try
			{
				std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/Test/simple1.txt");
				Assert::IsNotNull(graph.get());

				Assert::IsTrue(graph->getVertexCount() == 4);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD( Graph_Loading_Simple_Check_Weights )
		{
			try
			{
				std::shared_ptr<Graph> graph = Graph::loadFromFile("../WMH/Graphs/Test/simple1.txt");
				Assert::IsNotNull(graph.get());

				Assert::IsTrue(graph->getWeight(0, 1) == 4.0f);
				Assert::IsTrue(graph->getWeight(1, 2) == 2.0f);
				Assert::IsTrue(graph->getWeight(2, 1) == 3.0f);
				Assert::IsTrue(graph->getWeight(2, 3) == 11.0f);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

        TEST_METHOD( Graph_Loading_Complex_Check_Size )
        {
            try 
            {
                std::shared_ptr<Graph> graph = Graph::loadFromFile( "../WMH/Graphs/Test/complex1.txt" );
                Assert::IsNotNull( graph.get() );

                Assert::IsTrue( graph->getVertexCount() == 70 );
            } 
            catch ( ... ) 
            {
                Assert::Fail();
            }
        }
	};
}
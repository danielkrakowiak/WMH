#include "Graph.h"
#include <Windows.h>

void main()
{
    try {
        std::shared_ptr<Graph> graph = Graph::loadFromFile( "Graphs/test1.txt" );
    } catch ( std::exception& e ) {
        OutputDebugString( (e.what() + std::string( "\n" )).c_str() );
    }
}
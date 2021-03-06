#include "Solution.h"

#include <string>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <windows.h>

#include "Graph.h"

std::default_random_engine Solution::randomGenerator = std::default_random_engine( std::chrono::system_clock::now( ).time_since_epoch( ).count( ) );

std::shared_ptr<Solution> Solution::createRandom( const Graph& graph )
{
    std::shared_ptr<Solution> solution = std::make_shared<Solution>();

    std::vector<int> vertices;
    vertices.resize( graph.getVertexCount() );
    for ( int i = 0; i < graph.getVertexCount(); ++i )
        vertices[ i ] = i;

    solution->vertexOrder.resize( graph.getVertexCount() );

    std::uniform_int_distribution<int> distribution( 0, graph.getVertexCount() );

    for ( int i = 0; i < graph.getVertexCount(); ++i ) {
        const int randomIndex = distribution( randomGenerator ) % vertices.size( );

        solution->vertexOrder[ i ] = vertices[ randomIndex ];

        vertices.erase( vertices.begin() + randomIndex );
    }

	solution->evaluate( graph );

    return solution;
}

std::shared_ptr<Solution> Solution::reproduce( const Solution& solution1, const Solution& solution2, const Graph& graph )
{
	std::shared_ptr<Solution> solution = std::make_shared<Solution>();

	solution->vertexOrder.resize(solution1.getVertexOrder().size());
    
	signed int min = (solution1.getVertexOrder().size()) - 2*(solution1.getVertexOrder().size()) + 1;
	int max = (solution1.getVertexOrder().size()) - 1;
	signed int k;

	do {
		k = min + (rand() % (int)(max - min + 1));
	} while (k == 0);

	solution = cross(solution1, solution2, k);

    solution->evaluate( graph );

	return solution;
}

std::shared_ptr<Solution> Solution::cross(const Solution& solution1, const Solution& solution2, const int k)
{
	std::shared_ptr<Solution> solution = std::make_shared<Solution>();

	solution->vertexOrder.resize(solution1.getVertexOrder().size());

	std::vector<int> bannedCorners;
	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> diff;
	
	v1 = solution1.getVertexOrder();
	v2 = solution2.getVertexOrder();

	if (k > 0) {
		for (int i = 0; i < k; i++) {
			bannedCorners.push_back(v1[i]);
		}

	} else { //k <0
		for (int i = k; i < 0; i++) {
			bannedCorners.push_back(v1[v1.size()+i]);
		}
	}
	
	for (int i = 0; i < v2.size(); i++) {
		bool flag = TRUE;
		for (int j = 0; j < bannedCorners.size(); j++) {
			if (v2[i] == bannedCorners[j]) {
				flag = FALSE;
			}
		}
		if (flag) {
			diff.push_back(v2[i]);
		}
	}

	if (k > 0) {
		bannedCorners.insert(bannedCorners.end(), diff.begin(), diff.end());
		for (int i = 0; i < solution1.getVertexOrder().size(); ++i) {
			solution->vertexOrder[i] = bannedCorners[i];
		}
	} else {
		diff.insert(diff.end(), bannedCorners.begin(), bannedCorners.end());
		for (int i = 0; i < solution1.getVertexOrder().size(); ++i) {
			solution->vertexOrder[i] = diff[i];
		}
	}
	
	return solution;
}

void Solution::mutate( int k, const Graph& graph )
{
	int min = 0;
	int max = getVertexOrder().size() - 1;
	int elementNumber;
	
	std::vector<int> chosenPositions;
	std::vector<int> chosenNumbers;
	
	for (int i = 0; i < k; i++) {
		do {
			elementNumber = min + (rand() % (int)(max - min + 1));
		} while (std::find(chosenPositions.begin(), chosenPositions.end(), elementNumber) != chosenPositions.end());
		
		chosenPositions.push_back(elementNumber);
		chosenNumbers.push_back(this->vertexOrder[elementNumber]);
	}

	/*for (int i = 0; i < k; i++) {
		OutputDebugString(( "element position " + std::to_string(chosenPositions[i]) + "\n").c_str());
		OutputDebugString((" value: " + std::to_string(chosenNumbers[i]) + "\n").c_str());
	}*/

	shuffle(chosenNumbers.begin(), chosenNumbers.end(), randomGenerator);

	for (int i = 0; i < k; i++) {
		elementNumber = chosenPositions[i];
		this->vertexOrder[elementNumber] = chosenNumbers[i];
	}

    evaluate( graph );
}

Solution::Solution() :
evaluation(FLT_MAX)
{}

Solution::Solution( const Solution& obj ) :
evaluation( obj.evaluation ),
vertexOrder( obj.vertexOrder.cbegin(), vertexOrder.cend() )
{}

Solution::~Solution()
{}

const std::vector<int>& Solution::getVertexOrder() const
{
    return vertexOrder;
}

float Solution::getEvaluation() const
{
    return evaluation;
}

void Solution::evaluate( const Graph& graph )
{
    if ( getVertexOrder().size() != graph.getVertexCount() )
        throw std::exception( "Solution::evaluate - path is incomplete." );

    evaluation = 0.0f;

    for ( int i = 0; i < graph.getVertexCount() - 1; ++i )
        evaluation += graph.getWeight( getVertexOrder()[ i ], getVertexOrder()[ i + 1 ] );

    // Add cost of going back to the origin.
    evaluation += graph.getWeight( getVertexOrder()[ graph.getVertexCount() - 1 ], getVertexOrder()[ 0 ] );
}

std::string Solution::toString( ) const
{
    std::string text;

    text += "{";
    for ( int i = 0; i < (int)vertexOrder.size(); ++i ) {
        text += ( i > 0 ? ", " : "" ) + std::to_string( vertexOrder[ i ] );
    }
    text += "}";

    return text;
}

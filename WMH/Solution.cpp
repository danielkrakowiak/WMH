#include "Solution.h"

#include <string>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>

std::default_random_engine Solution::randomGenerator = std::default_random_engine( std::chrono::system_clock::now( ).time_since_epoch( ).count( ) );

std::shared_ptr<Solution> Solution::createRandom( int vertexCount )
{
    std::shared_ptr<Solution> solution = std::make_shared<Solution>();

    std::vector<int> vertices;
    vertices.resize( vertexCount );
    for ( int i = 0; i < vertexCount; ++i )
        vertices[ i ] = i;

    solution->vertexOrder.resize( vertexCount );

    std::uniform_int_distribution<int> distribution( 0, vertexCount );

    for ( int i = 0; i < vertexCount; ++i ) {
        const int randomIndex = distribution( randomGenerator ) % vertices.size( );

        solution->vertexOrder[ i ] = vertices[ randomIndex ];

        vertices.erase( vertices.begin() + randomIndex );
    }

	reproduce(*solution, *solution);

    return solution;
}

std::shared_ptr<Solution> Solution::reproduce( const Solution& solution1, const Solution& solution2 )
{
	std::shared_ptr<Solution> solution = std::make_shared<Solution>();

	solution->vertexOrder.resize(solution1.getVertexOrder().size());
    
	signed int min = (solution1.getVertexOrder().size()) - 2*(solution1.getVertexOrder().size()) + 1;
	int max = (solution1.getVertexOrder().size()) - 1;
	signed int k;

	do {
		k = min + (rand() % (int)(max - min + 1));
	} while (k == 0);

	solution = crosses(solution1, solution2, k);

	return solution;
}

std::shared_ptr<Solution> Solution::crosses(const Solution& solution1, const Solution& solution2, const int k)
{
	std::shared_ptr<Solution> solution = std::make_shared<Solution>();

	solution->vertexOrder.resize(solution1.getVertexOrder().size());

	std::vector<int> bannedCorners;
	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> diff;
	
	v1 = solution1.getVertexOrder();
	//v1.push_back(5);
	v2 = solution2.getVertexOrder();
	//v2.push_back(3);

	if (k > 0) {
		for (int i = 0; i < k; i++) {
			bannedCorners.push_back(v1[i]);
		}

		diff = solution2.getVertexOrder();
		//diff.push_back(3);

	} else { //k <0
		for (int i = k; i < 0; i++) {
			bannedCorners.push_back(v1[v1.size()+i]);
		}

		diff = solution1.getVertexOrder();
		//diff.push_back(5);

	}
	
	int p = 0;
	for (int i = 0; i < v1.size(); i++) {
		for (int j = 0; j < bannedCorners.size(); j++) {
			if (v1[i] == bannedCorners[j]) {
				diff.erase(diff.begin() + (i - p));
				p++;
			}
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

void Solution::mutate(int k)
{
    //#TODO: Modify this solution with k-interchange (k as param).
}

Solution::Solution()
{}


Solution::~Solution()
{}

const std::vector<int>& Solution::getVertexOrder() const
{
    return vertexOrder;
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

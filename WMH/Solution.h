#pragma once

#include <vector>
#include <memory>
#include <random>

class Graph;

class Solution
{
    public:

    static std::shared_ptr<Solution> createRandom( const Graph& graph );
    static std::shared_ptr<Solution> reproduce( const Solution& solution1, const Solution& solution2, const Graph& graph );

    Solution();
    Solution( const Solution& obj );
    ~Solution();

    void mutate( int k, const Graph& graph );

    const std::vector<int>& getVertexOrder() const;
    float getEvaluation() const;
    std::string toString() const;

    private:

    static std::default_random_engine randomGenerator;
	static std::shared_ptr<Solution> cross( const Solution& solution1, const Solution& solution2, const int k );

    void evaluate( const Graph& graph );

    std::vector<int> vertexOrder;
    float            evaluation;
};


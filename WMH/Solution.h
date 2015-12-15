#pragma once

#include <vector>
#include <memory>
#include <random>

class Solution
{
    public:

    static std::shared_ptr<Solution> createRandom( int vertexCount );
    static std::shared_ptr<Solution> reproduce( const Solution& solution1, const Solution& solution2 );

    Solution();
    ~Solution();

    const std::vector<int>& getVertexOrder() const;
    std::string toString() const;

    private:

    static std::default_random_engine randomGenerator;

    std::vector<int> vertexOrder;
};


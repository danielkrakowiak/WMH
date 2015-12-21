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

    void mutate(int k);

    const std::vector<int>& getVertexOrder() const;
    std::string toString() const;

    private:

    static std::default_random_engine randomGenerator;
	static std::shared_ptr<Solution> crosses(const Solution& solution1, const Solution& solution2, const int k);

    std::vector<int> vertexOrder;
};

